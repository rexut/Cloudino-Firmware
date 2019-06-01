/*
  CloudinoWeb/handleSegJSTerm.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../CloudinoWeb.h"

#ifdef JS_SUPPORT
void handleSegJSTerm()
{
  String ret;  

  ret += "<header>\n";
  ret += F("<h1>JavaScript Terminal</h1>\n");
  ret += F("<p>With this option, you can have access to the internal JavaScript Interpreter</p>\n");
  ret += "</header>\n";
  ret += "<section>\n";
  ret += F("<span><input type=\"text\" id=\"term_script\" style=\"width:75%;\" onkeydown=\"if(event.keyCode==13)term_send.click()\"> <input type=\"button\" id=\"term_send\"onclick=\"var idv=cdino.addDiv(term_log);idv.innerHTML='> '+term_script.value;idv=cdino.addDiv(term_log);cdino.getHtml('js',idv,'POST','['+ encodeURIComponent(term_script.value),'< ');term_script.value='';term_log.scrollTop=term_log.scrollHeight;\" value=\"Send\"></span>\n");
  ret += F("<div id=\"term_log\" style=\"width:100%; height:250px; overflow: scroll; padding: 5px 0px 0px 7px; color:#E63A4A; border-style: double; background-color: #FFFFFF; font-size: 12px; font-family: monospace;\"></div>\n");
  ret += "</section>\n";

  webserver.send(200, "text/html; charset=utf-8", ret); 
}
#endif
