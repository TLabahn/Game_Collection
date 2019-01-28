#include <SDL.h>
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


bool spielZug();
bool gewinner();

int Feld[3][3] = {0};

void TicTacToeFeld(struct Button* Buttons){

    //Hintergrund
    SDL_SetRenderDrawColor( gRenderer, 000, 000, 205, 0xFF );
    SDL_RenderClear( gRenderer );

    if(gewinner() == true){
        SDL_SetRenderDrawColor( gRenderer, 255, 000, 255, 0xFF );
    }

    SDL_RenderClear( gRenderer );

    //zeichnet den HauptFeld

    Rechteck_rand(SCREEN_WIDTH / 2 - 201, SCREEN_HEIGHT / 2 - 70, SCREEN_WIDTH * 16 / 30, SCREEN_HEIGHT * 1 / 30, 000, 000, 000);

    Rechteck_rand(SCREEN_WIDTH / 2 - 201, SCREEN_HEIGHT / 2 + 70, SCREEN_WIDTH * 16 / 30, SCREEN_HEIGHT * 1 / 30, 000, 000, 000);

    Rechteck_rand(SCREEN_WIDTH / 2 - 81, SCREEN_HEIGHT  / 7 + 10, SCREEN_WIDTH * 1 / 40, SCREEN_HEIGHT * 14 / 20, 000, 000, 000);

    Rechteck_rand(SCREEN_WIDTH / 2 + 80, SCREEN_HEIGHT  / 7 + 10, SCREEN_WIDTH * 1 / 40, SCREEN_HEIGHT * 14 / 20, 000, 000, 000);

    Rechteck_voll(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 70 + 1, SCREEN_WIDTH * 16 / 30 - 2, SCREEN_HEIGHT * 1 / 30 - 2, 000, 000, 000);

    Rechteck_voll(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 + 70 + 1, SCREEN_WIDTH * 16 / 30 - 2, SCREEN_HEIGHT * 1 / 30 - 2, 000, 000, 000);

    Rechteck_voll(SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT  / 7 + 11, SCREEN_WIDTH * 1 / 40 - 2, SCREEN_HEIGHT * 14 / 20 - 2, 000, 000, 000);

    Rechteck_voll(SCREEN_WIDTH / 2 + 81, SCREEN_HEIGHT  / 7 + 11, SCREEN_WIDTH * 1 / 40 - 2, SCREEN_HEIGHT * 14 / 20 - 2, 000, 000, 000);

    //malt den Button zum Hauptmenu
    Rechteck_voll(SCREEN_WIDTH / 3 - 220 + 1, SCREEN_HEIGHT / 3 - 150 + 1, SCREEN_WIDTH * 4 / 30 - 1, SCREEN_HEIGHT * 2 / 30 - 1, 222, 222, 222);

    Rechteck_rand(SCREEN_WIDTH / 3 - 220, SCREEN_HEIGHT / 3 - 150, SCREEN_WIDTH * 4 / 30, SCREEN_HEIGHT * 2 / 30, 000, 000, 000);

    // malt die Einzelne Kästchen des Feldes an
    // 3linke Spalte
    /*Rechteck_voll(SCREEN_WIDTH / 4 - 1 , SCREEN_HEIGHT / 4 - 55, SCREEN_WIDTH / 8 + 20 , SCREEN_HEIGHT / 5+15, 000, 000, 205);
    Rechteck_voll(SCREEN_WIDTH / 4 - 1 , SCREEN_HEIGHT / 2 - 50, SCREEN_WIDTH / 8 + 20 , SCREEN_HEIGHT / 5, 000, 000, 205);
    Rechteck_voll(SCREEN_WIDTH / 4 - 1 , SCREEN_HEIGHT / 2 + 90, SCREEN_WIDTH / 8 + 20 , SCREEN_HEIGHT / 5+5, 000, 000, 205);
    // 3Mittlere Spalte
    Rechteck_voll(SCREEN_WIDTH / 2 - 61 , SCREEN_HEIGHT / 4 - 55, SCREEN_WIDTH / 8 + 41 , SCREEN_HEIGHT / 5+15, 000, 000, 205);
    Rechteck_voll(SCREEN_WIDTH / 2 - 61 , SCREEN_HEIGHT / 2 - 50, SCREEN_WIDTH / 8 + 41 , SCREEN_HEIGHT / 5, 000, 000, 205);
    Rechteck_voll(SCREEN_WIDTH / 2 - 61 , SCREEN_HEIGHT / 2 + 90, SCREEN_WIDTH / 8 + 41 , SCREEN_HEIGHT / 5+5, 000, 000, 205);
    // 3Rechte Spalte
    Rechteck_voll(SCREEN_WIDTH / 2 + 100 , SCREEN_HEIGHT / 4 - 55, SCREEN_WIDTH / 8 + 25 , SCREEN_HEIGHT / 5+15, 000, 000, 205);
    Rechteck_voll(SCREEN_WIDTH / 2 + 100 , SCREEN_HEIGHT / 2 - 50, SCREEN_WIDTH / 8 + 25 , SCREEN_HEIGHT / 5, 000, 000, 205);
    Rechteck_voll(SCREEN_WIDTH / 2 + 100 , SCREEN_HEIGHT / 2 + 90, SCREEN_WIDTH / 8 + 25 , SCREEN_HEIGHT / 5+5, 000, 000, 205);*/

    for(int i = 0; i < 9; i++){
        if(Feld[i / 3][i % 3] == 1){
            Rechteck_voll( Buttons[i + 1].x, Buttons[i + 1].y, Buttons[i + 1].width, Buttons[i + 1].heigth, 148, 000, 211);
        } else if(Feld[i / 3][i % 3] == 2){
            Rechteck_voll( Buttons[i + 1].x, Buttons[i + 1].y, Buttons[i + 1].width, Buttons[i + 1].heigth, 230, 230, 250);
        }
    }

        //Lässt die Home Button beim mouseover leuchten
        switch(WhichButton(Buttons, 10)){
            case 1:
                Rechteck_voll(SCREEN_WIDTH / 3 - 220 + 1, SCREEN_HEIGHT / 3 - 150 + 1, SCREEN_WIDTH * 4 / 30 - 2, SCREEN_HEIGHT * 2 / 30 - 2, 242, 242, 242);
                break;
            case 2:
                Rechteck_voll(Buttons[WhichButton(Buttons, 10)-1].x, Buttons[WhichButton(Buttons, 10)-1].y, Buttons[WhichButton(Buttons, 10)-1].width, Buttons[WhichButton(Buttons, 10)-1].heigth, 255, 127, 000); break;
            case 3:
                Rechteck_voll(Buttons[WhichButton(Buttons, 10)-1].x, Buttons[WhichButton(Buttons, 10)-1].y, Buttons[WhichButton(Buttons, 10)-1].width, Buttons[WhichButton(Buttons, 10)-1].heigth, 255, 127, 000); break;
            case 4:
                Rechteck_voll(Buttons[WhichButton(Buttons, 10)-1].x, Buttons[WhichButton(Buttons, 10)-1].y, Buttons[WhichButton(Buttons, 10)-1].width, Buttons[WhichButton(Buttons, 10)-1].heigth, 255, 127, 000); break;
            case 5:
                Rechteck_voll(Buttons[WhichButton(Buttons, 10)-1].x, Buttons[WhichButton(Buttons, 10)-1].y, Buttons[WhichButton(Buttons, 10)-1].width, Buttons[WhichButton(Buttons, 10)-1].heigth, 255, 127, 000); break;
            case 6:
                Rechteck_voll(Buttons[WhichButton(Buttons, 10)-1].x, Buttons[WhichButton(Buttons, 10)-1].y, Buttons[WhichButton(Buttons, 10)-1].width, Buttons[WhichButton(Buttons, 10)-1].heigth, 255, 127, 000); break;
            case 7:
                Rechteck_voll(Buttons[WhichButton(Buttons, 10)-1].x, Buttons[WhichButton(Buttons, 10)-1].y, Buttons[WhichButton(Buttons, 10)-1].width, Buttons[WhichButton(Buttons, 10)-1].heigth, 255, 127, 000); break;
            case 8:
                Rechteck_voll(Buttons[WhichButton(Buttons, 10)-1].x, Buttons[WhichButton(Buttons, 10)-1].y, Buttons[WhichButton(Buttons, 10)-1].width, Buttons[WhichButton(Buttons, 10)-1].heigth, 255, 127, 000); break;
            case 9:
                Rechteck_voll(Buttons[WhichButton(Buttons, 10)-1].x, Buttons[WhichButton(Buttons, 10)-1].y, Buttons[WhichButton(Buttons, 10)-1].width, Buttons[WhichButton(Buttons, 10)-1].heigth, 255, 127, 000); break;
            case 10:
                Rechteck_voll(Buttons[WhichButton(Buttons, 10)-1].x, Buttons[WhichButton(Buttons, 10)-1].y, Buttons[WhichButton(Buttons, 10)-1].width, Buttons[WhichButton(Buttons, 10)-1].heigth, 255, 127, 000); break;
            default: break;
        }
        //Update screen
        SDL_RenderPresent( gRenderer );

}

