/*
  TinyJS_GPIOBinding.cpp - TinyJS Library add-on for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "TinyJS_GPIOBinding.h"

void scPinMode(CScriptVar *v, void *) {
  pinMode(v->getParameter("pin")->getInt(), v->getParameter("mode")->getInt());
}

void scDigitalWrite(CScriptVar *v, void *) {
  digitalWrite(v->getParameter("pin")->getInt(), v->getParameter("value")->getInt());
}

void scDigitalRead(CScriptVar *v, void *) {
  int value=digitalRead(v->getParameter("pin")->getInt());
  v->getReturnVar()->setInt(value);
}

void scAnalogRead(CScriptVar *v, void *) {
  int value=analogRead(A0);
  v->getReturnVar()->setInt(value);
}

void scAnalogWrite(CScriptVar *v, void *) {
  analogWrite(v->getParameter("pin")->getInt(), v->getParameter("value")->getInt());
}

// ----------------------------------------------- Register Functions
void registerGPIOBinding(CTinyJS *tinyJS) {
    tinyJS->addNative(F("function GPIO.pinMode(pin,mode)"), scPinMode, 0);
    tinyJS->addNative(F("function GPIO.digitalWrite(pin,value)"), scDigitalWrite, 0);
    tinyJS->addNative(F("function GPIO.digitalRead(pin)"), scDigitalRead, 0);
    tinyJS->addNative(F("function GPIO.analogRead()"), scAnalogRead, 0);
    tinyJS->addNative(F("function GPIO.analogWrite(pin,value)"), scAnalogWrite, 0);
    tinyJS->execute(F("GPIO.HIGH=1;GPIO.LOW=0;GPIO.INPUT=0;GPIO.OUTPUT=1;GPIO.INPUT_PULLUP=2;"));
}
