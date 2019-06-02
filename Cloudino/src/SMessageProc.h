/*
  SMessageProc.h - MessageProcessor for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#ifndef SMessageProc_h
#define SMessageProc_h

#include <Arduino.h>  // for type definitions

const char SEP='|';   // field separation mark
const char MSEP='M';  // Message (starting) mark, followed by length int (<255)
const char SSEP='S';  // String mark, followed by length int (<65535)
const char LSEP='L';  // Log (starting) mark, followed by length int (<65535)

/*****************************************************************************

|L18|hello %d, XAVIER10
  `v `v---------------´
   :  :
   :  `-> txt = "hello %d, XAVIER10" <-- SMessageProc::handleStreamMessages::txt
   `----> txt length = 18            <-- SMessageProc::handleStreamMessages::x


|M5|helloS6|world!
  : `-v-´ : `--v-´
  :   :   :    :
  :   :   :    `-> msg = "world!" <-- SMessageProc::handleStreamMessages::msg
  :   :   `------> msg length = 6 <-- SMessageProc::handleStreamMessages::y
  :   :
  :   `-> topic = "hello"  <-- SMessageProc::handleStreamMessages::topic
  `-----> topic length = 5 <-- SMessageProc::handleStreamMessages::x

|M3|ledS2|on
  : `v´ : `v
  :  :  :  :
  :  :  :  `-> msg = "on"     <-- SMessageProc::handleStreamMessages::msg
  :  :  `----> msg length = 2 <-- SMessageProc::handleStreamMessages::y
  :  :
  :  `--> topic = "led"    <-- SMessageProc::handleStreamMessages::topic
  `-----> topic length = 3 <-- SMessageProc::handleStreamMessages::x

*****************************************************************************/

class SMessageProc
{
  protected:

    typedef void (*MessageFunction)(String, String);
    typedef void (*LogFunction)(String);

  private:

    MessageFunction messageHandler = NULL;
    MessageFunction serverMessageHandler = NULL;
    MessageFunction localMessageHandler = NULL;

    boolean waitStream(Stream &stream);

  public:

    // send message to Arduino and JS
    void post(String topic, String message);

    String encodePost(String topic, String data);
    String encodeLog(String log);

    void handleMessages();                      //Handle Messages from Serial
    void handleLocalMessages(Stream &stream);   //Handle Messages from UDP
    void handleStreamMessages(Stream &stream,   //Generic Handle Messages
            MessageFunction msgHandler,
            LogFunction logHandler);

    void onMessage(MessageFunction fn);
    void onServerMessage(MessageFunction fn);
    void onLocalMessage(MessageFunction fn);
    void onLog(LogFunction fn);

    // process received message from the Arduino to the server
    void processMessage(String topic, String msg);

    // process message received from the server for JS
    void processServerMessage(String topic, String msg);

    // process message received from the local network for JS
    void processLocalMessage(String topic, String msg);

    void on(String topic, String fn);
    void clear();

    LogFunction logHandler;
};

extern SMessageProc proc;

#endif  // SMessageProc_h
