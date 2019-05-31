/*
  EEPROMAnything.h - EEPROM Library for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

template <class T> int EEPROM_clean(int ee, const T& value)
{
    int s=sizeof(value);
    EEPROM.begin(s+ee);
    unsigned int i;
    for (i = 0; i < s; i++)
          EEPROM.write(ee++, 0);
    EEPROM.commit();
    EEPROM.end();
    return i;
}

template <class T> int EEPROM_write(int ee, const T& value, int ext=0)
{
    EEPROM.begin(sizeof(value)+ee+ext);
    const byte* p = (const byte*)(const void*)&value;
    unsigned int i;

    //Serial.print("ee:"+String(ee)+" "+String(sizeof(value)));
    
    for (i = 0; i < sizeof(value); i++)
          EEPROM.write(ee++, *p++);
    EEPROM.commit();
    EEPROM.end();
    return i;
}

template <class T> int EEPROM_read(int ee, T& value)
{
    EEPROM.begin(sizeof(value)+ee);
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          *p++ = EEPROM.read(ee++);
    EEPROM.end();   
    return i;
}

String fileWrite(String name, String content)
{
    File file = SPIFFS.open(name, "w");
    if(file)file.print(content);
    if(file)file.close();  
}

String fileRead(String name){
  //read file from SPIFFS and store it as a String variable
  File file = SPIFFS.open(name.c_str(), "r");
  if (!file) {
    return "";
  }
  else {    
    int fileSize = file.size();
    char buf[fileSize+1];
    file.read((uint8_t *)buf, fileSize);
    file.close();
    buf[fileSize]=0;
    return String(buf);
  }
  
}


