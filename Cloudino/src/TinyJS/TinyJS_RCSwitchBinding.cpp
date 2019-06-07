/*
  TinyJS_RCSwitchBinding.cpp - TinyJS Library add-on for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "TinyJS_RCSwitchBinding.h"
#include "TinyJS_Helper.h"

#include "Trace.h"

#ifdef RCSWITCH_SUPPORT

#include <RCSwitch.h>
RCSwitch *rcswitch = NULL;

void scRCSwitchEnableTransmit(CScriptVar *c, void *) {
    // protocol,pin,pulseLength,repeat
    int protocol = c->getParameter("protocol")->getInt();
    int pin = c->getParameter("pin")->getInt();
    int pulseLength = c->getParameter("pulseLength")->getInt();
    int repeat = c->getParameter("repeat")->getInt();
    if(rcswitch==NULL)rcswitch=new RCSwitch();
    rcswitch->setProtocol(protocol);
    rcswitch->enableTransmit(pin);
    rcswitch->setPulseLength(pulseLength);
    rcswitch->setRepeatTransmit(repeat);
    // TRACE("enableTransmit:"+String(protocol));
}

void scRCSwitchEnableReceive(CScriptVar *c, void *) {
    //pin
    int pin = c->getParameter("pin")->getInt();
    if(rcswitch==NULL)rcswitch=new RCSwitch();
    rcswitch->disableReceive();
    rcswitch->enableReceive(pin);
    //TRACE("enableReceive:"+String(pin));
}

void scRCSwitchSend(CScriptVar *c, void *) {
    //protocol,tpin,rpin,pulseLength,repeat
    String code = c->getParameter("code")->getString();
    if(rcswitch)
    {
      int str_len = code.length() + 1;
      char char_array[str_len];
      code.toCharArray(char_array, str_len);
      rcswitch->send(char_array);
      //TRACE("send:"+String(char_array));
    }
}

static char * dec2binWzerofill(unsigned long Dec, unsigned int bitLength){
  static char bin[64];
  unsigned int i=0;

  while (Dec > 0) {
    bin[32+i++] = (Dec & 1 > 0) ? '1' : '0';
    Dec = Dec >> 1;
  }

  for (unsigned int j = 0; j< bitLength; j++) {
    if (j >= bitLength - i) {
      bin[j] = bin[ 31 + i - (j - (bitLength - i)) ];
    }else {
      bin[j] = '0';
    }
  }
  bin[bitLength] = '\0';

  return bin;
}

void scRCSwitchReceive(CScriptVar *c, void *) {
    if(rcswitch)
    {
        //TRACE("available:"+String(rcswitch->available()));
        if (rcswitch->available())
        {
            String code=dec2binWzerofill(rcswitch->getReceivedValue(), rcswitch->getReceivedBitlength());
            //TRACE("code:"+code);
            CScriptVar *ret=c->getReturnVar();
            addIntChild(ret,F("protocol"),rcswitch->getReceivedProtocol());
            addDoubleChild(ret,F("value"),rcswitch->getReceivedValue());
            addStringChild(ret,F("code"),code);
            addIntChild(ret,F("bits"),rcswitch->getReceivedBitlength());
            addIntChild(ret,F("delay"),rcswitch->getReceivedDelay());
            rcswitch->resetAvailable();
        }
    }
}

// ----------------------------------------------- Register Functions
void registerRCSwitchBinding(CTinyJS *tinyJS) {
    tinyJS->addNative(F("function RCSwitch.enableTransmit(protocol,pin,pulseLength,repeat)"), scRCSwitchEnableTransmit, tinyJS);
    tinyJS->addNative(F("function RCSwitch.enableReceive(pin)"), scRCSwitchEnableReceive, tinyJS);
    tinyJS->addNative(F("function RCSwitch.send(code)"), scRCSwitchSend, tinyJS);
    tinyJS->addNative(F("function RCSwitch.receive()"), scRCSwitchReceive, tinyJS);
}

#endif  // RCSWITCH_SUPPORT
