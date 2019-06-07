/*
  TinyJS_ExtFunctions.h - TinyJS Library add-on for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#ifndef TinyJS_ExtFunctions_h
#define TinyJS_ExtFunctions_h

#include "../TinyJS.h"

/// Register useful extra/extention functions with the TinyJS interpreter
extern void registerStringExtFunctions(CTinyJS *tinyJS);
extern void registerDoubleExtFunctions(CTinyJS *tinyJS);
extern void registerParseExtFunctions(CTinyJS *tinyJS);
extern void registerExtFunctions(CTinyJS *tinyJS);

#endif  // TinyJS_ExtFunctions_h
