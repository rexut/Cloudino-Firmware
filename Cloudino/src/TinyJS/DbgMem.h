/*
 * TinyJS
 *
 * A single-file Javascript-alike engine
 *
 * - Common memory debug functions
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

#ifndef TinyJS_DbgMem_h
#define TinyJS_DbgMem_h

#define DEBUG_MEMORY 1

#if DEBUG_MEMORY

#define DBGMEM_OUTPUT_OBJ Serial

#include "../TinyJS.h"      // catch CScriptVar and CScriptVarLink

#include <vector>

void mark_allocated(CScriptVar *v);
void mark_deallocated(CScriptVar *v);

void mark_allocated(CScriptVarLink *v);
void mark_deallocated(CScriptVarLink *v);

void show_allocated();

extern std::vector<CScriptVar*> allocatedVars;
extern std::vector<CScriptVarLink*> allocatedLinks;

#endif  // DEBUG_MEMORY

#endif  // TinyJS_DbgMem_h
