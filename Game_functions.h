#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
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

bool WinCondition();

void TicTacToeAdvancedFeld();

int TicTacToeAdvancedZug();

bool TicTacToeAdvanced();

void Drehen();



int Feld[6][6] = {0};

void TicTacToeAdvancedFeld(struct Button* Buttons){

    //Hintergrund
    SDL_SetRenderDrawColor( gRenderer, 102, 205, 170, 0xFF );
    if(WinCondition() == true){
        SDL_SetRenderDrawColor( gRenderer, 000, 255, 000, 0xFF );
    }
    SDL_RenderClear( gRenderer );

    Rechteck_rand( SCREEN_WIDTH * 3 / 12, SCREEN_HEIGHT * 1 / 8, SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 4, 000, 000, 000);
    Rechteck_voll( SCREEN_WIDTH * 3 / 12 + 1, SCREEN_HEIGHT * 1 / 8 + 1, SCREEN_WIDTH / 2 - 2, SCREEN_HEIGHT * 3 / 4 - 2, 238, 064, 000);

    Rechteck_rand( SCREEN_WIDTH / 40, SCREEN_HEIGHT / 40, SCREEN_WIDTH / 10, SCREEN_WIDTH / 20, 000, 000, 000);
    Rechteck_voll( SCREEN_WIDTH / 40 + 1, SCREEN_HEIGHT / 40 + 1, SCREEN_WIDTH / 10 - 2, SCREEN_WIDTH / 20 - 2, 158, 158, 158);

    Rechteck_voll( SCREEN_WIDTH / 2, SCREEN_HEIGHT * 1 / 8, SCREEN_WIDTH / 160, SCREEN_HEIGHT * 3 / 4, 000, 000, 000);

    Rechteck_voll( SCREEN_WIDTH * 3 / 12, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_WIDTH / 160, 000, 000, 000);

    for(int i = 0; i < 36; i++){
        if(Feld[i % 6][i / 6] == 1){
            Rechteck_voll( Buttons[i + 1].x + 5, Buttons[i + 1].y + 5, Buttons[i + 1].width - 10, Buttons[i + 1].heigth - 10, 255, 255, 255);
        } else if(Feld[i % 6][i / 6] == 2){
            Rechteck_voll( Buttons[i + 1].x + 5, Buttons[i + 1].y + 5, Buttons[i + 1].width - 10, Buttons[i + 1].heigth - 10, 000, 000, 000);
        }
    }

    for(int i = 37; i < 46; i++){
        Rechteck_rand(Buttons[i].x, Buttons[i].y, Buttons[i].width, Buttons[i].heigth, 000, 000, 000);
        Rechteck_voll(Buttons[i].x + 1, Buttons[i].y + 1, Buttons[i].width - 2, Buttons[i].heigth - 2, 158, 158, 158);
    }

/*    TTF_Font* Sans24 = TTF_OpenFont("Sans.ttf", 24);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans24, "Exit to main Menu", Black);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);
    SDL_Rect Exit_to_Menu = { 50, 50, 200, 200};
    SDL_RenderCopy(gRenderer, Message, NULL, &Exit_to_Menu);
*/

    int tile = WhichButton(Buttons, 45) - 1;

    //Lässt Buttons Leuchten
    switch(tile + 1){
        case 1:
            Rechteck_voll( SCREEN_WIDTH / 40 + 1, SCREEN_HEIGHT / 40 + 1, SCREEN_WIDTH / 10 - 2, SCREEN_WIDTH / 20 - 2, 242, 242, 242);
            break;
        case 2:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 3:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 4:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 5:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 6:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 7:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 8:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 9:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 10:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 11:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 12:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 13:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 14:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 15:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 16:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 17:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 18:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 19:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 20:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 21:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 22:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 23:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 24:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 25:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 26:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 27:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 28:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 29:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 30:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 31:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 32:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 33:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 34:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 35:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 36:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 37:
            Rechteck_voll(Buttons[tile].x, Buttons[tile].y, Buttons[tile].width, Buttons[tile].heigth, 152, 255, 255); break;
        case 38:
            Rechteck_voll(Buttons[tile].x + 1, Buttons[tile].y + 1, Buttons[tile].width - 2, Buttons[tile].heigth - 2, 242, 242, 242); break;
        case 39:
            Rechteck_voll(Buttons[tile].x + 1, Buttons[tile].y + 1, Buttons[tile].width - 2, Buttons[tile].heigth - 2, 242, 242, 242); break;
        case 40:
            Rechteck_voll(Buttons[tile].x + 1, Buttons[tile].y + 1, Buttons[tile].width - 2, Buttons[tile].heigth - 2, 242, 242, 242); break;
        case 41:
            Rechteck_voll(Buttons[tile].x + 1, Buttons[tile].y + 1, Buttons[tile].width - 2, Buttons[tile].heigth - 2, 242, 242, 242); break;
        case 42:
            Rechteck_voll(Buttons[tile].x + 1, Buttons[tile].y + 1, Buttons[tile].width - 2, Buttons[tile].heigth - 2, 242, 242, 242); break;
        case 43:
            Rechteck_voll(Buttons[tile].x + 1, Buttons[tile].y + 1, Buttons[tile].width - 2, Buttons[tile].heigth - 2, 242, 242, 242); break;
        case 44:
            Rechteck_voll(Buttons[tile].x + 1, Buttons[tile].y + 1, Buttons[tile].width - 2, Buttons[tile].heigth - 2, 242, 242, 242); break;
        case 45:
            Rechteck_voll(Buttons[tile].x + 1, Buttons[tile].y + 1, Buttons[tile].width - 2, Buttons[tile].heigth - 2, 242, 242, 242); break;
        default:
            break;
    }

    //Update screen
    SDL_RenderPresent( gRenderer );
}

