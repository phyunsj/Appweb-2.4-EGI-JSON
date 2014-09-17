#GARD PLC-PRO

A simple web application to handle GARD PLC-PRO JSON Communications and provide JSON files for HTTP GET request.

## Quick Start

Install node.js and npm prior to run an application as shown below

Install dependencies. 

```
$ npm install
```

Start the server.

```
$ npm start
```

> RFL-GARD-PLC-Demo@0.0.1 start ***Project Directory*** $

> node app.js

> db init...

> Running on port **8080**

Mulitple json files will be created with default values to interact with a SPA application,

# Supported Services 

***rfljsonapp-ng.js*** providess the enum value of *cmd* and *returncode*.
 
## Login

All users need to  log in prior to request other services. **userSession** will be kept and tracked continously throughout the operation. **userSession** will be renewed by a server. The session timeout is 5 mins. **userPrivilege** will be used internally by a SPA to control UI elements. 

#### JSON

request 

>```{"cmd":101, "userPassword":"admin","loginName":"admin"}```

response 

>```{"loginName":"admin","userSession":"HIhIrUPgWseJ", "userPrivilege": 4, returncode":301,"errormsg":"Success."}```

## Logout

#### JSON
request

> ```{"cmd":102,"userSession":"HIhIrUPgWseJ","loginName":"admin"}```

response 

>```{"loginName":"admin","userSession":"empty","returncode":301,"errormsg":"Success."}```

## PLC Configuration

All parameters (additional parameters are *cmd*, *userSession* and *loginName* ) are sent regardless of **plcSystemMode** but ***General Settings +  FSK Settings*** will be shown if plcSystemMode is 2F/3F. (For ON/OFF, ***General Settings + ON/OFF Settings***)

General Settings

    plcSlotNum
    plcSystemMode
    plcModuleEnable
    plcTxCenterFrequency	
    plcRxCenterFrequency
    plcRxBandwidth
    plcMinRxLevel
    plcRpmAlarmThreshold
    plcFskTxGuardLevel	
    plcFskTxTripLevel
    plcDiscriminatorEnergyThreshold
    plcRxAgcSetpoint

FSK Settings

    plcLowSignalLevelAlarm	
    plcTxEnable	
    plcRxEnable	
    plcTxShift	
    plcRxThreshold	
    plcPretripTimer	
    plcSNRAlarmThreshold	
    plcTrip1ShiftDirection	 

ON/OFF Settings

    plcBlockHoldTimer	
    plcStart1InputPolarity	
    plcStart2InputPolarity	
    plcStop1InputPolarity	
    plcStop2InputPolarity	
    plcStart12AndOr
    plcStop12AndOr	
    plcLocalTxCausesBlock	
    plcTxLogicBusStartBit	
    plcTxLogicBusLength	
    plcRxLogicBusStartBit	
    plcRxLogicBusLength	
    plcCheckbackMode	
    plcCheckback1Command	
    plcCheckback1Response	
    plcCheckback1Level	
    plcCheckback2Command	
    plcCheckback2Response	
    plcCheckback2Level	
    plcCheckback3Command	
    plcCheckback3Response	
    plcCheckback3Level	
    plcCheckback4Command	
    plcCheckback4Response	
    plcCheckback4Level	
    plcCheckback5Command	
    plcCheckback5Response	
    plcCheckback5Level
    plcCheckback6Command	
    plcCheckback6Response	
    plcCheckback6Level	
    plcCheckback7Command	
    plcCheckback7Response	
    plcCheckback7Level	
    plcCheckback8Command	
    plcCheckback8Response	
    plcCheckback8Level	
    plcTxHardCarrierCode1	
    plcTxHardCarrierCode2	
    plcTxHardCarrierCode3	
    plcTxHardCarrierCode4	
    plcRxHardCarrierLowPower	
    plcRxHardCarrierHighPower	
    plcHardCarrierTimer	
    plcRemoteInitCode	
    plcCheckbackStartTimeHour	
    plcCheckbackStartTimeMinute	
    plcCheckbackHoursBetween	
    plcCheckbackResponseTimeout	
  

```plcSlotNum``` points a PLC slot(or module) to be configured.

```plcSystemMode``` indicates PLC mode. (FSK - 2F/3F or ON/OFF)

```plcTxCenterFrequency``` ```plcRxCenterFrequency``` converted from a float to an integer. 

```plcCheckbackMode``` enable/disable plcCheckback[1..8]Command and plcCheckback[1..8]Response settings

```plcCheckback[1..8]Command``` ```plcCheckback[1..8]Response``` must have an unique value from 1 to 16 if not 0.

  
#### JSON 
Request 

