/*
  SMessageProc/onLog.cpp - MessageProcessor for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "../SMessageProc.h"

void SMessageProc::onLog(LogFunction fn)
{
  logHandler = fn;
}
