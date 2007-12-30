/*
Copyright Remco Bras 2007
This file is part of RPGE

RPGE is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

RPGE is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#ifndef TEXT_H
#define TEXT_H

#include "sequence.h"
#include <SDL/SDL_ttf.h>

typedef struct
{
  sequence buffers; 
  int fontindex;
  SDL_Color color;
} text;

typedef struct
{
  TTF_Font* font;
  char* filename;
  unsigned int size;
} font;

extern sequence texts;
extern sequence fonts;

int open_font(char* filename, int size);
void close_font(int index);

#endif