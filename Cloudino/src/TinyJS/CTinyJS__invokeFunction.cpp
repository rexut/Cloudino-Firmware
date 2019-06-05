/*
  CTinyJS__invokeFunction.cpp - TinyJS Library add-on for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "../TinyJS.h"

#if 0
void CTinyJS::invokeFunction(String function, String param)
{
  bool exec=true;

  Serial.println("invokeFunction:"+function+" p:"+param);
  CScriptVarLink f = evaluateComplex(function);
  Serial.println("evaluation passed");

  Serial.println(f.name);
  Serial.println(f.var->getString());

  CScriptVar *obj = new CScriptVar(param);
  functionCall(exec, &f, obj);
  Serial.println("call passed");

  delete obj;
}
#endif