bool WinCondition(){
    int spieler1 = 0, spieler2 = 0;

    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            if(Feld[i][j] == 1){
                spieler1++;
                spieler2 = 0;
                if(spieler1 == 5){
                    return true;
                }
            }else if(Feld[i][j] == 2){
                spieler1 = 0;
                spieler2++;
                if(spieler2 == 5){
                    return true;
                }
            } else {
                spieler1 = spieler2 = 0;
            }
        }
    }
    spieler1 = 0;
    spieler2 = 0;
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            if(Feld[j][i] == 1){
                spieler1++;
                spieler2 = 0;
                if(spieler1 == 5){
                    return true;
                }
            }else if(Feld[j][i] == 2){
                spieler1 = 0;
                spieler2++;
                if(spieler2 == 5){
                    return true;
                }
            }else {
                spieler1 = spieler2 = 0;
            }
        }
    }
    return false;
}

void TicTacToeAdvancedZug(struct Button arr[], int nummer, int* spieler){

    int x, y;

    y = nummer / 6;
    x = nummer % 6;

    if(Feld[x][y] == 0){

        if(*spieler % 2 == false){
            Feld[x][y] = 1;
        } else {
            Feld[x][y] = 2;
        }
        *spieler+=1;
    }
}

void Drehen(struct Button* arr, int viertel, char richtung){

    int matrix[3][3], x, y, a;

    struct Button temp[3][3], Button2D[3][3];

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            x = j + 6 * i + i * 3;

            Button2D[i][j] = arr[x + 1];

            printf("Der Knopf im Feld %d ist in der Matrix auf der Position %d%d\n", x, i, j);

        }
    }
    printf("\n\n");

    //In welchem Viertel befinde ich mich
    if( viertel == 1){

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                x = j + 6 * i + 1;

                Button2D[i][j] = arr[x + 1];

                printf("Der Knopf im Feld %d ist in der Matrix auf der Position %d%d\n", x, i, j);

            }
        }
        printf("\n\n");

        //In welche Richtung wird gedreht
        if( richtung == 'l'){
            for(int i = 0, m = 2; i < 3; i++, m--){
                for(int j = 0, n = 0; j < 3; j++, n++){
                    printf("%d%d -> %d%d\nFeld: %d\n", i+1, j+1, n+1, m+1, Feld[i][j]);
                    matrix[n][m] = Feld[i][j];

                    temp[n][m] = Button2D[i][j];
                }
            }
        } else if( richtung == 'r'){
            for(int i = 0, m = 0; i < 3; i++, m++){
                for(int j = 0, n = 2; j < 3; j++, n--){
                    matrix[n][m] = Feld[i][j];

                    temp[n][m] = Button2D[i][j];
                }
            }
        }

        //Zurückschreiben
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                a = i * 3 + j + i * 3 + 1;

                printf("Das Feld %d wird an die Stelle %d%d geschrieben\n", a, i+1, j+1);

                Feld[i][j] = matrix[i][j];

                arr[a] = temp[i][j];
            }
        }


    } else if( viertel == 2){

    } else if( viertel == 3){

    } else if( viertel == 4){

    }
}

