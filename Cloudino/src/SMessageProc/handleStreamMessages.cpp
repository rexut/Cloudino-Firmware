/*
  SMessageProc/handleStreamMessages.cpp - MessageProcessor for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "../SMessageProc.h"

void SMessageProc::handleStreamMessages(Stream &stream,
        MessageFunction msgHandler, LogFunction logHandler)
{
  if (stream.available()) {

    uint8_t d = stream.read();

    // stream.println("D:" + String(d));

    if (d == SEP) {

      if (waitStream(stream)) {

        d = stream.read();

        if (d == MSEP) {        // Message (starting) mark

          uint8_t x = stream.parseInt();

          if (waitStream(stream)) {

            if (x > 0 && stream.read() == SEP) {

              char topic[x + 1];

              stream.readBytes(topic, x);
              topic[x] = 0;     // close the string

              // stream.println(topic);

              if (waitStream(stream) && stream.read() == SSEP) {

                uint16_t y = stream.parseInt();

                if (waitStream(stream) && stream.read() == SEP) {

                  char msg[y + 1];

                  stream.readBytes(msg, y);
                  msg[y] = 0;   // close the string

                  // stream.println(msg);

                  if (messageHandler != NULL) {

                    msgHandler(topic, msg);

                  }

                }
              }
            }
          }

        } else if (d == LSEP) { // Log (starting) mark

          uint16_t x = stream.parseInt();

          if (waitStream(stream)) {

            if (x > 0 && stream.read() == SEP) {

              char txt[x + 1];

              stream.readBytes(txt, x);
              txt[x] = 0;       // close the string

              logHandler(txt);

            }
          }

        }
      }
    }
  }
}
