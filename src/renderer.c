#include "Tetris.h"

void print_tetris( char** tab ) {
    /*
    print the scene and the ACTUAL tetroninum at the right coordinate
    */

    int lim = 4;
    if( actual_tet > 1 ) { lim = 3; }
    int limv = 3;
    if( actual_tet == 1) { limv = 4; }

    int nextlim = 4;
    if( next_tet > 1 ) { nextlim = 3; }
    int nextlimv = 3;
    if( next_tet == 1) { nextlimv = 4; }

    int tempy = c_y;
    int tempx = c_x;
    int X = c_x;

    if(tempx < 0) { 
        tempx++;
        X++;
    }

    system("clear"); //clear screen
    printf("SCORE : %d \n", SCORE );
    printf("#___________________________# NEXT BLOCK:\n");

    for(int i=0 ; i<HIGHT ; i++ ) {
        printf("#| ");

        for(int j=0 ; j<WIDTH ; j++ ) {

            if( tempx > c_x + lim || tempx > WIDTH - 1) {
                    tempy++;
                    tempx = X;
                
            }
 
            if( i == tempy && j == tempx && tempy < c_y + limv ) {

                if( actual[lim * (tempy - c_y) + (tempx - c_x)] != ' ' && tempx < c_x + lim ) {
                    printf("%c ", actual[ lim * (tempy - c_y) + (tempx - c_x)] );

                }else {
                    printf("%c ", tab[i][j] );

                }

                tempx++;

            }else {
                printf("%c ", tab[i][j] );
            }

        }

        printf("|#");
        if( i<nextlimv ) {
            printf("|");
            for(int k=0 ; k<nextlim ; k++ ) {
                printf("%c", NEXT[nextlim * i + k] );
            }
            printf("|#");
        }
        if( i == nextlimv ) {
            printf("######");
        }
        printf("\n");
    }

    printf("#############################\n");
}
