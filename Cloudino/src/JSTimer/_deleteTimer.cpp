/*
  JSTimer/_deleteTimer.cpp - Library for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "../JSTimer.h"

/**
 * Return the next item in the list.
 */
JSTimer::TimerInstance *JSTimer::_deleteTimer(int id)
{
  JSTimer::TimerInstance *prev = NULL;
  JSTimer::TimerInstance *aux = _ini;

  // run over the concatenated list
  while (aux != NULL) {

    // looking for given identifier
    if (aux->id == id) {

      // save next list entry for re-concatenation on end
      JSTimer::TimerInstance *next = aux->next;

      // beeing on head of concatenated list, then ...
      if (prev == NULL) {

        // link list entry point with following entry
        _ini = next;

      } else {

        // link previous with following entry
        prev->next = next;

      }

      // beeing on tail of concatenated list, then ...
      if (next == NULL) {

        // link list exit point with previous entry
        _end = prev;

      }

      // delete given identified entry, return with following entry
      delete aux;
      return next;

    }

    // given identifier was not there, go to next entry
    prev = aux;
    aux = aux->next;

  }

  // empty concatenated list, return with NULL
  return NULL;
}
