/*
 * TinyJS
 *
 * A single-file Javascript-alike engine
 *
 * - Useful language functions
 *
 * Authored By Gordon Williams <gw@pur3.co.uk>
 * (https://github.com/gfwilliams/tiny-js - sha1:3677bae)
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

#ifndef TinyJS_Functions_h
#define TinyJS_Functions_h

#include "../TinyJS.h"

/// Register useful functions with the TinyJS interpreter
extern void registerCodeFunctions(CTinyJS *tinyJS);
extern void registerObjectFunctions(CTinyJS *tinyJS);
extern void registerRandFunctions(CTinyJS *tinyJS);
extern void registerStringFunctions(CTinyJS *tinyJS);
extern void registerIntegerFunctions(CTinyJS *tinyJS);
extern void registerJSONFunctions(CTinyJS *tinyJS);
extern void registerArrayFunctions(CTinyJS *tinyJS);
extern void registerParseFunctions(CTinyJS *tinyJS);
extern void registerFunctions(CTinyJS *tinyJS);

#endif  // TinyJS_Functions_h