bool spielZug(struct Button arr[], int nummer, int* spieler){

    int x, y;

    x = nummer / 3;
    y = nummer % 3;

    if(Feld[x][y] == 0){

        if(*spieler % 2 == false){
            Feld[x][y] = 1;
        } else {
            Feld[x][y] = 2;
        }
        *spieler+=1;
    }


}

bool gewinner(){
    int spieler1 = 0;
    int spieler2 = 0;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(Feld[i][j] == 1){
                spieler1++;
                spieler2 = 0;
                if(spieler1 == 3){
                    return true;
                }
            }else if(Feld[i][j] == 2){
                spieler1 = 0;
                spieler2++;
                if(spieler2 == 3){
                    return true;
                }
            } else {
                spieler1 = spieler2 = 0;
            }
        }
        spieler1 = spieler2 = 0;
    }
    spieler1 = 0;
    spieler2 = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(Feld[j][i] == 1){
                spieler1++;
                spieler2 = 0;
                if(spieler1 == 3){
                    return true;
                }
            }else if(Feld[j][i] == 2){
                spieler1 = 0;
                spieler2++;
                if(spieler2 == 3){
                    return true;
                }
            }else {
                spieler1 = spieler2 = 0;
            }
        }
        spieler1 = spieler2 = 0;
    }
    spieler1 = 0;
    spieler2 = 0;
    for(int i = 0; i < 3; i++){
            if(Feld[i][i] == 1){
                spieler1++;
                spieler2 = 0;
                if(spieler1 == 3){
                    return true;
                }
            }else if(Feld[i][i] == 2){
                spieler1 = 0;
                spieler2++;
                if(spieler2 == 3){
                    return true;
                }

            }else {
                spieler1 = spieler2 = 0;
            }
        }
        spieler1 = spieler2 = 0;

    for (int i = 0, j = 2; i < 3; i++, j--){
            if( Feld[j][i] = 1)
                spieler1++;
                spieler2 = 0;
                if(spieler1 == 3){
                    return true;
                }
    }else if(Feld[j][i] == 2){
                spieler1 = 0;
                spieler2++;
                if(spieler2 == 3){
                    return true;
                }

            }else {
                spieler1 = spieler2 = 0;
            }
        }

    return false;
}