>```{"plcRxCenterFrequency":240,"plcTxLogicBusLength":8,"plcCheckback6Response":0,"plcRxHardCarrierLowPower":0,"plcCheckback1Response":0,"plcRxAgcSetpoint":7,"plcCheckback5Response":0,"plcLowSignalLevelAlarm":10,"plcTrip1ShiftDirection":0,"plcModuleEnable":1,"plcCheckback2Level":0,"plcCheckback7Level":0,"plcRxLogicBusLength":10,"plcCheckback4Level":0,"plcTxEnable":1,"plcCheckbackResponseTimeout":0,"plcCheckback4Command":0,"plcSystemMode":2,"plcPretripTimer":9,"plcLocalTxCausesBlock":1,"loginName":"admin","plcRemoteInitCode":0,"plcCheckbackStartTimeMinute":4,"plcStop2InputPolarity":0,"plcCheckback2Command":0,"plcSNRAlarmThreshold":2,"plcCheckback4Response":0,"plcTxCenterFrequency":240,"plcFskTxTripLevel":1,"plcTxHardCarrierCode4":0,"plcCheckback8Level":0,"userSession":"P13tFH8W1R24","plcCheckback6Command":0,"plcCheckback2Response":0,"plcStart12AndOr":1,"plcFskTxGuardLevel":2,"plcSlotNum":4,"plcCheckback8Command":0,"plcStop12AndOr":1,"plcRxHardCarrierHighPower":0,"plcRpmAlarmThreshold":20,"plcCheckback5Level":0,"plcTxHardCarrierCode1":0,"plcCheckback7Command":0,"plcCheckback7Response":0,"plcCheckback5Command":0,"plcBlockHoldTimer":3,"plcRxBandwidth":1,"plcCheckback1Level":0,"plcCheckbackStartTimeHour":5,"plcTxHardCarrierCode2":0,"plcCheckback3Command":0,"plcCheckbackHoursBetween":2,"plcTxHardCarrierCode3":0,"plcStart1InputPolarity":0,"plcStop1InputPolarity":0,"plcHardCarrierTimer":0,"plcMinRxLevel":11,"plcTxShift":100,"plcCheckback1Command":0,"plcStart2InputPolarity":0,"plcCheckbackMode":2,"plcRxThreshold":25,"plcRxLogicBusStartBit":6,"cmd":107,"plcCheckback6Level":0,"plcCheckback8Response":0,"plcCheckback3Response":0,"plcCheckback3Level":0,"dummpy":0,"plcDiscriminatorEnergyThreshold":4,"plcRxEnable":1,"plcTxLogicBusStartBit":5}```

Response 

>```{"loginName":"admin","userSession":"3ieaGumNK2JG","returncode":301,"errormsg":"Success."}```

## PLC Status

#### JSON

request

>```{"loginName":"admin", "plcStatusSlotNum":4, "cmd":106, "userSession":"FYfcsIlQCPtq" }```

response

>```{"loginName":"admin","userSession":"kAxGuQRamA4c","returncode":301,"errormsg":"Success.","plcStatusSlotNum":4,"plcStatusSystemMode":2,"plcStatusTxPower":123,"plcStatusRxLevel":18,"plcStatusTxFailAlarm":1,"plcStatusRxCarrierAlarm":0,"plcStatusTxState":64,"plcStatusRxState":16,"plcStatusSNR":34,"plcStatusSNRAlarm":0,"plcStatusReflectedPower":111,"plcStatusReflectedPowerAlarm":0,"plcStatusTransHybridLoss":89,"plcStatusCheckbackMode":0,"plcStatusCheckbackStatus":0,"plcStatusRearBoardID":0,"plcStatusPLCSoftwareVersion":12,"plcStatusActelVersionMajor":13,"plcStatusPICVersion":14,"plcStatusActelVersionMinor":15,"plcStatusHMIInterfaceVersion":14,"plcStatusTripKey1":0,"plcStatusTripKey2":0,"plcStatusTrip1Rx":0,"plcStatusTrip2Rx":0,"plcStatusRxAlarm":0,"plcStatusRPMAlarm":0,"plcStatusCheckbackTestsCount":0,"plcStatusCheckbackPassCount":0,"plcStatusCheckbackFailCount":0}```

## PLC Command/Diagnosis

#### JSON
request 

>```{"plcCmndSendCheckbackCode":0,"plcCmndForceCarrier":0,"plcCmndSendHardCarrierRequest":0,"plcCmndLogicBusOutput":1,"plcCmndSlotNum":4,"plcCmndCalibrateRPM":0,"loginName":"admin","cmd":108,"userSession":"2leFsA0X50hJ","plcCmndCalibrateTxLevel":0,"plcCmndRecommission":0,"plcCmndResetAllCounters":0,"dummpy":0,"plcCmndStartCheckback":0}```

response 

>```{"loginName":"admin","userSession":"cWP5ymoznoT6","returncode":301,"errormsg":"Success."}```

## LED Configuration

####JSON

>request 

```{"ledColorOffBus":2,"ledNum":7,"ledColorYellowActiveState":1,"ledColorOffActiveState":1,"ledColorYellowLabel":"yellow label","loginName":"admin","ledColorYellowBit":24,"ledColorGreenActiveState":1,"ledColorRedActiveState":1,"ledColorGreenLabel":"off label","userSession":"P0XMdLyy3Zoi","ledColorOffLabel":"off label","ledColorGreenBus":2,"ledColorYellowBus":3,"ledColorRedLabel":"red label","ledColorRedBus":1,"ledColorRedBit":25,"ledColorGreenBit":23,"ledColorOffBit":23,"cmd":114,"ledDescription":"testing"}```

response 

>```{"loginName":"admin","userSession":"Wku2S1qGpf2M","returncode":301,"errormsg":"Success."}```

## LED Status

####JSON

request 

>```{"cmd":115,"loginName":"admin","userSession":"5wGS3UQkJ0Wc"}```

response 

>```{"loginName":"admin","userSession":"iaXEhER5XBpM","returncode":301,"errormsg":"Success.","led":"0:2:2:1:3:1:1:0:3:3:0:3:0:1:1:1:2:2:0:2:"}```



