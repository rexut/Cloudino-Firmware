/*
  TinyJS_TimerBinding.cpp - TinyJS Library add-on for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "TinyJS_TimerBinding.h"

void scTimerSetInterval(CScriptVar *v, void *userdata)
{
    JSTimer *timer = (JSTimer*)userdata;
    int ret=timer->setInterval(v->getParameter("time_ms")->getLong(),v->getParameter("funct")->getString());
    v->getReturnVar()->setInt(ret);
}

void scTimerClearTimer(CScriptVar *v, void *userdata)
{
    JSTimer *timer = (JSTimer*)userdata;
    timer->deleteTimer(v->getParameter("id")->getInt());
}

void scTimerSetTimeout(CScriptVar *v, void *userdata)
{
    JSTimer *timer = (JSTimer*)userdata;
    int ret=timer->setTimeout(v->getParameter("time_ms")->getLong(),v->getParameter("funct")->getString());
    v->getReturnVar()->setInt(ret);
}

// ----------------------------------------------- Register Functions
void registerTimerBinding(CTinyJS *tinyJS, JSTimer *timer) {
    tinyJS->addNative(F("function Timer.setInterval(funct,time_ms)"), scTimerSetInterval, timer);
    tinyJS->addNative(F("function Timer.clearInterval(id)"), scTimerClearTimer, timer);
    tinyJS->addNative(F("function Timer.setTimeout(funct,time_ms)"), scTimerSetTimeout, timer);
    tinyJS->execute(F("Timer.clearTimeout=Timer.clearInterval;"));
}
