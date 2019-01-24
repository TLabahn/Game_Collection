#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stdbool.h>
#include <cmath>
#include "SDL_functions.h"
#include "Game_functions.h"



int main(int argc, char* args[]){

    struct Button Button_1 = { SCREEN_WIDTH * 2 / 6, SCREEN_HEIGHT * 1 / 6, SCREEN_WIDTH * 2 / 6, SCREEN_HEIGHT * 1 / 5};
    struct Button Button_2 = { SCREEN_WIDTH * 2 / 6, SCREEN_HEIGHT * 4 / 6, SCREEN_WIDTH * 2 / 6, SCREEN_HEIGHT * 1 / 5};

    struct Button MenuButtons[2] = {Button_1, Button_2};

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
					if ( e.type == SDL_QUIT ){
                        quit = true;
					}
					if( e.type == SDL_MOUSEBUTTONDOWN){
                        switch( WhichButton(MenuButtons, 2)){
                            case 1:
                                //quit = TicTacToe();
                                break;

                            case 2:
                                quit = TicTacToeAdvanced();
                                break;

                            default:
                                break;

                        }
					}
				}
				//Hintergrund
				SDL_SetRenderDrawColor( gRenderer, 000, 229, 238, 0xFF );
				SDL_RenderClear( gRenderer );

                //malt die Menubottons
				Rechteck_voll(SCREEN_WIDTH * 2 / 6 + 1, SCREEN_HEIGHT * 1 / 6 + 1, SCREEN_WIDTH * 2 / 6 - 1, SCREEN_HEIGHT * 1 / 5 - 2, 158, 158, 158);

                Rechteck_voll(SCREEN_WIDTH * 2 / 6 + 1, SCREEN_HEIGHT * 4 / 6 + 1, SCREEN_WIDTH * 2 / 6 - 1, SCREEN_HEIGHT * 1 / 5 - 2, 158, 158, 158);

				Rechteck_rand(SCREEN_WIDTH * 2 / 6, SCREEN_HEIGHT * 1 / 6, SCREEN_WIDTH * 2 / 6, SCREEN_HEIGHT * 1 / 5, 000, 000, 000);

				Rechteck_rand(SCREEN_WIDTH * 2 / 6, SCREEN_HEIGHT * 4 / 6, SCREEN_WIDTH * 2 / 6, SCREEN_HEIGHT * 1 / 5, 000, 000, 000);

                //Lässt die Buttons beim mouseover leuchten
				switch(WhichButton(MenuButtons, 2)){
                    case 1:
                        Rechteck_voll(SCREEN_WIDTH * 2 / 6 + 1, SCREEN_HEIGHT * 1 / 6 + 1, SCREEN_WIDTH * 2 / 6 - 2, SCREEN_HEIGHT * 1 / 5 - 2, 242, 242, 242);
                        break;

                    case 2:
                        Rechteck_voll(SCREEN_WIDTH * 2 / 6 + 1, SCREEN_HEIGHT * 4 / 6 + 1, SCREEN_WIDTH * 2 / 6 - 2, SCREEN_HEIGHT * 1 / 5 - 2, 242, 242, 242);
                        break;

                    default:
                        break;
                }


				//Update screen
				SDL_RenderPresent( gRenderer );

/*				int x, y;
				SDL_GetMouseState(&x, &y);
				printf("x: %d, y: %d\n", x, y);
*/			}
		}
	}
	close();



    return 0;
}
