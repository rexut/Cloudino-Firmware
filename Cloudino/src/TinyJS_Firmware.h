/*
  TinyJS_Firmware.h - TinyJS Library firmware integration for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#ifndef TinyJS_Firmware_h
#define TinyJS_Firmware_h

#include "TinyJS.h"
#include "JSTimer.h"

#define CDINOJS

#ifdef CDINOJS
#include "SMessageProc.h"
#endif

struct UsrData
{
  CTinyJS *js;
  JSTimer *timer;
#ifdef CDINOJS
  SMessageProc *proc;
#endif
};

/// Register backend functions into the firmware with the TinyJS interpreter
#ifdef CDINOJS
extern void registerFirmware(CTinyJS *tinyJS, JSTimer *timer, SMessageProc *proc);
#endif
#ifndef CDINOJS
extern void registerFirmware(CTinyJS *tinyJS, JSTimer *timer);
#endif

#endif  // TinyJS_Firmware_h
