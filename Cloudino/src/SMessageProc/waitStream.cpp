/*
  SMessageProc/waitStream.cpp - MessageProcessor for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "../SMessageProc.h"

boolean SMessageProc::waitStream(Stream &stream)
{
  unsigned long time = millis();

  while (stream.available() == 0 && millis() - time < 1000) {
    delay(1);
  }

  return stream.available() > 0;
}
