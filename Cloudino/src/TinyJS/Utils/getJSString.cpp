/*
 * TinyJS
 *
 * A single-file Javascript-alike engine
 *
 * - Common utility functions
 *
 * Authored By Gordon Williams <gw@pur3.co.uk>
 * (https://github.com/gfwilliams/tiny-js)
 *
 * Ported to ESP8266 - Arduino by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com
 * Nov 2015
 *
 * Copyright (C) 2009 Pur3 Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "../Utils.h"

String getJSString(const String &str)
{
  String nStr = str;

  for (unsigned int i = 0; i < nStr.length(); i++) {

    const char *replaceWith = "";
    bool replace = true;

    switch (nStr.charAt(i)) {

      case '\\':
        replaceWith = "\\\\";
	break;

      case '\n':
        replaceWith = "\\n";
	break;

      case '\r':
        replaceWith = "\\r";
	break;

      case '\a':
        replaceWith = "\\a";
	break;

      case '"':
        replaceWith = "\\\"";
	break;

      default: {
        int nCh = ((int)nStr.charAt(i)) & 0xFF;

        if (nCh < 32 || nCh > 127) {

          char buffer[5];
          sprintf_s(buffer, 5, "\\x%02X", nCh);
          replaceWith = buffer;

        } else {
          replace=false;
        }
      }
    }

    // adjust character in new string when needed
    if (replace) {
      nStr = nStr.substring(0, i) + replaceWith + nStr.substring(i + 1);
      i += strlen(replaceWith) - 1;
    }

  }

  // return new string with enclosed quote characters
  return "\"" + nStr + "\"";
}