bool TicTacToeAdvanced(){

    int spieler = 2;

    struct Button Exit_to_Menu = { SCREEN_WIDTH / 40, SCREEN_HEIGHT / 40, SCREEN_WIDTH / 10, SCREEN_WIDTH / 20};

    int TILE_WIDTH = SCREEN_WIDTH / 12 - 15;

    //Felder des Spielfelds
    struct Button tile_11 = { SCREEN_WIDTH * 3 / 12 + 15, SCREEN_WIDTH / 12 + 15, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_12 = { SCREEN_WIDTH * 3 / 12 + 25 + TILE_WIDTH, SCREEN_WIDTH / 12 + 15, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_13 = { SCREEN_WIDTH * 3 / 12 + 35 + TILE_WIDTH * 2, SCREEN_WIDTH / 12 + 15, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_14 = { SCREEN_WIDTH / 2 + 15, SCREEN_WIDTH / 12 + 15, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_15 = { SCREEN_WIDTH / 2 + 25 + TILE_WIDTH, SCREEN_WIDTH / 12 + 15, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_16 = { SCREEN_WIDTH / 2 + 35 + TILE_WIDTH * 2, SCREEN_WIDTH / 12 + 15, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_21 = { SCREEN_WIDTH * 3 / 12 + 15, SCREEN_WIDTH / 12 + 25 + TILE_WIDTH, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_22 = { SCREEN_WIDTH * 3 / 12 + 25 + TILE_WIDTH, SCREEN_WIDTH / 12 + 25 + TILE_WIDTH, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_23 = { SCREEN_WIDTH * 3 / 12 + 35 + TILE_WIDTH * 2, SCREEN_WIDTH / 12 + 25 + TILE_WIDTH, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_24 = { SCREEN_WIDTH / 2 + 15, SCREEN_WIDTH / 12 + 25 + TILE_WIDTH, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_25 = { SCREEN_WIDTH / 2 + 25 + TILE_WIDTH, SCREEN_WIDTH / 12 + 25 + TILE_WIDTH, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_26 = { SCREEN_WIDTH / 2 + 35 + TILE_WIDTH * 2, SCREEN_WIDTH / 12 + 25 + TILE_WIDTH, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_31 = { SCREEN_WIDTH * 3 / 12 + 15, SCREEN_WIDTH / 12 + 35 + TILE_WIDTH * 2, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_32 = { SCREEN_WIDTH * 3 / 12 + 25 + TILE_WIDTH, SCREEN_WIDTH / 12 + 35 + TILE_WIDTH * 2, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_33 = { SCREEN_WIDTH * 3 / 12 + 35 + TILE_WIDTH * 2, SCREEN_WIDTH / 12 + 35 + TILE_WIDTH * 2, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_34 = { SCREEN_WIDTH / 2 + 15, SCREEN_WIDTH / 12 + 35 + TILE_WIDTH * 2, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_35 = { SCREEN_WIDTH / 2 + 25 + TILE_WIDTH, SCREEN_WIDTH / 12 + 35 + TILE_WIDTH * 2, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_36 = { SCREEN_WIDTH / 2 + 35 + TILE_WIDTH * 2, SCREEN_WIDTH / 12 + 35 + TILE_WIDTH * 2, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_41 = { SCREEN_WIDTH * 3 / 12 + 15, SCREEN_WIDTH * 4 / 12 + 15, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_42 = { SCREEN_WIDTH * 3 / 12 + 25 + TILE_WIDTH, SCREEN_WIDTH * 4 / 12 + 15, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_43 = { SCREEN_WIDTH * 3 / 12 + 35 + TILE_WIDTH * 2, SCREEN_WIDTH * 4 / 12 + 15, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_44 = { SCREEN_WIDTH / 2 + 15, SCREEN_WIDTH * 4 / 12 + 15, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_45 = { SCREEN_WIDTH / 2 + 25 + TILE_WIDTH, SCREEN_WIDTH * 4 / 12 + 15, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_46 = { SCREEN_WIDTH / 2 + 35 + TILE_WIDTH * 2, SCREEN_WIDTH * 4 / 12 + 15, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_51 = { SCREEN_WIDTH * 3 / 12 + 15, SCREEN_WIDTH * 4 / 12 + 25 + TILE_WIDTH, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_52 = { SCREEN_WIDTH * 3 / 12 + 25 + TILE_WIDTH, SCREEN_WIDTH * 4 / 12 + 25 + TILE_WIDTH, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_53 = { SCREEN_WIDTH * 3 / 12 + 35 + TILE_WIDTH * 2, SCREEN_WIDTH * 4 / 12 + 25 + TILE_WIDTH, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_54 = { SCREEN_WIDTH / 2 + 15, SCREEN_WIDTH * 4 / 12 + 25 + TILE_WIDTH, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_55 = { SCREEN_WIDTH / 2 + 25 + TILE_WIDTH, SCREEN_WIDTH * 4 / 12 + 25 + TILE_WIDTH, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_56 = { SCREEN_WIDTH / 2 + 35 + TILE_WIDTH * 2, SCREEN_WIDTH * 4 / 12 + 25 + TILE_WIDTH, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_61 = { SCREEN_WIDTH * 3 / 12 + 15, SCREEN_WIDTH * 4 / 12 + 35 + TILE_WIDTH * 2, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_62 = { SCREEN_WIDTH * 3 / 12 + 25 + TILE_WIDTH, SCREEN_WIDTH * 4 / 12 + 35 + TILE_WIDTH * 2, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_63 = { SCREEN_WIDTH * 3 / 12 + 35 + TILE_WIDTH * 2, SCREEN_WIDTH * 4 / 12 + 35 + TILE_WIDTH * 2, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_64 = { SCREEN_WIDTH / 2 + 15, SCREEN_WIDTH * 4 / 12 + 35 + TILE_WIDTH * 2, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_65 = { SCREEN_WIDTH / 2 + 25 + TILE_WIDTH, SCREEN_WIDTH * 4 / 12 + 35 + TILE_WIDTH * 2, TILE_WIDTH, TILE_WIDTH};
    struct Button tile_66 = { SCREEN_WIDTH / 2 + 35 + TILE_WIDTH * 2, SCREEN_WIDTH * 4 / 12 + 35 + TILE_WIDTH * 2, TILE_WIDTH, TILE_WIDTH};

    struct Button Aturnleft = { SCREEN_WIDTH * 3 / 12, SCREEN_WIDTH / 12 - TILE_WIDTH * 2 / 3, TILE_WIDTH * 2 / 3, TILE_WIDTH * 2 / 3};
    struct Button Aturnright = { SCREEN_WIDTH / 2 - TILE_WIDTH * 2 / 3, SCREEN_WIDTH / 12 - TILE_WIDTH * 2 / 3, TILE_WIDTH * 2 / 3, TILE_WIDTH * 2 / 3};
    struct Button Bturnleft = { SCREEN_WIDTH / 2 + 5, SCREEN_WIDTH / 12 - TILE_WIDTH * 2 / 3, TILE_WIDTH * 2 / 3, TILE_WIDTH * 2 / 3};
    struct Button Bturnright = { SCREEN_WIDTH * 9 / 12 - TILE_WIDTH * 2 / 3, SCREEN_WIDTH / 12 - TILE_WIDTH * 2 / 3, TILE_WIDTH * 2 / 3, TILE_WIDTH * 2 / 3};
    struct Button Cturnleft = { SCREEN_WIDTH * 3 / 12, SCREEN_WIDTH * 7 / 12, TILE_WIDTH * 2 / 3, TILE_WIDTH * 2 / 3};
    struct Button Cturnright = { SCREEN_WIDTH / 2 - TILE_WIDTH * 2 / 3, SCREEN_WIDTH * 7 / 12, TILE_WIDTH * 2 / 3, TILE_WIDTH * 2 / 3};
    struct Button Dturnleft = { SCREEN_WIDTH / 2 + 5, SCREEN_WIDTH * 7 / 12, TILE_WIDTH * 2 / 3, TILE_WIDTH * 2 / 3};
    struct Button Dturnright = { SCREEN_WIDTH * 9 / 12 - TILE_WIDTH * 2 / 3, SCREEN_WIDTH * 7 / 12, TILE_WIDTH * 2 / 3, TILE_WIDTH * 2 / 3};

    //Alle Knöpfe der Oberfläche
    struct Button TicTacToeAdvancedButtons[45] = {Exit_to_Menu, tile_11, tile_12, tile_13, tile_14, tile_15, tile_16, tile_21, tile_22,tile_23, tile_24,tile_25,
    tile_26, tile_31, tile_32, tile_33, tile_34, tile_35, tile_36, tile_41, tile_42, tile_43, tile_44, tile_45, tile_46, tile_51, tile_52, tile_53,
    tile_54, tile_55, tile_56, tile_61, tile_62, tile_63, tile_64, tile_65, tile_66, Aturnleft, Aturnright, Bturnleft, Bturnright, Cturnleft, Cturnright,
    Dturnleft, Dturnright};

    SDL_Event e;

    //While application is running
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
			if(e.type == SDL_MOUSEBUTTONDOWN){

                int tile = WhichButton(TicTacToeAdvancedButtons, 45) - 1;
                switch(tile + 1){
                    case 1:
                        spieler = 2;
                        for(int i = 0; i < 6; i++){
                            for(int j = 0; j < 6; j++){
                                Feld[i][j] = 0;
                            }
                        }
                        return false;
                        break;
                    case 2:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 3:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 4:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 5:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 6:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 7:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 8:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 9:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 10:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 11:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 12:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 13:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 14:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 15:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 16:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 17:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 18:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 19:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 20:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 21:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 22:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 23:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 24:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 25:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 26:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 27:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 28:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 29:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 30:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 31:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 32:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 33:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 34:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 35:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 36:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 37:
                        TicTacToeAdvancedZug(&TicTacToeAdvancedButtons[tile], tile - 1, &spieler);
                        break;
                    case 38:
                        Drehen(TicTacToeAdvancedButtons, 1, 'l');
                        break;
                }

			}

            TicTacToeAdvancedFeld(TicTacToeAdvancedButtons);
        }

    }
}


























