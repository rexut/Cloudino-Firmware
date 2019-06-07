/*
  TinyJS_DHT11Binding.cpp - TinyJS Library add-on for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "TinyJS_DHT11Binding.h"
#include "TinyJS_Helper.h"

// #define DHTLIB_OK              0
#define DHTLIB_ERROR_CHECKSUM -1
#define DHTLIB_ERROR_TIMEOUT  -2

void scDHT11Read(CScriptVar *c, void *) {
    int pin = c->getParameter("pin")->getInt();
    CScriptVar *ret=c->getReturnVar();

    // BUFFER TO RECEIVE
    uint8_t bits[5];
    uint8_t cnt = 7;
    uint8_t idx = 0;

    // EMPTY BUFFER
    for (int i=0; i< 5; i++) bits[i] = 0;

    // REQUEST SAMPLE
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delay(18);
    digitalWrite(pin, HIGH);
    delayMicroseconds(40);
    pinMode(pin, INPUT);

    // ACKNOWLEDGE or TIMEOUT
    unsigned int loopCnt = 10000;
    while(digitalRead(pin) == LOW)
    {
      if (loopCnt-- == 0)
      {
        addIntChild(ret,"err",DHTLIB_ERROR_TIMEOUT);
        return;
      }
    }

    loopCnt = 10000;
    while(digitalRead(pin) == HIGH)
    {
      if (loopCnt-- == 0)
      {
        addIntChild(ret,"err",DHTLIB_ERROR_TIMEOUT);
        return;
      }
    }

    // READ OUTPUT - 40 BITS => 5 BYTES or TIMEOUT
    for (int i=0; i<40; i++)
    {
      loopCnt = 10000;
      while(digitalRead(pin) == LOW)
      {
        if (loopCnt-- == 0)
        {
          addIntChild(ret,"err",DHTLIB_ERROR_TIMEOUT);
          return;
        }
      }

      unsigned long t = micros();

      loopCnt = 10000;
      while(digitalRead(pin) == HIGH)
      {
        if (loopCnt-- == 0)
        {
          addIntChild(ret,"err",DHTLIB_ERROR_TIMEOUT);
          return;
        }
      }

      if ((micros() - t) > 40) bits[idx] |= (1 << cnt);
      if (cnt == 0)   // next byte?
      {
        cnt = 7;      // restart at MSB
        idx++;        // next byte!
      }
      else cnt--;
    }

    // WRITE TO RIGHT VARS
    // as bits[1] and bits[3] are allways zero they are omitted in formulas.
    addIntChild(ret,F("humidity"),bits[0]);
    addIntChild(ret,F("temperature"),bits[2]);

    uint8_t sum = bits[0] + bits[2];

    if (bits[4] != sum)
    {
      addIntChild(ret,"err",DHTLIB_ERROR_CHECKSUM);
      return;
    }
    // return DHTLIB_OK;
}

// ----------------------------------------------- Register Functions
void registerDHT11Binding(CTinyJS *tinyJS) {
    tinyJS->addNative(F("function DHT11.read(pin)"), scDHT11Read, tinyJS); // Get DHT11 Values
}
