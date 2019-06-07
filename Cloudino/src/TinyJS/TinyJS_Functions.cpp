/*
 * TinyJS
 *
 * A single-file Javascript-alike engine
 *
 * - Useful language functions
 *
 * Authored By Gordon Williams <gw@pur3.co.uk>
 * (https://github.com/gfwilliams/tiny-js - sha1:1c91498)
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

#include "../CloudinoConf.h"

#include "TinyJS_Functions.h"

#include <Arduino.h>  // for type definitions

#include <vector>
#include <cstdlib>
static const size_t NPOS = -1;

// ----------------------------------------------- Actual Functions
void scTrace(CScriptVar *, void *userdata) {
    CTinyJS *js = (CTinyJS*)userdata;
    js->root->trace();
}

void scObjectDump(CScriptVar *c, void *) {
    c->getParameter("this")->trace("> ");
}

void scObjectClone(CScriptVar *c, void *) {
    CScriptVar *obj = c->getParameter("this");
    c->getReturnVar()->copyValue(obj);
}

void scMathRand(CScriptVar *c, void *) {
    c->getReturnVar()->setDouble((double)rand()/RAND_MAX);
}

void scMathRandInt(CScriptVar *c, void *) {
    int min = c->getParameter("min")->getInt();
    int max = c->getParameter("max")->getInt();
    int val = min + (int)(rand()%(1+max-min));
    c->getReturnVar()->setInt(val);
}

void scCharToInt(CScriptVar *c, void *) {
    String str = c->getParameter("ch")->getString();;
    int val = 0;
    if (str.length()>0)
        val = (int)str.c_str()[0];
    c->getReturnVar()->setInt(val);
}

void scStringIndexOf(CScriptVar *c, void *) {
    String str = c->getParameter("this")->getString();
    String search = c->getParameter("search")->getString();
    size_t p = str.indexOf(search);
    int val = (p==NPOS) ? -1 : p;
    c->getReturnVar()->setInt(val);
}

void scStringSubstring(CScriptVar *c, void *) {
    String str = c->getParameter("this")->getString();
    int lo = c->getParameter("lo")->getInt();
    int hi = c->getParameter("hi")->getInt();

    int l = hi-lo;
    if (l>0 && lo>=0 && lo+l<=(int)str.length())
      c->getReturnVar()->setString(str.substring(lo, hi));
    else
      c->getReturnVar()->setString("");
}

void scStringCharAt(CScriptVar *c, void *) {
    String str = c->getParameter("this")->getString();
    int p = c->getParameter("pos")->getInt();
    if (p>=0 && p<(int)str.length())
      c->getReturnVar()->setString(str.substring(p, p+1));
    else
      c->getReturnVar()->setString("");
}

void scStringCharCodeAt(CScriptVar *c, void *) {
    String str = c->getParameter("this")->getString();
    int p = c->getParameter("pos")->getInt();
    if (p>=0 && p<(int)str.length())
      c->getReturnVar()->setInt(str.charAt(p));
    else
      c->getReturnVar()->setInt(0);
}

void scStringSplit(CScriptVar *c, void *) {
    String str = c->getParameter("this")->getString();
    String sep = c->getParameter("separator")->getString();
    CScriptVar *result = c->getReturnVar();
    result->setArray();
    int length = 0;

    size_t pos = str.indexOf(sep);
    while (pos != NPOS) {
      result->setArrayIndex(length++, new CScriptVar(str.substring(0,pos)));
      str = str.substring(pos+1);
      pos = str.indexOf(sep);
    }

    if (str.length()>0)
      result->setArrayIndex(length++, new CScriptVar(str));
}

void scStringFromCharCode(CScriptVar *c, void *) {
    char str[2];
    str[0] = c->getParameter("char")->getInt();
    str[1] = 0;
    c->getReturnVar()->setString(str);
}

void scIntegerParseInt(CScriptVar *c, void *) {
    String str = c->getParameter("str")->getString();
    int val = atoi(str.c_str());
    c->getReturnVar()->setInt(val);
}

void scIntegerValueOf(CScriptVar *c, void *) {
    String str = c->getParameter("str")->getString();

    int val = 0;
    if (str.length()==1)
      val = str[0];
    c->getReturnVar()->setInt(val);
}

void scJSONStringify(CScriptVar *c, void *) {
    String result;
    c->getParameter("obj")->getJSON(result);
    c->getReturnVar()->setString(result);
}

void scExec(CScriptVar *c, void *userdata) {
    CTinyJS *tinyJS = (CTinyJS *)userdata;
    String str = c->getParameter("jsCode")->getString();
    tinyJS->execute(str);
}

void scEval(CScriptVar *c, void *userdata) {
    CTinyJS *tinyJS = (CTinyJS *)userdata;
    String str = c->getParameter("jsCode")->getString();
    c->setReturnVar(tinyJS->evaluateComplex(str).var);
}

void scArrayContains(CScriptVar *c, void *) {
  CScriptVar *obj = c->getParameter("obj");
  CScriptVarLink *v = c->getParameter("this")->firstChild;

  bool contains = false;
  while (v) {
      if (v->var->equals(obj)) {
        contains = true;
        break;
      }
      v = v->nextSibling;
  }

  c->getReturnVar()->setInt(contains);
}

void scArrayRemove(CScriptVar *c, void *) {
  CScriptVar *obj = c->getParameter("obj");
  std::vector<int> removedIndices;
  CScriptVarLink *v;
  // remove
  v = c->getParameter("this")->firstChild;
  while (v) {
      if (v->var->equals(obj)) {
        removedIndices.push_back(v->getIntName());
      }
      v = v->nextSibling;
  }
  // renumber
  v = c->getParameter("this")->firstChild;
  while (v) {
      int n = v->getIntName();
      int newn = n;
      for (size_t i=0;i<removedIndices.size();i++)
        if (n>=removedIndices[i])
          newn--;
      if (newn!=n)
        v->setIntName(newn);
      v = v->nextSibling;
  }
}

void scArrayJoin(CScriptVar *c, void *) {
  String sep = c->getParameter("separator")->getString();
  CScriptVar *arr = c->getParameter("this");

  String sstr;
  int l = arr->getArrayLength();
  for (int i=0;i<l;i++) {
    if (i>0) sstr+=sep;
    sstr+=arr->getArrayIndex(i)->getString();
  }

  c->getReturnVar()->setString(sstr);
}

// ----------------------------------------------- Register Code Functions
void registerCodeFunctions(CTinyJS *tinyJS) {
    tinyJS->addNative(F("function exec(jsCode)"), scExec, tinyJS); // execute the given code
    tinyJS->addNative(F("function eval(jsCode)"), scEval, tinyJS); // execute the given string (an expression) and return the result
    tinyJS->addNative(F("function trace()"), scTrace, tinyJS);
}

// ----------------------------------------------- Register Object Functions
void registerObjectFunctions(CTinyJS *tinyJS) {
    tinyJS->addNative(F("function Object.dump()"), scObjectDump, 0);
    tinyJS->addNative(F("function Object.clone()"), scObjectClone, 0);
}

// ----------------------------------------------- Register Rand Functions
void registerRandFunctions(CTinyJS *tinyJS) {
    tinyJS->addNative(F("function Math.rand()"), scMathRand, 0);
    tinyJS->addNative(F("function Math.randInt(min, max)"), scMathRandInt, 0);
}

// ----------------------------------------------- Register String Functions
void registerStringFunctions(CTinyJS *tinyJS) {
    tinyJS->addNative(F("function charToInt(ch)"), scCharToInt, 0); //  convert a character to an int - get its value
    tinyJS->addNative(F("function String.indexOf(search)"), scStringIndexOf, 0); // find the position of a string in a string, -1 if not
    tinyJS->addNative(F("function String.substring(lo,hi)"), scStringSubstring, 0);
    tinyJS->addNative(F("function String.charAt(pos)"), scStringCharAt, 0);
    tinyJS->addNative(F("function String.charCodeAt(pos)"), scStringCharCodeAt, 0);
    tinyJS->addNative(F("function String.fromCharCode(char)"), scStringFromCharCode, 0);
    tinyJS->addNative(F("function String.split(separator)"), scStringSplit, 0);
}

// ----------------------------------------------- Register Integer Functions
void registerIntegerFunctions(CTinyJS *tinyJS) {
    tinyJS->addNative(F("function Integer.parseInt(str)"), scIntegerParseInt, 0); // string to int
    tinyJS->addNative(F("function Integer.valueOf(str)"), scIntegerValueOf, 0); // value of a single character
}

// ----------------------------------------------- Register JSON Functions
void registerJSONFunctions(CTinyJS *tinyJS) {
    tinyJS->addNative(F("function JSON.stringify(obj, replacer)"), scJSONStringify, 0); // convert to JSON. replacer is ignored at the moment
    // JSON.parse is left out as you can (unsafely!) use eval instead
}

// ----------------------------------------------- Register Array Functions
void registerArrayFunctions(CTinyJS *tinyJS) {
    tinyJS->addNative(F("function Array.contains(obj)"), scArrayContains, 0);
    tinyJS->addNative(F("function Array.remove(obj)"), scArrayRemove, 0);
    tinyJS->addNative(F("function Array.join(separator)"), scArrayJoin, 0);
}

// ----------------------------------------------- Register Parse Functions
void registerParseFunctions(CTinyJS *tinyJS) {
    tinyJS->addNative(F("function parseInt(str)"), scIntegerParseInt, 0); // string to int
}

// ----------------------------------------------- Register Functions
void registerFunctions(CTinyJS *tinyJS) {
    registerCodeFunctions(tinyJS);
    registerObjectFunctions(tinyJS);
    registerRandFunctions(tinyJS);
    registerStringFunctions(tinyJS);
    registerIntegerFunctions(tinyJS);
    registerJSONFunctions(tinyJS);
    registerArrayFunctions(tinyJS);
}
