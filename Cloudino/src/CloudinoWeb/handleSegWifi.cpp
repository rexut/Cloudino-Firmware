/*
  CloudinoWeb/handleSegWifi.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include <ESP8266WiFi.h>

#include "../CloudinoWeb.h"

void handleSegWifi()
{
  String msg;
  String ret;

  if (webserver.hasArg("d")) {

    WiFi.disconnect();
    msg = "Changes Applied";

  }

  if (webserver.hasArg("id")) {

    String id = webserver.arg("id");

    if (webserver.hasArg("pwd")) {

      String pwd = webserver.arg("pwd");
      WiFi.begin(WiFi.SSID(id.toInt()).c_str(), pwd.c_str());

    } else {
      WiFi.begin(WiFi.SSID(id.toInt()).c_str());
    }

    msg = "Changes Applied";

  }

  const char* status[] = {"IDLE_STATUS", "NO_SSID_AVAIL", "SCAN_COMPLETED", "CONNECTED","CONNECT_FAILED", "CONNECTION_LOST", "DISCONNECTED"};
  const char* phymodes[] = {"", "B", "G", "N"};
  const char* boo[] = {"OFF", "ON"};
  const char* auth[] = {"-", "-", "WPA", "-", "WPA2", "WEP", "-", "OPEN", "WPA/WPA2"};

  if (webserver.hasArg("s")) {

    ret += "<header>\n";
    ret += F("<h1>WiFi Scan</h1>\n");
    ret += F("<p>List of availables WiFi Networks</p>\n");
    ret += "</header>\n";
    ret += "<section>\n";
    ret += "<table class=\"table\">\n";
    ret += F("<tr><th>SSID</th><th>RSSI</th><th>Encryption</th><th></th></tr>\n");

    for (int i = 0; i < WiFi.scanNetworks(); ++i) {

      ret += "<tr>";
      ret += "<td>" + String(WiFi.SSID(i)) + "</td>";
      ret += "<td>" + String(WiFi.RSSI(i)) + "</td>";
      ret += "<td>" + String(auth[WiFi.encryptionType(i)]) + "</td>";
      ret += String() + F("<td><input onclick=\"cdino.seg('wifi?id=") + String(i) + "'";

      if(WiFi.encryptionType(i) > 0)
        ret += F("+'&pwd='+prompt('Password','')");

      ret += F(",'wifi',5000);\" type=\"button\" value=\"Connect\"></td>");
      ret += F("</tr>\n");
    }

    ret += "</table>\n";
    ret += addbutton(F("Return"), F("cdino.seg('wifi');"));
    ret += "</section>\n";

    webserver.send(200, "text/html; charset=utf-8", ret);

    return;
  }

  ret += "<header>\n";
  ret += F("<h1>WiFi Status</h1>\n");
  ret += F("<p>The WiFi configuration of the Cloudino Router</p>\n");
  ret += "</header>\n";
  ret += "<section>\n";
  ret += "<table class=\"table\">\n";
  ret += addtr(F("Status"), status[WiFi.status()]);
  ret += addtr(F("SID"), WiFi.SSID());
  ret += addtr(F("Channel"), String(wifi_get_channel()));
  ret += addtr(F("PHY mode"), phymodes[(int)wifi_get_phy_mode()]);
  ret += addtr(F("Auto connect"), boo[wifi_station_get_auto_connect()]);
  ret += addtr(F("IP"), getAddress(WiFi.localIP()));
  ret += addtr(F("MAC"), WiFi.macAddress());
  ret += addtr(F("Mask"), getAddress(WiFi.subnetMask()));
  ret += addtr(F("Gateway"), getAddress(WiFi.gatewayIP()));
  ret += "</table>\n";
  ret += addbutton(F("Reload"), F("cdino.seg('wifi');"));
  ret += addbutton(F("Scan"), F("cdino.seg('wifi?s=1');"));
  ret += addbutton(F("Disconect"), F("cdino.seg('wifi?d=1');"));
  ret += alert(msg);
  ret += "</section>";

  webserver.send(200, "text/html; charset=utf-8", ret);
}
