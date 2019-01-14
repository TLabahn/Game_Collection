#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stdbool.h>
#include <SDL2/SDL.h>


//Definiert einen Knopf
struct Button{
    int edgeleft;
    int edgeright;
    int edgetop;
    int edgebottom;
};


//Prüft ob sich der Mauszeiger an bestimmten Koordinaten befindet
bool MouseOverButton(struct Button test){

    int x, y;
    SDL_GetMouseState(&x, &y);

    if(x < test.edgeleft){
        return false;

    } else if(x > test.edgeright){
        return false;

    } else if(y < test.edgetop){
        return false;

    }else if(y > test.edgebottom){
        return false;

    } else {
        return true;
    }
}
