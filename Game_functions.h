#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stdbool.h>
#include <cmath>


/*Generelle Funktionen, Makros, Globale Variablen etc.
*/


//Definiert einen Knopf
struct Button{
    int x;
    int y;
    int width;
    int heigth;
};


//Prüft ob sich der Mauszeiger an bestimmten Koordinaten befindet
bool MouseOverButton(struct Button test){

    int x, y;
    SDL_GetMouseState(&x, &y);

    if(x < test.x){
        return false;

    } else if(x > test.x + test.width){
        return false;

    } else if(y < test.y){
        return false;

    }else if(y > test.y + test.heigth){
        return false;

    } else {
        return true;
    }
}


int WhichButton(struct Button a[], int n){

    for(int i=0; i<n; i++){
        if(MouseOverButton(a[i]) == 1)
        return i+1;
    }
    return 0;
}


//malt ein ausgefülltes Rechteck. Inputs: x = koordinate der linken oberen Ecke, y = koordinate der linken oberen ecke, width = breite, height = höhe, RGB = Farbcode;
void Rechteck_voll(int x, int y, int width, int height, int R, int G, int B){
    SDL_Rect fillButton = { x, y, width, height};
    SDL_SetRenderDrawColor( gRenderer, R, G, B, 0xFF );
	SDL_RenderFillRect( gRenderer, &fillButton );
}

void Rechteck_rand(int x, int y, int width, int heigth, int R, int G, int B){
    SDL_Rect outlineButton = { x, y, width, heigth};
    SDL_SetRenderDrawColor( gRenderer, R, G, B, 0xFF );
	SDL_RenderDrawRect( gRenderer, &outlineButton );
}



/*Funktionen die im Zusammenhang zu Tic Tac Toe stehen.
*/







/*Funktionen die im Zusammenhang zu Tic Tac Toe Advanced stehen.
*/
