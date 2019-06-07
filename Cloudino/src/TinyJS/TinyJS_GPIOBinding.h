/*
  TinyJS_GPIOBinding.h - TinyJS Library add-on for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#ifndef TinyJS_GPIOBinding_h
#define TinyJS_GPIOBinding_h

#include "../TinyJS.h"

/// Register digital and analog GPIO functions with the TinyJS interpreter
extern void registerGPIOBinding(CTinyJS *tinyJS);

#endif  // TinyJS_GPIOBinding_h
