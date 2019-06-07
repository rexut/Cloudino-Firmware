/*
  TinyJS_CDINOBinding.cpp - TinyJS Library add-on for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "TinyJS_CDINOBinding.h"

#ifdef CDINOJS

#include "../CloudinoConf.h"  // for UDP_PORT

#include <Arduino.h>  // for type definitions
#include <IPAddress.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
extern WiFiUDP udp;   // TODO: the symbol udp is in ../CloudinoWeb/initWebServer.cpp
                      //       evaluate #include "../CloudinoWeb.h"

void scCloudinoLocalPost(CScriptVar *v, void *userdata)
{
    //Serial.println("scCloudinoLocalPost");
    SMessageProc *proc = (SMessageProc*)userdata;
    String data=proc->encodePost(v->getParameter("topic")->getString(),v->getParameter("data")->getString());
    String sip=v->getParameter("ip")->getString();
    //Serial.println(sip);

    IPAddress ip=WiFi.localIP();
    if(sip!="undefined")
    {
      ip.fromString(v->getParameter("ip")->getString());
    }else
    {
      ip[3] = 255;
    }
    //Serial.println(ip.toString());
    udp.beginPacket(ip, UDP_PORT);
    udp.print(data);
    udp.endPacket();
}

void scCloudinoPost(CScriptVar *v, void *userdata)
{
    SMessageProc *proc = (SMessageProc*)userdata;
    proc->processMessage(v->getParameter("topic")->getString(),v->getParameter("data")->getString());
}

/*
void scCloudinoPrint(CScriptVar *v, void *userdata)
{
    SMessageProc *proc = (SMessageProc*)userdata;
    proc->logHandler(v->getParameter("text")->getString());
}

void js_trace(CScriptVar *var, SMessageProc *proc, String indentStr, const String &name) {
    proc->logHandler(indentStr+"'"+name+"' = '"+var->getString()+"' "+var->getFlagsAsString());
    String indent = indentStr+" ";
    CScriptVarLink *link = var->firstChild;
    while (link) {
      js_trace(link->var,proc,indent, link->name);
      link = link->nextSibling;
    }
}

void js_scCloudinoDump(CScriptVar *v, void *userdata)
{
    UsrData *data = (UsrData*)userdata;
    CTinyJS *js=data->js;
    SMessageProc *proc=data->proc;
    proc->logHandler("FreeHeap:"+String(ESP.getFreeHeap()));
    js_trace(js->root,proc,"> ","");
}
*/

// ----------------------------------------------- Register Functions
void registerCDINOBinding(CTinyJS *tinyJS, SMessageProc *proc) {
    tinyJS->addNative(F("function Cloudino.localPost(topic,data,ip)"), scCloudinoLocalPost, proc);
    tinyJS->addNative(F("function Cloudino.localBCPost(topic,data)"), scCloudinoLocalPost, proc);
    tinyJS->addNative(F("function Cloudino.post(topic,data)"), scCloudinoPost, proc);
    // tinyJS->addNative(F("function Cloudino.on(topic, funct)"), scCloudinoOn, proc);
    tinyJS->execute(F("Cloudino.print=print;"));
    // tinyJS->addNative(F("function Cloudino.print(text)"), js_print, proc);
    tinyJS->execute(F("Cloudino.dump=dump;"));
    // tinyJS->addNative(F("function Cloudino.dump()"), js_dump, tinyJS);
    tinyJS->execute(F("Cloudino._tp='';Cloudino._msg='';Cloudino._on={};Cloudino.on=function (topic, funct){Cloudino._on[topic]=funct;};"));
    tinyJS->execute(F("Cloudino._onLocal={};Cloudino.onLocal=function (topic, funct){Cloudino._onLocal[topic]=funct;};"));
}

#endif  // CDINOJS
