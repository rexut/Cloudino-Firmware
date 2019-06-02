/*
  SMessageProc/post.cpp - MessageProcessor for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "../CloudinoConf.h"
#include "../SMessageProc.h"

/**
 * Post Message to Arduino or JavaScript
 */
void SMessageProc::post(String topic, String data)
{
  //TODO: verify whether or not there is Arduino
#ifdef CDINO_ARDUINO
  if(configuration.arduino_active)
  {
    Serial.print(encodePost(topic, data));
  }
#endif

  // ... otherwise send to JS
  processServerMessage(topic, data);
}
