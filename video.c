/*
Copyright Remco Bras and Michael de Lang 2007.
This file is part of RPGE.

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

#include "video.h"

SDL_Surface*
load_image (char* filename)
{
  printf ("%s\n", filename);
  SDL_Surface* loadedImage = NULL;
  SDL_Surface* optimizedImage = NULL;

  loadedImage = IMG_Load ( filename );
  if ( loadedImage != NULL )
  {
    optimizedImage = SDL_DisplayFormatAlpha ( loadedImage ); //forces loading of alpha in images(PNG mostly)
    SDL_FreeSurface ( loadedImage );
  }
  else
    printf ("Loading of %s failed: %s\n", filename, IMG_GetError());
  return optimizedImage;
}

void
apply_surface ( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface ( source, clip, destination, &offset );
}
