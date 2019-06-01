/*
  CloudinoWeb/handleRoot.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "../CloudinoWeb.h"

const char home[] PROGMEM ="<html><head>\n\
<meta charset=\"utf-8\">\n\
<title>Cloudino</title>\n\
<meta name=\"viewport\" content=\"width=device-width\">\n\
<style>html,button,input,select,textarea{color:#222}\n\
body{font-size:1em;line-height:1.4;margin:0}\n\
::-moz-selection{background:#b3d4fc;text-shadow:none}\n\
::selection{background:#b3d4fc;text-shadow:none}\n\
hr{display:block;height:1px;border:0;border-top:1px solid #ccc;margin:1em 0;padding:0}\n\
img{vertical-align:middle}\n\
fieldset{border:0;margin:0;padding:0}\n\
textarea{resize:vertical}\n\
body{font:16px/26px Helvetica,Helvetica Neue,Arial}\n\
.wrapper{width:90%;margin:0 5%}\n\
.header-container{border-bottom:20px solid #BE3A46}\n\
.footer-container,.main aside{border-top:20px solid #BE3A46}\n\
.header-container,.footer-container,.main aside{background:#E63A4A}\n\
.title{color:#fff}\n\
nav ul{margin:0;padding:0}\n\
nav a{display:block;margin-bottom:10px;padding:15px 0;text-align:center;text-decoration:none;font-weight:700;color:#fff;background:#BE3A46}\n\
nav a:hover,nav a:visited{color:#fff}\n\
nav a:hover{text-decoration:underline}\n\
.main{padding:30px 0}\n\
.main article h1{font-size:2em;color:#E63A4A;}\n\
.main aside{color:#fff;padding:0 5% 10px}\n\
.footer-container *{color:#FFF;letter-spacing:1px}\n\
.footer-container{width:100%;position_:fixed;bottom:0;}\n\
.footer-container footer{text-align:center}\n\
footer a{padding:5px 20px 0;display:inline-block;font-weight:bold}\n\
footer span{ display:block;font-size:11px}\n\
#term_log * {margin: 0px -5px;}\n\
@media only screen and (min-width: 480px) {\n\
nav a{float:left;width:27%;margin:0 1.7%;padding:25px 2%;margin-bottom:0}\n\
nav li:first-child a{margin-left:0}\n\
nav li:last-child a{margin-right:0}\n\
nav ul li{display:inline}\n\
.alert{border-color: #1C1F1F;background-color: #E63A4A;color: whitesmoke;border: 2px;padding: 8;border-style: dashed;font-size: medium;}\n\
@media only screen and (min-width: 768px) {\n\
.header-container,.main aside{-webkit-box-shadow:0 5px 10px #aaa;-moz-box-shadow:0 5px 10px #aaa;box-shadow:0 5px 10px #aaa}\n\
.title{float:left}\n\
nav{float:right;width:38%}\n\
.main article{float:left;width:60%}\n\
.main aside{float:right;width:28%}\n\
}\n\
@media only screen and (min-width: 1140px) {\n\
.wrapper{width:1026px;margin:0 auto}\n\
}\n\
.clearfix:before,.clearfix:after{content:\" \";display:table}\n\
.clearfix:after{clear:both}\n\
.clearfix{*zoom:1}\n\
table{width:100%;border-collapse:collapse}\n\
tbody tr:nth-child(odd){background:rgba(230,58,74,.1);}\n\
input[type=\"button\"],input[type=\"submit\"]{width:100px;margin:5px;}\n\
input[type=\"text\"]{width:250px}\n\
.sidebar-nav{margin:0;padding:0;list-style:none}\n\
.sidebar-nav li{text-indent:20px;line-height:40px}\n\
.sidebar-nav li a{display:block;text-decoration:none;color:#FFF;}\n\
.sidebar-nav li a:hover{background:rgba(255,255,255,0.2)}</style><script type=\"text/javascript\">\n\
var cdino = {getHtml:function(url,node,method,data,prefix){var xmlhttp;if (window.XMLHttpRequest){xmlhttp=new XMLHttpRequest();}else{xmlhttp=new ActiveXObject(\"Microsoft.XMLHTTP\");}\n\
xmlhttp.onreadystatechange=function(){if (xmlhttp.readyState==4 && xmlhttp.status==200){if(node===null)return;if(typeof node === 'string'){document.getElementById(node).innerHTML = (prefix?prefix:\"\")+xmlhttp.responseText;}else{node.innerHTML = (prefix?prefix:\"\")+xmlhttp.responseText;}}};\n\
xmlhttp.open(!method?\"GET\":method,url,true);xmlhttp.send(data);},\n\
invoke:function(func,timeout,inter){setTimeout(func,timeout);if(inter)window.setInterval(func,inter);},\n\
seg:function(seg,next,time){if(next){cdino.invoke(function(){cdino.seg(next);},time?time:1000);}cdino.getHtml('seg/'+seg,'content');},\n\
getForm:function(form){if(!form)form=document.forms[0];if(form.checkValidity()){var ret=\"\";var arr=form.getElementsByTagName('input');for (x=0; x<arr.length; ++x){var inp=arr[x];if(inp.name && (inp.type!='radio' || inp.checked==true))ret+=\"&\"+inp.name+\"=\"+inp.value;}if(ret.length>0)return \"?\"+ret.substr(1);}},\n\
addDiv:function(node){var idv=document.createElement('div');node.appendChild(idv);return idv;},\n\
};</script>\n\
</head><body>\n\
<div class=\"header-container\">\n\
<header class=\"wrapper clearfix\">\n\
<a href=\"/\"><div class=\"title\"><svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" version=\"1.1\" x=\"0px\" y=\"0px\" width=\"50px\" height=\"70px\" viewBox=\"-413.2 0 200 200\" xml:space=\"preserve\"><style>.style0{fill:  #FFFFFF;}.style1{fill:  #FFFFFF;}.style2{fill:  #FFFFFF;}.style3{fill:  #E63A4A;}.style4{fill:  #FFFFFF;}.style5{fill:  #FFFFFF;}</style><g><path d=\"M-298.6 3.7c-4.3 0-8 2.4-9.8 6h-2.8c-5.1 0-10 1.6-13.8 4.5c-4.4 3.4-6.8 8.1-6.8 13.3v14.7h9.8V27.5 c0-4.9 5.7-8.1 10.8-8.1h2.6c1.8 3.8 5.6 6.5 10.1 6.5c6.1 0 11.1-5 11.1-11.1C-287.5 8.6-292.5 3.7-298.6 3.7z M-298.6 18 c-1.8 0-3.2-1.4-3.2-3.2c0-1.8 1.4-3.2 3.2-3.2c1.8 0 3.2 1.4 3.2 3.2C-295.4 16.6-296.9 18-298.6 18z\" class=\"style5\"></path><g><path d=\"M-368.7 152.1c1.5-7.9 3.6-17.1 6.2-26.7l-23-5.7c-2.8 10.4-5.1 20.5-6.8 29.5 c-11.1 3.7-19.2 14.2-19.2 26.5h55.9C-355.6 165.8-360.9 157-368.7 152.1z\" class=\"style1\"></path><path d=\"M-261.5 149.3c-1.9-10.1-4.5-21.7-7.9-33.5l-23.1 5.8c3.1 10.9 5.6 21.4 7.3 30.4 c-7.9 4.9-13.2 13.7-13.2 23.7h55.9C-242.5 163.5-250.4 153-261.5 149.3z\" class=\"style1\"></path></g><path d=\"M-276.3 93.9c-5.8-16.3-12.1-29.6-18.7-39.5c-9.7-14.6-20.5-22-31.9-22s-22.2 7.4-31.9 22 c-6.6 9.9-12.8 23.1-18.7 39.5c-21 4.8-34.6 12.5-34.6 21.2c0 14.6 38.1 26.3 85.2 26.3c47 0 85.2-11.8 85.2-26.3 C-241.7 106.4-255.3 98.7-276.3 93.9z\" class=\"style2\"></path><circle cx=\"-327.2\" cy=\"79.7\" r=\"20.8\" class=\"style3\"></circle><path d=\"M-327.2 90.8c-6.1 0-11.1-5-11.1-11.1c0-6.1 5-11.1 11.1-11.1s11.1 5 11.1 11.1 C-316.1 85.8-321.1 90.8-327.2 90.8z\" class=\"style4\"></path></g></svg></div><h1 class=\"title\">Cloudino</h1></a>\n\
</header>\n\
</div>\n\
<div class=\"main-container\">\n\
<div class=\"main wrapper clearfix\">\n\
<aside id=\"menu\"></aside>\n\
<article id=\"content\"><h1>Welcome to Cloudino Platform</h1>\n\
<h3>An easy way to connect your Arduino to the Cloud</h3>\n\
\n\
<section>\n\
<p>Cloudino is an Internet of Things Platform (Cloud Connector) that allows you to fully connect to the cloud, differents MCU platforms (Atmel AVR, Microchip PIC, etc.) in a very easy and transparent way.</p>\n\
</section>\n\
<footer>\n\
<p>Cloidino is developed and maintained by INFOTEC (Public Research Center of CONACYT) as a Open Source and Open Hardware Platform</p>\n\
</footer></article>\n\
</div>\n\
</div>\n\
<div class=\"footer-container\">\n\
<footer class=\"wrapper\">\n\
<a href=\"http://cloudino.cc/\">cloudino.cc</a> <a href=\"http://infotec.mx/\">infotec.mx</a> <span>Cloudino © 2015 INFOTEC</span>\n\
</footer>\n\
</div>\n\
<script type=\"text/javascript\">cdino.getHtml('seg/menu','menu');</script>\n\
</body></html>\n\
";

void handleRoot()
{
  webserver.send_P(200, "text/html; charset=utf-8", home);
}
