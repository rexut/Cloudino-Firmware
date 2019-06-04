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

#include "../DbgMem.h"

#if DEBUG_MEMORY

#include <cstdlib>
#include <vector>

std::vector<CScriptVar*> allocatedVars;
std::vector<CScriptVarLink*> allocatedLinks;

void show_allocated()
{
  for (size_t i = 0; i < allocatedVars.size(); i++) {
    // DBGMEM_OUTPUT_OBJ.printf("ALLOCATED, %d refs\n",
    //     allocatedVars[i]->getRefs());
    allocatedVars[i]->trace("  ");
  }

  for (size_t i = 0; i < allocatedLinks.size(); i++) {
    // DBGMEM_OUTPUT_OBJ.printf("ALLOCATED LINK %s, allocated[%d] to \n",
    //     allocatedLinks[i]->name.c_str(),
    //     allocatedLinks[i]->var->getRefs());
    allocatedLinks[i]->var->trace("  ");
  }

  allocatedVars.clear();
  allocatedLinks.clear();
}

#endif  // DEBUG_MEMORY
