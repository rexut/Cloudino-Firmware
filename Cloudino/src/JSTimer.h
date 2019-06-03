/*
  JSTimer.h - Library for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#ifndef JSTimer_h
#define JSTimer_h

#include <Arduino.h>  // for type definitions

class JSTimer
{
  protected:

    int _idc = 0;     // accumulation of IDs

    typedef String timer_callback;
    typedef void (*timer_global_callback)(timer_callback);

    timer_global_callback funct;

    struct TimerInstance
    {
      TimerInstance(unsigned long time, timer_callback fnTimed,
                    int num, timer_callback fnNumbered)
      : time(time)
      , tcbTimed(fnTimed)
      , num(num)
      , tcbNumbered(fnNumbered)
      {
        lltime = millis();
      }

      int id;   // identifier and next instance pointer
      TimerInstance *next = NULL;;

      unsigned long lltime = 0;   // last loop time

      unsigned long time = 0;     // trigger time
      timer_callback tcbTimed;    // trigger callback function

      int num;                    // number of triggers
      timer_callback tcbNumbered; // numbered trigger callback function
    };

    TimerInstance *_ini = NULL;
    TimerInstance *_end = NULL;

    TimerInstance *_deleteTimer(int id);

  public:

    JSTimer();
    void setGlobalCallBack(timer_global_callback fn);

    // this function must be called inside the Arduino super loop
    void loop();

    // call JS function fd() every d milliseconds
    int setInterval(unsigned long d, timer_callback fd);

    // call JS function fd() once after d milliseconds
    int setTimeout(unsigned long d, timer_callback fd);

    // call JS function fd() every d milliseconds for n times
    int setTimer(unsigned long d, timer_callback fd, int n);

    // call JS function fd() every d milliseconds for n times
    // and the end call JS function fn()
    int setTimer(unsigned long d, timer_callback fd,
                 int n, timer_callback fn);

    // destroy the specified timer instance
    void deleteTimer(int id);

    // destroy all timer instances
    void clear();
};

#endif  // JSTimer_h
