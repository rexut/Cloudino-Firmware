/*
  TinyJS_RCSwitchBinding.h - TinyJS Library add-on for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#ifndef TinyJS_RCSwitchBinding_h
#define TinyJS_RCSwitchBinding_h

#include "../CloudinoConf.h"

#include "../TinyJS.h"

#ifdef RCSWITCH_SUPPORT

/// Register radio-control switch functions with the TinyJS interpreter
extern void registerRCSwitchBinding(CTinyJS *tinyJS);

#endif  // RCSWITCH_SUPPORT

#endif  // TinyJS_RCSwitchBinding_h
