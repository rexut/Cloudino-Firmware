/*
  JSTimer/setTimer.cpp - Library for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "../JSTimer.h"

int JSTimer::setTimer(unsigned long d, timer_callback fd, int n)
{
  return setTimer(d, fd, n, "");
}

int JSTimer::setTimer(unsigned long d, timer_callback fd,
                      int n, timer_callback fn)
{
  // create a new JS timer instance
  JSTimer::TimerInstance *inst = new JSTimer::TimerInstance(d, fd, n, fn);

  // allocate and accumulate the new identifier
  inst->id = _idc;
  _idc++;

  // insert the new JS timer instance into the concatenated list at ...
  if (_ini == NULL) {

    // ... head of concatenated list in case of an fresh empty list
    _ini = inst;
    _end = inst;

  } else {

    // ... tail of concatenated list in case of already filled list
    _end->next = inst;
    _end = inst;

  }

  // return with the new assigned timer identifier
  return inst->id;
}
