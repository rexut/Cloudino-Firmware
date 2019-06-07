/*
  TinyJS_HCSR04Binding.cpp - TinyJS Library add-on for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "TinyJS_HCSR04Binding.h"
#include "TinyJS_Helper.h"

void scHCSR04Read(CScriptVar *c, void *) {
    int tpin = c->getParameter("tpin")->getInt();
    int hpin = c->getParameter("hpin")->getInt();

    int val=-1;

    pinMode(tpin, OUTPUT);
    digitalWrite(tpin, LOW);
    pinMode(hpin, INPUT);

    digitalWrite(tpin, HIGH);  //generamos Trigger (disparo) de 10us
    delayMicroseconds(10);
    digitalWrite(tpin, LOW);

    long duration = pulseIn(hpin, HIGH, 23400);  //medimos el tiempo entre pulsos, en microsegundos

    val = duration * 10 / 292/ 2;   //convertimos a distancia, en cm

    c->getReturnVar()->setInt(val);
}

// ----------------------------------------------- Register Functions
void registerHCSR04Binding(CTinyJS *tinyJS) {
    tinyJS->addNative(F("function HCSR04.read(tpin,hpin)"), scHCSR04Read, tinyJS); // Get HC-SR04 Values
}
