#!/usr/bin/env python

import unittest
import requests
import json
import xmlrpclib
import pexpect
import sys, getopt, pprint

IPADDR = '127.0.0.1'

def cmdOptions(argv):
    global IPADDR  
    try:
      opts, args = getopt.getopt(argv,"ht:",["target="])
    except getopt.GetoptError:
      print 'Usage : unittest-appweb.py -t <target>'
      sys.exit(2)
    for opt, arg in opts:
      if opt == '-h':
        print 'Usage : unittest-appweb.py -t <target> '
        sys.exit()
      elif opt in ("-t", "--target"):
        IPADDR = arg
      

class TestAppweb(unittest.TestCase):

    global IPADDR

    def setUp(self):
        pass

    def tearDown(self):
        pass

    def test_json(self):
        
        TargetUrl = 'http://'+IPADDR+':8888/json.egi'
        self.headers = {'Content-type': 'application/json', 'Accept': 'text/plain'}

        # login as admin
        payload = {'action' : 1, 'code' : 1234 }
        r = requests.post(TargetUrl, data=json.dumps(payload), timeout=60, headers=self.headers, verify=False)
        print '[RESULT] HTTP Response Status :', r.status_code
        print '[RESULT] HTTP Response Header :', r.headers
        print '[RESULT] HTTP Payload         :', r.content 
        jsonResponse = json.loads(r.content)
        self.assertEqual( jsonResponse['result'], 1235)


    def xmlrpc(self):
        TargetUrl = 'http://'+IPADDR+':8888/xmlrpc.egi'

        proxy = xmlrpclib.ServerProxy(TargetUrl)
        try:
            print proxy.actionAdd(2, 5)
            print proxy.actionSub(5, 3)
            self.assertEqual( 6, 7)

        except xmlrpclib.Fault as err:
            print "A fault occurred"
            print "Fault code: %d" % err.faultCode
            print "Fault string: %s" % err.faultString
            self.assertEqual( err.faultCode, 0)
          

###################################################################################################
# 
#  __main__  UnitTest Runner
#
if __name__ == '__main__':

    cmdOptions(sys.argv[1:])

    suite = unittest.TestLoader().loadTestsFromTestCase(TestAppweb)
    result = unittest.TextTestRunner(verbosity=2).run(suite)
    
