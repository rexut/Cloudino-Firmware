/*
  CTinyJS__evaluateToJSONResult.cpp - TinyJS Library add-on for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "../TinyJS.h"

String CTinyJS::evaluateToJSONResult(const String &code)
{
  String result;

  evaluateComplex(code).var->getJSON(result);

  return result;
}
