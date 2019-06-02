/*
  SMessageProc.cpp - MessageProcessor for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "../CloudinoConf.h"
#include "../SMessageProc.h"

//|L|17|hello %d, XAVIER10
//|M5|helloS6|world!
//|M3|ledS2|on

void SMessageProc::handleMessages()
{
  handleStreamMessages(Serial,messageHandler,logHandler);
}

void SMessageProc::handleLocalMessages(Stream &stream)
{
  handleStreamMessages(stream,localMessageHandler,logHandler);
}

void SMessageProc::handleStreamMessages(Stream &stream, MessageFunction msgHdler, LogFunction logHdler)
{
  if(stream.available())
  {
    uint8_t d=stream.read();
    //stream.println("D:"+String(d));
    if(d==SEP)
    {
      if(waitStream(stream))
      {
        d=stream.read();
        if(d==MSEP)
        {
          uint8_t x=stream.parseInt();
          if(waitStream(stream))
          {
            if(x>0 && stream.read()==SEP)
            {
              char topic[x+1];
              stream.readBytes(topic, x);
              topic[x]=0;                 //cerrar el string
              //stream.println(topic);
              if(waitStream(stream) && stream.read()==SSEP)
              {
                uint16_t y=stream.parseInt();
                if(waitStream(stream) && stream.read()==SEP)
                {
                  char msg[y+1];
                  stream.readBytes(msg, y);
                  msg[y]=0;                 //cerrar el string   
                  //stream.println(msg);
                  if(messageHandler!=NULL)
                  {
                    msgHdler(topic,msg);
                  }
                }
              }
            }
          }
        }else if(d==LSEP)
        {
          uint16_t x=stream.parseInt();
          if(waitStream(stream))
          {
            if(x>0 && stream.read()==SEP)
            {
              char txt[x+1];
              stream.readBytes(txt, x);
              txt[x]=0;                 //cerrar el string
              logHdler(txt);
            }
          }
        }
      }   
    }
  }        
}

String SMessageProc::encodePost(String topic, String data)
{
    String ret;
    ret+=SEP;
    ret+=MSEP;
    ret+=String(topic.length());  
    ret+=SEP;  
    ret+=topic;    
    ret+=SSEP;
    ret+=String(data.length());  
    ret+=SEP;
    ret+=data;   
    return ret; 
}

String SMessageProc::encodeLog(String log)
{
  String ret;
  ret+=SEP;
  ret+=LSEP;
  ret+=String(log.length());  
  ret+=SEP;  
  ret+=log;    
  return ret; 
}

/**
 * Post Message to Arduino or JavaScript
 */
void SMessageProc::post(String topic, String data)
{
  //TODO
  //Verificar si hay o no arduino
#ifdef CDINO_ARDUINO   
  if(configuration.arduino_active)
  {
    Serial.print(encodePost(topic,data));
  }
#endif  

  //de lo contrario enviar a Javascript
  processServerMessage(topic,data);
}

void SMessageProc::onMessage(MessageFunction fn)
{
  messageHandler=fn;
}

void SMessageProc::onServerMessage(MessageFunction fn)
{
  serverMessageHandler=fn;
}

void SMessageProc::onLocalMessage(MessageFunction fn)
{
  localMessageHandler=fn;
}

void SMessageProc::onLog(LogFunction fn)
{
  logHandler=fn;
}

boolean SMessageProc::waitStream(Stream &stream)
{
  unsigned long time=millis();
  while(stream.available()==0 && millis()-time<1000){delay(1);}
  return stream.available()>0;
}

void SMessageProc::processMessage(String topic, String msg)
{
  messageHandler(topic,msg);
}

void SMessageProc::processServerMessage(String topic, String msg)
{
  serverMessageHandler(topic,msg);
}

void SMessageProc::processLocalMessage(String topic, String msg)
{
  localMessageHandler(topic,msg);
}

void SMessageProc::clear()
{
}

SMessageProc proc;
