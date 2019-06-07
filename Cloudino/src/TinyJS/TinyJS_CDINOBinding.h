/*
  TinyJS_CDINOBinding.h - TinyJS Library add-on for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#ifndef TinyJS_CDINOBinding_h
#define TinyJS_CDINOBinding_h

#include "../TinyJS.h"
#include "../TinyJS_Firmware.h"

#ifdef CDINOJS

#include "../SMessageProc.h"

/// Register Cloudino message processing functions with the TinyJS interpreter
extern void registerCDINOBinding(CTinyJS *tinyJS, SMessageProc *proc);

#endif  // CDINOJS

#endif  // TinyJS_CDINOBinding_h
