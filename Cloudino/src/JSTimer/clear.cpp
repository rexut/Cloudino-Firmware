/*
  JSTimer/clear.cpp - Library for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "../JSTimer.h"

void JSTimer::clear()
{
  JSTimer::TimerInstance *aux = _ini;

  // run over the concatenated list
  while (aux != NULL) {

    // save current list entry for deletion on end
    JSTimer::TimerInstance *tmp = aux;

    // go to next entry
    aux = aux->next;

    // delete current list entry
    delete tmp;
  }

  // reset list entry point, exit point, and accumulator
  _ini = NULL;
  _end = NULL;
  _idc = 0;
}
