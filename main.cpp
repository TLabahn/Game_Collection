#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "SDL_functions.h"
#include "Game_functions.h"



int main(int argc, char* args[]){

    //Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_KEYDOWN ){
						if( e.key.keysym.sym == SDLK_ESCAPE ){
                            quit = true;
						}
					}
				}
				SDL_BlitSurface( gMouseSurfaces[ MENU_BACKGROUND ], NULL, gScreenSurface, NULL);
				SDL_UpdateWindowSurface( gWindow );
			}
		}
	}
	close();



    return 0;
}
