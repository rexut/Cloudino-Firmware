/*
  TinyJS_Helper.h - TinyJS Library add-on for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#ifndef TinyJS_Helper_h
#define TinyJS_Helper_h

#include "../TinyJS.h"

extern void addIntChild(CScriptVar *ret, String name, int val);
extern void addDoubleChild(CScriptVar *ret, String name, double val);
extern void addStringChild(CScriptVar *ret, String name, String val);

#endif  // TinyJS_Helper_h
