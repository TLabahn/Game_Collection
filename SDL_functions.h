#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stdbool.h>
#include <SDL2/SDL.h>

//Bildschirmauflösung
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;


enum ButtonSprite {
    MENU_BACKGROUND,
    TOTAL,
};


//Initialisiert SDL2 Funktionen
bool init();

//Lädt Medien hoch
bool loadmedia();

//Schließt SDL2 Funktionen und gibt Pointer frei
void close();


//Mit SDL2 in Verbindung stehende Pointer
SDL_Surface* loadSurface(std::string path);

SDL_Window* gWindow = NULL;

SDL_Surface* gScreenSurface = NULL;

SDL_Surface* gMouseSurfaces[ TOTAL ];

SDL_Surface* gCurrentSuface = NULL;


//Initialisiert SDL2 Funktionen
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "Game_Collection.exe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}


//Lädt Medien hoch
bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Lädt Menu Hintergrund
	gMouseSurfaces[ MENU_BACKGROUND ] = loadSurface( "images/menu_background.bmp" );
	if( gMouseSurfaces[ MENU_BACKGROUND ] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	return success;
}


//Beendet alle SDL2 Funktionen
void close()
{
	//Deallocate surfaces
	for( int i = 0; i < TOTAL; ++i )
	{
		SDL_FreeSurface( gMouseSurfaces[ i ] );
		gMouseSurfaces[ i ] = NULL;
	}

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}


SDL_Surface* loadSurface( std::string path )
{
	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	}

	return loadedSurface;
}











































