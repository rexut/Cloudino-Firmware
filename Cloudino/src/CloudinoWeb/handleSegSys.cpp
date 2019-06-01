/*
  CloudinoWeb/handleSegSys.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../EEPROMAnything.h"
#include "../CloudinoWeb.h"

void handleSegSys()
{
  String msg;
  String ret;

  ret += "<header>\n";
  ret += F("<h1>System Tools</h1>\n");
  ret += "</header>\n";

  if (webserver.hasArg("restart")) {

    ret += "Restarting...";

    webserver.send(200, "text/html; charset=utf-8", ret);
    delay(50);

    //ESP.wdtDisable();
    ESP.restart();
    //delay(100);

    return;
  }

#ifdef HTTP_UPDATE
  if (webserver.hasArg("chk_upd")) {

    String ret2 = chk_upd();
    ret += ret2;

    if (ret2.startsWith("New")) {

      ret += "<br>";

      String url = CDINO_UPDURL;
      url = String() + F("cdino.seg('sys?upd_url='+encodeURI('") + url + F("'));");
      ret += addbutton("Update", url.c_str());
    }

    webserver.send(200, "text/html; charset=utf-8", ret);
    return;
  }

  if (webserver.hasArg("upd_url2")) {

    ret += F("<p>Updating...</p>");

    webserver.send(200, "text/html; charset=utf-8", ret);
    return;
  }

  if (webserver.hasArg("upd_url")) {

    String ret2 = update(webserver.arg("upd_url"));

    if (ret2 == "OK") {

      ret += F("Update Success<br>\nYou need to ");
      ret += addbutton(F("Reboot Cloudino"), F("cdino.seg('sys?restart=','sys',3000);"));

      webserver.send(200, "text/html; charset=utf-8", ret);
      return;

    } else {

      ret += ret2;

      webserver.send(200, "text/html; charset=utf-8", ret);
      return;
    }
  }
#endif

  if (webserver.hasArg("freset")) {

    resetEEPROM();
    msg = "Changes Applied";

  }

  if (webserver.hasArg("auth_user")) {

    strcpy(configuration.auth_user, webserver.arg("auth_user").c_str());
    strcpy(configuration.auth_passwd, webserver.arg("auth_passwd").c_str());

    EEPROM_write(0, configuration);

    msg = "Changes Applied";
  }

#ifdef CDINO_ARDUINO
  if (webserver.hasArg("arduino_active")) {

    configuration.arduino_active = webserver.arg("arduino_active").toInt();
    configuration.arduino_gpio = webserver.arg("arduino_gpio").toInt();

    EEPROM_write(0, configuration);

    msg = "Changes Applied";
  }

  ret += "<section>\n";
  ret += F("<p>Arduino Connector Support.</p>\n");
  ret += "<form>\n";
  ret += "<table class=\"table\">\n";
  ret += addtrrad(F("Active"), "arduino_active", configuration.arduino_active);
  ret += addtrinp(F("Reset GPIO"), "number", "arduino_gpio", String(configuration.arduino_gpio), 0, 2);
  ret += "</table>\n";
  ret += addbutton(F("Save"), F("cdino.seg('sys'+cdino.getForm());"));
  ret += "</form>\n";
  ret += "</section>\n";
#endif

  ret += "<section>\n";
  ret += F("<p>Basic Authentication</p>\n");
  ret += "<form>\n";
  ret += "<table class=\"table\">\n";
  ret += addtrinp("User", "text", "auth_user", configuration.auth_user, 0, 20);
  ret += addtrinp("Password", "text", "auth_passwd", configuration.auth_passwd, 0, 20);
  ret += "</table>\n";
  ret += addbutton(F("Save"), F("cdino.seg('sys'+cdino.getForm(document.forms[1]));"));
  ret += "</form>\n";
  ret += "</section>\n";

#ifdef HTTP_UPDATE
  ret += "<section>\n";
  ret += F("<p>Http Firmware Update</p>\n");
  ret += "<form>\n";
  ret += "<table class=\"table\">\n";
  ret += addtr(F("Version"), CDINO_VERSION);
  ret += addtrinp(F("Update URL"), "text", "upd_url", CDINO_UPDURL, 0, 200);
  ret += "</table>\n";
  ret += addbutton(F("Update"), F("cdino.seg('sys?upd_url2=','sys'+cdino.getForm(document.forms[2]),100);"));
  ret += addbutton(F("Check for Updates"), F("cdino.seg('sys?chk_upd=');"));
  ret += "</form>\n";
  ret += "</section>\n";
#endif

  ret += "<section>\n";
  ret += F("<p>Reset Cloudino Connector</p>\n");
  ret += "<form>\n";
  ret += addbutton(F("Reboot Cloudino"), F("cdino.seg('sys?restart=','sys',3000);"));
  ret += addbutton(F("Delete Configurations"), F("cdino.seg('sys?freset=');"));
  ret += "</form>\n";
  ret += "</section>\n";
  ret += alert(msg);

  webserver.send(200, "text/html; charset=utf-8", ret);
}
