/*
  TinyJS_Firmware.cpp - TinyJS Library firmware integration for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "../CloudinoConf.h"

#include "../TinyJS_Firmware.h"

#include "TinyJS_Functions.h"
#include "TinyJS_ExtFunctions.h"
#include "TinyJS_MathFunctions.h"
#include "TinyJS_TimerBinding.h"
#ifdef CDINOJS
#include "TinyJS_CDINOBinding.h"
#endif
#include "TinyJS_GPIOBinding.h"
#include "TinyJS_DHT11Binding.h"
#include "TinyJS_HCSR04Binding.h"
#include "TinyJS_RCSwitchBinding.h"
#include "TinyJS_HTTPBinding.h"

#include "Trace.h"

#include <Arduino.h>  // for type definitions

void addDefaulFWBEFunct(UsrData *data);

void scReset(CScriptVar *, void *userdata) {
  UsrData *data=(UsrData*)userdata;
  CTinyJS *js = data->js;
  JSTimer *timer=data->timer;
#ifdef CDINOJS
  SMessageProc *proc=data->proc;
#endif
  js->reset();
  timer->clear();
#ifdef CDINOJS
  proc->clear();
#endif
  addDefaulFWBEFunct(data);
}

void scRestart(CScriptVar *, void *) {
  ESP.restart();
}

void scPrint(CScriptVar *v, void *) {
  TRACE(v->getParameter("text")->getString());
}

void scDump(CScriptVar *, void *userdata) {
  CTinyJS *js = (CTinyJS*)userdata;
  TRACE("FreeHeap:"+String(ESP.getFreeHeap()));
  js->root->trace(">  ");
}

void scRequire(CScriptVar *v, void *userdata) {
  UsrData *data = (UsrData*)userdata;
  CTinyJS *js=data->js;
  JSTimer *timer=data->timer;
#ifdef CDINOJS
  SMessageProc *proc=data->proc;
#endif

  String name=v->getParameter("name")->getString();

  if (name=="Object")
  {
    registerObjectFunctions(js);
  }
  else if(name=="Rand")
  {
    registerRandFunctions(js);
  }
  else if (name=="String")
  {
    registerStringFunctions(js);
    registerStringExtFunctions(js);
  }
  else if (name=="Double")
  {
    registerDoubleExtFunctions(js);
  }
  else if (name=="Integer")
  {
    registerIntegerFunctions(js);
  }
  else if (name=="JSON")
  {
    registerJSONFunctions(js);
  }
  else if (name=="Array")
  {
    registerArrayFunctions(js);
  }
  else if(name=="Math")
  {
    registerMathFunctions(js);
  }
  else if(name=="Timer")
  {
    registerTimerBinding(js, timer);
#ifdef CDINOJS
  }
  else if(name=="Cloudino")
  {
    registerCDINOBinding(js, proc);
#endif
  }
  else if(name=="GPIO")
  {
    registerGPIOBinding(js);
  }
  else if(name=="DHT11")
  {
    registerDHT11Binding(js);
  }
  else if(name=="HCSR04")
  {
    registerHCSR04Binding(js);
#ifdef RCSWITCH_SUPPORT
  }
  else if(name=="RCSwitch")
  {
    registerRCSwitchBinding(js);
#endif
  }
  else if(name=="HTTP")
  {
    registerHTTPBinding(js);
  }
}

void addDefaulFWBEFunct(UsrData *data)
{
  CTinyJS *js=data->js;

  registerCodeFunctions(js);
  registerParseFunctions(js);
  registerParseExtFunctions(js);
  js->addNative(F("function require(name)"), scRequire, data);
  js->addNative(F("function reset()"), scReset, data);
  js->addNative(F("function restart()"), scRestart, 0);
  js->addNative(F("function print(text)"), scPrint, 0);
  js->addNative(F("function dump()"), scDump, js);
}

// ----------------------------------------------- Register Firmware
#ifdef CDINOJS
void registerFirmware(CTinyJS *js, JSTimer *timer, SMessageProc *proc) {
#endif
#ifndef CDINOJS
void registerFirmware(CTinyJS *js, JSTimer *timer) {
#endif
  //Serial.begin(57600);
  UsrData *data=new UsrData();
  data->js=js;
  data->timer=timer;
#ifdef CDINOJS
  data->proc=proc;
#endif
  addDefaulFWBEFunct(data);
}
