/*
  JSTimer/setGlobalCallBack.cpp - Library for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "../JSTimer.h"

void JSTimer::setGlobalCallBack(timer_global_callback fn)
{
  funct = fn;
}
