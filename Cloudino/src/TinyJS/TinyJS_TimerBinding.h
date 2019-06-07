/*
  TinyJS_TimerBinding.h - TinyJS Library add-on for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#ifndef TinyJS_TimerBinding_h
#define TinyJS_TimerBinding_h

#include "../TinyJS.h"
#include "../JSTimer.h"

/// Register JSTimer access functions with the TinyJS interpreter
extern void registerTimerBinding(CTinyJS *tinyJS, JSTimer *timer);

#endif  // TinyJS_TimerBinding_h
