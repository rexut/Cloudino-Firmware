/*
  JSTimer/setTimeout.cpp - Library for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "../JSTimer.h"

int JSTimer::setTimeout(unsigned long d, timer_callback fd) {
  return setTimer(d, fd, 1);
}
