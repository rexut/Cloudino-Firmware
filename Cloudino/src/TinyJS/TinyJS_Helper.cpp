/*
  TinyJS_Helper.cpp - TinyJS Library add-on for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "TinyJS_Helper.h"

#include <Arduino.h>  // for type definitions

void addIntChild(CScriptVar *ret, String name, int val)
{
    CScriptVar *var = new CScriptVar();
    var->setInt(val);
    ret->addChild(name, var);
}

void addDoubleChild(CScriptVar *ret, String name, double val)
{
    CScriptVar *var = new CScriptVar();
    var->setDouble(val);
    ret->addChild(name, var);
}

void addStringChild(CScriptVar *ret, String name, String val)
{
    CScriptVar *var = new CScriptVar();
    var->setString(val);
    ret->addChild(name, var);
}
