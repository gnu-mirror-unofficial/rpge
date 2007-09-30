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

#include "main.h"

int exec_guile_shell(void* unused_arg)
{
  scm_init_guile();
  scm_shell(0,0);
  return 0;//never reached, just here to please gcc.
}

int
main (int argc, char **argv)
{
  SDL_Surface *screen;
  SDL_Event *event = malloc(sizeof(SDL_Event));
  int next, now;
  tile test_tile;
  SCM testt;
  SDL_Rect clippy = {0,0,16,16};
  SDL_Init (SDL_INIT_EVERYTHING);
  screen = SDL_SetVideoMode (800, 640, 32, SDL_HWSURFACE);
  if ( screen == NULL )
  {
    fprintf (stderr,"SDL_SetVideoMode failed: %s\n", SDL_GetError());
    return 1;
  }
  SDL_WM_SetCaption ("RPGE", "RPGE");
  scm_init_guile();
  scm_c_define_gsubr("create-mob",3,0,0,guile_create_mob);
  scm_c_define_gsubr("create-tile",3,0,0,guile_create_tile);
  scm_c_define_gsubr("set-tile",3,0,0,guile_set_tile);
  scm_c_define_gsubr("set-all-tiles",1,0,0,guile_set_all_tiles);
  scm_c_define_gsubr("move-mob-right",3,0,0,guile_move_mob_right);
  scm_c_define_gsubr("move-mob-left",3,0,0,guile_move_mob_left);
  scm_c_define_gsubr("move-mob-down",3,0,0,guile_move_mob_down);
  scm_c_define_gsubr("move-mob-up",3,0,0,guile_move_mob_up);
  scm_c_define_gsubr("move-mob",4,0,0,guile_move_mob_all);
  scm_c_primitive_load ("table.guile");
  scm_c_primitive_load ("utils.guile");
  scm_c_primitive_load ("table_test.guile");
  SDL_CreateThread(exec_guile_shell,0);
  //testing
  tilegrid = init_tilegrid(50,40);
  test_tile = make_tile(push_image_on_stack("test.png"),clippy,BLOCK_NONE);
  tilegrid_width = 50;
  tilegrid_height = 40;
  set_all_tiles(test_tile);
  set_tile(25,20,make_tile(push_image_on_stack("test_sprite.png"),clippy,BLOCK_NONE));
  testt = tile_to_list(test_tile);
  test_tile = list_to_tile(testt);
  testt = tile_to_list(test_tile);
  for(int i = 0; i< 6; i++)
    {
      printf("%d ",scm_to_int16(scm_car(testt)));
      testt = scm_cdr(testt);
    }
  printf("\n");
  while (1)
    {
      SCM_TICK;
      now = SDL_GetTicks ();
      next = now + (int) (1000 / FRAMES_PER_SECOND);
      while (SDL_PollEvent (event))
	{
          switch (event->type)
	    {
	      case SDL_QUIT:
	        return 0;
	        break;
	    }
	}
      move_mobs();
      animate_mobs();
      render_screen(screen);
      if ( SDL_Flip( screen ) == -1 )
        {
          fprintf (stderr, "Cannot render frame, flip failure: %s\n", SDL_GetError());
          return 1;
        }
      now = SDL_GetTicks ();
      if (now < next)
	SDL_Delay (next - now);
    }
  free(event);
}