bool TicTacToe(){

    int spieler = 2;

    // Knopf für Zurück zu HauptMenu
    struct Button Button_1 = { SCREEN_WIDTH / 3 - 220 + 1, SCREEN_HEIGHT / 3 - 150 + 1, SCREEN_WIDTH * 4 / 30 - 2, SCREEN_HEIGHT * 2 / 30 - 2};
    // Knöpfe für Spielfeld
    struct Button Button_2 = { SCREEN_WIDTH / 4 - 1 , SCREEN_HEIGHT / 4 - 55, SCREEN_WIDTH / 8 + 20 , SCREEN_HEIGHT / 5+15};
    struct Button Button_3 = { SCREEN_WIDTH / 4 - 1 , SCREEN_HEIGHT / 2 - 50, SCREEN_WIDTH / 8 + 20 , SCREEN_HEIGHT / 5};
    struct Button Button_4 = { SCREEN_WIDTH / 4 - 1 , SCREEN_HEIGHT / 2 + 90, SCREEN_WIDTH / 8 + 20 , SCREEN_HEIGHT / 5+5};
    struct Button Button_5 = { SCREEN_WIDTH / 2 - 61 , SCREEN_HEIGHT / 4 - 55, SCREEN_WIDTH / 8 + 41 , SCREEN_HEIGHT / 5+15};
    struct Button Button_6 = { SCREEN_WIDTH / 2 - 61 , SCREEN_HEIGHT / 2 - 50, SCREEN_WIDTH / 8 + 41 , SCREEN_HEIGHT / 5};
    struct Button Button_7 = { SCREEN_WIDTH / 2 - 61 , SCREEN_HEIGHT / 2 + 90, SCREEN_WIDTH / 8 + 41 , SCREEN_HEIGHT / 5+5};
    struct Button Button_8 = { SCREEN_WIDTH / 2 + 100 , SCREEN_HEIGHT / 4 - 55, SCREEN_WIDTH / 8 + 25 , SCREEN_HEIGHT / 5+15};
    struct Button Button_9 = { SCREEN_WIDTH / 2 + 100 , SCREEN_HEIGHT / 2 - 50, SCREEN_WIDTH / 8 + 25 , SCREEN_HEIGHT / 5};
    struct Button Button_10 = { SCREEN_WIDTH / 2 + 100 , SCREEN_HEIGHT / 2 + 90, SCREEN_WIDTH / 8 + 25 , SCREEN_HEIGHT / 5+5};

    struct Button MenuButtons[10] = {Button_1,Button_2,Button_3,Button_4,Button_5,Button_6,Button_7,Button_8,Button_9,Button_10};

    SDL_Event e; // Für Tasteneingabe

    bool quit = false;

    while(true){

        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 ){

            //User requests quit
            if( e.type == SDL_KEYDOWN ){
				if( e.key.keysym.sym == SDLK_ESCAPE ){
                    return true;
				}
			}
			if ( e.type == SDL_QUIT ){
                return true;
			}
			if(e.type == SDL_MOUSEBUTTONDOWN){;
                switch(WhichButton(MenuButtons, 10)){
                    case 1:
                        spieler = 2;
                        for(int i = 0; i < 3; i++){
                            for(int j = 0; j < 3; j++){
                                Feld[i][j] = 0;
                            }
                        }
                        return false;
                        break;
                    case 2:
                        spielZug(&MenuButtons[WhichButton(MenuButtons, 10)-1], WhichButton(MenuButtons, 10)-2, &spieler);
                        break;
                    case 3:
                        spielZug(&MenuButtons[WhichButton(MenuButtons, 10)-1], WhichButton(MenuButtons, 10)-2, &spieler);
                        break;
                    case 4:
                        spielZug(&MenuButtons[WhichButton(MenuButtons, 10)-1], WhichButton(MenuButtons, 10)-2, &spieler);
                        break;
                    case 5:
                        spielZug(&MenuButtons[WhichButton(MenuButtons, 10)-1], WhichButton(MenuButtons, 10)-2, &spieler);
                        break;
                    case 6:
                        spielZug(&MenuButtons[WhichButton(MenuButtons, 10)-1], WhichButton(MenuButtons, 10)-2, &spieler);
                        break;
                    case 7:
                        spielZug(&MenuButtons[WhichButton(MenuButtons, 10)-1], WhichButton(MenuButtons, 10)-2, &spieler);
                        break;
                    case 8:
                        spielZug(&MenuButtons[WhichButton(MenuButtons, 10)-1], WhichButton(MenuButtons, 10)-2, &spieler);
                        break;
                    case 9:
                        spielZug(&MenuButtons[WhichButton(MenuButtons, 10)-1], WhichButton(MenuButtons, 10)-2, &spieler);
                        break;
                    case 10:
                        spielZug(&MenuButtons[WhichButton(MenuButtons, 10)-1], WhichButton(MenuButtons, 10)-2, &spieler);
                        break;
                }

			}

            TicTacToeFeld(MenuButtons);
        }

    }
}

