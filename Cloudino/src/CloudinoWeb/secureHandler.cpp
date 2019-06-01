/*
  CloudinoWeb/secureHandler.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../CloudinoWeb.h"

std::function<void(void)> secureHandler(std::function<void(void)> handleFunc)
{
  if (configuration.auth_user[0] != 0) {

    handleFunc = [handleFunc]() {

      if (!webserver.authenticate(configuration.auth_user, configuration.auth_passwd)) {
        return webserver.requestAuthentication();
      }

      handleFunc();
    };

  }

  return handleFunc;
}
