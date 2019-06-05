/*
  CTinyJS__reset.cpp - TinyJS Library add-on for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "../TinyJS.h"

void CTinyJS::reset()
{
  CScriptVarLink *c = root->firstChild;

  while (c) {

    CScriptVarLink *t = c->nextSibling;

    if (c->name=="String" || c->name=="Array" || c->name=="Object") {

      c->var->removeAllChildren();

    } else {

      root->removeLink(c);

    }

    c = t;

  }
}
