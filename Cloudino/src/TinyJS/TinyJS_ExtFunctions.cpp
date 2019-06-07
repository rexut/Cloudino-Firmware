/*
  TinyJS_ExtFunctions.cpp - TinyJS Library add-on for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "TinyJS_ExtFunctions.h"

#include <Arduino.h>  // for type definitions

#include <cstdlib>
static const size_t NPOS = -1;

void scStringLastIndexOf(CScriptVar *c, void *) {
    String str = c->getParameter("this")->getString();
    String search = c->getParameter("search")->getString();
    size_t p = str.lastIndexOf(search);
    int val = (p==NPOS) ? -1 : p;
    c->getReturnVar()->setInt(val);
}

void scDoubleParseFloat(CScriptVar *c, void *) {
    String str = c->getParameter("str")->getString();
    float val = atof(str.c_str());
    c->getReturnVar()->setDouble(val);
}

// ----------------------------------------------- Register String Functions
void registerStringExtFunctions(CTinyJS *tinyJS) {
    tinyJS->addNative(F("function String.lastIndexOf(search)"), scStringLastIndexOf, 0); // find the last position of a string in a string, -1 if not
}

// ----------------------------------------------- Register Double Functions
void registerDoubleExtFunctions(CTinyJS *tinyJS) {
    tinyJS->addNative(F("function Double.parseFloat(str)"), scDoubleParseFloat, 0); // string to float
}

// ----------------------------------------------- Register Parse Functions
void registerParseExtFunctions(CTinyJS *tinyJS) {
    tinyJS->addNative(F("function parseFloat(str)"), scDoubleParseFloat, 0); // string to float
}

// ----------------------------------------------- Register Functions
void registerExtFunctions(CTinyJS *tinyJS) {
    registerStringExtFunctions(tinyJS);
    registerDoubleExtFunctions(tinyJS);
}
