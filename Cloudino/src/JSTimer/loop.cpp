/*
  JSTimer/loop.cpp - Library for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "../JSTimer.h"

void JSTimer::loop()
{
  JSTimer::TimerInstance *aux=_ini;

  // run over the concatenated list
  while (aux != NULL) {

    unsigned long t = millis();

    // check duration time since last loop
    if (t - aux->lltime >= aux->time) {

      // reach required trigger time, execute given JS function
      funct(aux->tcbTimed);

      // increment last loop time
      aux->lltime += aux->time;

      // decrement required number counter
      if (aux->num > 0) aux->num--;
    }

    // check end of numbered triggers
    if (aux->num == 0) {

      // reach end of numbered triggers, delete timer entry and ...
      timer_callback tcbEnd = aux->tcbNumbered;
      aux = _deleteTimer(aux->id);  // ... go to next entry and ...

      // ... execute given end of numbered trigger JS function if there was any
      if (tcbEnd.length() > 0) funct(tcbEnd);

    } else {

      // go to next entry
      aux = aux->next;

    }
  }
}
