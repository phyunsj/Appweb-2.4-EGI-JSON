///
///	@file 	myEgiForm.cpp
/// @brief 	Demonstrate the use of Embedded Gate Interface (EGI) 
///


#include	"appweb/appweb.h"
//#include    "egiHandler.h"

#include    "include/json.h"

#ifdef BLD_FEATURE_XMLRPC_MODULE
#include    "xmlrpc-c/base.hpp"
#include    "xmlrpc-c/registry.hpp"
#endif

#include    "myEgiForm.h"

const int action_add = 1;
const int action_sub = 2; 
//
////////////////////////////////////////////////////////////////////////

myJsonEgi::myJsonEgi(char *name) : MaEgiForm(name)
{
	//	Put required initialization (if any) here
}

////////////////////////////////////////////////////////////////////////

myJsonEgi::~myJsonEgi()
{
	//	Put cleanup here
}

////////////////////////////////////////////////////////////////////////
//
//	Method that is run when the EGI form is called from the web
//	page. Rq is the request context. URI is the bare URL minus query.
//	Query is the string after a "?" in the URL. Post data is posted
//	HTTP form data.
//

void myJsonEgi::run(MaRequest *rq, char *script, char *uri, char *query, 
	char *postData, int postLen)
{

#if TEST_MULTI_THREADED_ACCESS
	mprPrintf("In myJsonEgi::run, thread %s\n", mprGetCurrentThreadName());
#else
	mprPrintf("In myJsonEgi::run, single threaded\n");
#endif
    std::string      postResponse;
    int jsonParseError = 0;

    Json::Value      JsonReq;
    Json::Reader     JsonReader;
    Json::Value      JsonRes;
    Json::FastWriter JsonWriter;
    

    std::cout << "run::req[" << postData << "] size : " << postLen << std::endl;
    jsonParseError = JsonReader.parse( postData, JsonReq );

    if ( !jsonParseError )
    {
        JsonRes["errno"]    = 301; // error no.
        JsonRes["message"]  = "INVALID JSON FORMAT";
        postResponse = JsonWriter.write(JsonRes);
        rq->writeFmt("%s", postResponse.c_str());
    } else {

         
        int action = JsonReq.get("action", 0 ).asInt();
        int result = 0;
        switch( action ) {
        	case action_add :  result = JsonReq.get("code", 0 ).asInt(); result++; JsonRes["errno"] = 302; JsonRes["message"]  = "SUCCESS";
            break;
            case action_sub :  result = JsonReq.get("code", 0 ).asInt(); result--; JsonRes["errno"] = 302; JsonRes["message"]  = "SUCCESS";
            break;
            default  :  JsonRes["errno"] = 302; JsonRes["message"]  = "INVALID ACTION";
            break;
        }

        JsonRes["result"] = result;
        postResponse = JsonWriter.write(JsonRes);
        rq->writeFmt("%s", postResponse.c_str());
    }
  
    std::cout << "run::res[" << postResponse << "] size : " << postResponse.length() << std::endl;
    return;
}


#if BLD_FEATURE_XMLRPC_MODULE
////////////////////////////////////////////////////////////////////////
// XML-RPC
//

 
class sampleAddMethod : public xmlrpc_c::method {
public:
    sampleAddMethod() {
        // signature and help strings are documentation -- the client
        // can query this information with a system.methodSignature and
        // system.methodHelp RPC.
        this->_signature = "i:ii";
            // method's result and two arguments are integers
        this->_help = "This method adds two integers together";
    }
    void
    execute(xmlrpc_c::paramList const& paramList,
            xmlrpc_c::value *   const  retvalP) {
        
        int const addend(paramList.getInt(0));
        int const adder(paramList.getInt(1));
        
        paramList.verifyEnd(2);
        
        *retvalP = xmlrpc_c::value_int(addend + adder);

        // Sometimes, make it look hard (so client can see what it's like
        // to do an RPC that takes a while).
        if (adder == 1)
            sleep(2);
    }
};

class sampleSubMethod : public xmlrpc_c::method {
public:
    sampleSubMethod() {
        // signature and help strings are documentation -- the client
        // can query this information with a system.methodSignature and
        // system.methodHelp RPC.
        this->_signature = "i:ii";
            // method's result and two arguments are integers
        this->_help = "This method subtracts two integers together";
    }
    void
    execute(xmlrpc_c::paramList const& paramList,
            xmlrpc_c::value *   const  retvalP) {
        
        int const addend(paramList.getInt(0));
        int const adder(paramList.getInt(1));
        
        paramList.verifyEnd(2);
        
        if ( addend > adder )
           *retvalP = xmlrpc_c::value_int(addend - adder);
        else 
           *retvalP = xmlrpc_c::value_int(adder - addend);
        // Sometimes, make it look hard (so client can see what it's like
        // to do an RPC that takes a while).
        if (adder == 1)
            sleep(2);
    }
};

///////////////////////////////////////////////////////////////////////
myXmlRpcEgi::myXmlRpcEgi(char *name) : MaEgiForm(name)
{
	//	Put required initialization (if any) here
	xmlrpc_c::methodPtr const sampleAddMethodP(new sampleAddMethod);
    xmlrpc_c::methodPtr const sampleSubMethodP(new sampleSubMethod);

    myRegistry.addMethod("actionAdd", sampleAddMethodP );
    //myRegistry.addMethod("actionSub", sampleSubMethodP);
}

////////////////////////////////////////////////////////////////////////

myXmlRpcEgi::~myXmlRpcEgi()
{
	//	Put cleanup here
}

////////////////////////////////////////////////////////////////////////
//
//	Method that is run when the EGI form is called from the web
//	page. Rq is the request context. URI is the bare URL minus query.
//	Query is the string after a "?" in the URL. Post data is posted
//	HTTP form data.
//

void myXmlRpcEgi::run(MaRequest *rq, char *script, char *uri, char *query, 
	char *postData, int postLen)
{

#if TEST_MULTI_THREADED_ACCESS
	mprPrintf("In myXmlRpcEgi::run, thread %s\n", mprGetCurrentThreadName());
#else
	mprPrintf("In myXmlRpcEgi::run, single threaded\n");
#endif
    
    std::cout << "run::req[" << postData << "] size : " << postLen << std::endl;
    std::string           postResponse; 
    myRegistry.processCall( postData, &postResponse);
    rq->writeFmt("%s", postResponse.c_str());

    std::cout << "run::res[" << postResponse << "] size : " << postResponse.length() << std::endl;
    return;
}

#endif



