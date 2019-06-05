/*
  CTinyJS__invokeFunction.cpp - TinyJS Library add-on for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "../TinyJS.h"

#if 0
bool CTinyJS::functionCall(CScriptVar *function)
{
  bool exec=true;

  CScriptVarLink *link = new CScriptVarLink(function);
  functionCall(exec, link, 0);

  delete link;
  return exec;
}
#endif
