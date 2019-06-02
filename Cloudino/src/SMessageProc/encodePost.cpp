/*
  SMessageProc/encodePost.cpp - MessageProcessor for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "../SMessageProc.h"

String SMessageProc::encodePost(String topic, String data)
{
  String ret;   // |Mx|<topic>Sy|<string>

  ret += SEP;
  ret += MSEP;
  ret += String(topic.length());  // TODO: length() && 0xFF

  ret += SEP;
  ret += topic;
  ret += SSEP;
  ret += String(data.length());   // TODO: length() && 0xFFFF

  ret += SEP;
  ret += data;

  return ret;
}
