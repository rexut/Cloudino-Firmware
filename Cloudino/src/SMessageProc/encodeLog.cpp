/*
  SMessageProc/encodeLog.cpp - MessageProcessor for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "../SMessageProc.h"

String SMessageProc::encodeLog(String log)
{
  String ret;   // |Lx|<text>

  ret += SEP;
  ret += LSEP;
  ret += String(log.length());    // TODO: length() && 0xFFFF

  ret += SEP;
  ret += log;

  return ret;
}
