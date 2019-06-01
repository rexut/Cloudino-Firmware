/*
  CloudinoWeb/update.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../CloudinoWeb.h"

#ifdef HTTP_UPDATE
String update(String url)
{
  int i, port = 80;
  String host;
  String path;

  // Parse the URL
  if (url.startsWith("http://")) {

    url = url.substring(7);

  } else if (url.startsWith("https://")) {

    url = url.substring(8);
    port = 443;

  }

  i = url.indexOf('/');
  if (i > -1) {

    host = url.substring(0, i);
    path = url.substring(i);

  } else {

    host = url;
    path = "/";
  }

  i = host.indexOf(':');
  if(i > -1) {

    port = host.substring(i + 1).toInt();
    host = host.substring(0, i);

  }

  // Serial.println("Host:" + host);
  // Serial.println("Port:" + String(port));
  // Serial.println("Path:" + path);

  WiFiClient client;
  if (!client.connect(host.c_str(), port)) {
    return "Error: connection failed";
  }

  // This will send the request to the server
  client.print(String("GET ") + path + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");

  int responseCode = 0;

  // Read the Headers
  while (client.connected()) {

    String line = client.readStringUntil('\n');

    if (line == "\r") {

      // Serial.println("headers received");
      break;

    } else {

      if (line.startsWith("HTTP/")) {

         int n = line.indexOf(' ');
         if (n > -1) {
            responseCode = line.substring(n + 1, line.indexOf(' ', n + 1)).toInt();
         }

      }

      // Serial.println("head:" + line);
    }

  }

  if (responseCode != 200) {
    return String() + F("Error: Bad response code:") + String(responseCode);
  }

  WiFiUDP::stopAll();

  uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
  if (!Update.begin(maxSketchSpace)) {
    return F("Error: Initializing update"); // Update.printError(Serial);
  }

  while (client.connected()) {

    uint8 buf[1024];

    while(client.available() > 0) {

      uint ret = client.read(buf, 1024);
      // Serial.write(buf, ret);

      if (Update.write(buf, ret) != ret) {

        // Update.printError(Serial);
        Update.end();
        // client.disconnect();

        return F("Error: Writing data");
      }
    }

    delay(50);
  }

  if (!Update.end(true)) {

    // Update.printError(Serial);
    return F("Error: Ending update");

  }

  return "OK";
}
#endif
