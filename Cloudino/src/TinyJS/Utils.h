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

#ifndef TinyJS_Utils_h
#define TinyJS_Utils_h

#include <Arduino.h>  // for type definitions

// Convert the given string into a quoted string suitable for JavaScript.
String getJSString(const String &str);

bool isWhitespace(char ch);
bool isHexadecimal(char ch);
bool isNumeric(char ch);
bool isAlpha(char ch);
bool isNumber(const String &str);
bool isAlphaNum(const String &str);
bool isIDString(const char *s);

#include <assert.h>
#define ASSERT(X) assert(X)

// Frees the given link IF it isn't owned by anything else.
#define CLEAN(x) { \
  CScriptVarLink *__v = x; \
  if (__v && !__v->owned) { \
    delete __v; \
  } \
}

// Create a LINK to point to VAR and free the old link.
// BUT this is more clever - it tries to keep the old link
// IF it's not owned to save allocations.
#define CREATE_LINK(LINK, VAR) { \
  if (!LINK || LINK->owned) \
    LINK = new CScriptVarLink(VAR); \
  else \
    LINK->replaceWith(VAR); \
}

#ifdef __GNUC__
#define vsprintf_s vsnprintf
#define sprintf_s snprintf
#define _strdup strdup
#endif

#endif  // TinyJS_Utils_h
