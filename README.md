
# Appweb 2 EGI+JSONCPP

Integrate JSON Parser to process POST data (JSON Format) using EGI handler. 
Appweb 2.x/3.x supports EGI handler. Appweb 2.x was written in C++. Appweb 3+ ( 2018 : the latest version is 7) is re-written in C.

## Source Code 

##### Appweb 2.4.4 https://www.embedthis.com/appweb/download.html (Commercial or GPL License)

##### JsonCpp https://github.com/open-source-parsers/jsoncpp (MIT License)

## Quick Start

```
 $ cd ${PROJECT_ROOT_DIR}/lib/jsoncpp
 $ make
 $ cd ${PROJECT_ROOT_DIR}/egiForm
 $ make 
 $ cd ${PROJECT_ROOT_DIR}/appweb-2.4.4 
 $ ./configure ...options...
 $ make
 $ cd samples/```C++```/EgiSample (Modified version of samples/```C++```/simpleEgi)
 $ make
 $ export **$LD_LIBRARY_PATH**=... 
 (Perhaps you want to put *.so in one place.)
 $ ./simpleEgi

 $ ./unittest_egi.py  -t **IP-ADDR** 
```

```
$ ./unittest-egi.py  -t 127.0.0.1
test_json (__main__.TestAppweb) ... [RESULT] HTTP Response Status : 200
[RESULT] HTTP Response Header : {'Content-length': '48', 'Keep-Alive': 'timeout=60, max=100', 'Server': 'Embedthis-Appweb/2.4.4', 'Connection': 'keep-alive', 'Cache-Control': 'no-cache', 'Content-type': 'text/html'}
[RESULT] HTTP Payload         : {"errno":302,"message":"SUCCESS","result":1235}

ok

----------------------------------------------------------------------
Ran 1 test in 0.097s

OK
```

## EGI Handler/Form 

`EGI` = **E**mbedded **G**ateway **I**nterface. **Fast** in-process replacement for `CGI`.


`EgiForm Registration` after `setupServer()` before `http->start()` in `realMain():appweb.cpp`


```
new MaEgiForm("/myjson.egi")
-> MaEgiHandler::insertForm(this) 
```

Per-POST request if URI has **.egi** extension
```
MaEgiHandler::run() {
  ...
  form = (MaEgiForm*) forms->lookup(uri); 
  form->run()
  ...
}
```

**MaEgiForm::run**(MaRequest *rq, char *script, char *uri, char *query, char *postData, int postLen)
```
JsonReader.parse( postData, JsonReq );
JsonReq.get(...)
/* ... do something ... */
JsonRes['result'] = ...some value...;
postResponse = JsonWriter.write(JsonRes);
rq->writeFmt("%s", postResponse.c_str());
```




## Use Cases

Configure IoT over HTTP(s). Session Management & User Authentication are required.

##### Other Options : 

- GoAhead Webserver (GoAction)
- XML-RPC

##### appweb 2.4.4 configuration options for this build

```
./configure  --type=RELEASE \
    --enable-samples \
	--disable-multi-thread \
	--enable-safe-strings \
	--enable-shared \
	--disable-static \
	--enable-modules \
	--enable-shared-libc \
	--disable-squeeze \
	--enable-access-log \
	--enable-config-parse \
	--enable-cookie \
	--enable-digest-auth \
	--disable-ejs \
	--disable-if-modified \
	--disable-ipv6 \
	--enable-keep-alive \
	--enable-ranges \
	--enable-session \
	--enable-stdc++ \
	--with-egi=builtin \
	--with-admin=builtin \
	--with-auth=builtin \
	--without-cgi \
	--with-dir=builtin \
	--with-copy=builtin \
	--with-put=builtin \
	--with-upload=builtin \
	--disable-test \
	--without-esp \
	--without-c-api \
	--without-gacompat
```
