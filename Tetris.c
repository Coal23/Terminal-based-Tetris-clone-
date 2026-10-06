#include "Tetris.h"
 
/* ___FUNC_INNIT/FREE__ */

char** innit_scene(){
    /*
    allocate the memory for the scene
    */
    char** tab = malloc( HIGHT * sizeof( char* ) );

    for(int i=0 ; i<HIGHT ; i++ ) {
        tab[i] = malloc( WIDTH * sizeof( char ) );

        for(int j=0 ; j<WIDTH ; j++ ) {
            tab[i][j] = ' ';
        }

    }

    return tab;
}

void free_scene( char** t ) {
    /*
    free the memory of the scene
    */

    for(int i=0 ; i<HIGHT ; i++ ) {
        free( t[i] );
    }

    free( t );
}

/* ___FUNC___ */


bool is_pos_valid( int x , int y , char** buffer ) {
    /*
    check if the area designed by the top left corner's coordinates can fit the ACTUAL tetroninum
    */
    int lim = 4;
    if( actual_tet > 1 ){ lim = 3; }
    int tempy = -1;

    for(int i=0 ; i<blocks_length[actual_tet] ; i++ ) {

        if( i % lim == 0 ) { tempy++; }

        if( actual[i] != ' ' ) {

            if( tempy + y >= HIGHT ) { return false; }

            if( i % lim + x >= WIDTH ) { return false; }

            if( i % lim + x < 0 ) { return false; }

            if( buffer[tempy + y][i % lim + x] != ' ' ) { return false; }
        }

    }

    return true;
}

void add_random_new_tet( char** scene){ 
    /*
    the moving blocks are not added to the scene, it contain only non moving blocks
    */
    actual = NEXT;
    actual_tet = next_tet;
    next_tet = rand() % 7;
    rotation = 0;
    NEXT = TETRONINUM[ next_tet ][0];

    c_x = i_currx;
    c_y = i_curry;

    if( !is_pos_valid( i_currx , i_curry , scene ) ) {
        GAME_OVER = true;
    }
}

bool move_down( char** scene ) {
    /*
    move the block one block bellow but only if the block fit in the new place return true if success
    */

    if( is_pos_valid( c_x , c_y + 1 , scene ) ) { //check if the block fit

        c_y++;
        return true;

    }
    return false;
}

void move_horizontal(char **scene, bool way) {
    /*
    move the block to the right or left if way is true or false but only if the block fit in the new place
    */
    if( way ) { //deplacement a droite

        if( is_pos_valid( c_x + 1 , c_y , scene ) ) { c_x++; } //check if the block fit

    } else { //deplacement a gauche

        if( is_pos_valid( c_x - 1 , c_y , scene ) ) { c_x--; } //check if the block fit

    }
}

void checklines( char** buffer ) {
    /*
    deal with full lines in the scene, increase the score by 1000 for every full line
    */
    int count = 0;
    bool is_full;

    for( int y=0 ; y<HIGHT ; y++ ) {
        is_full = true;

        for(int x=0 ; x<WIDTH ; x++) {
            if( buffer[y][x] == ' ' ) { is_full = false; }
        }

        if( is_full ) { 
            count++;
            
            for (int i=0 ; i<WIDTH ; i++) {
                buffer[y][i] = ' ';
            }

            for (int j=0 ; j<y ; j++) {
                for (int k=0 ; k<WIDTH ; k++) {
                    buffer[y - j][k] = buffer[y - j - 1][k];
                }    
            }
            
            

        }
    }

    SCORE += count * 1000;
}

void rotate( int act , char** buffer ){
    /*
    rotate the moving block if possible
    */

    if( act >= 1 && act <= 3 ) {

        if( rotation == 0 ) { 
            rotation = 1; 
            actual = TETRONINUM[actual_tet][rotation];

            if( !is_pos_valid( c_x , c_y , buffer ) ) { 
                rotation = 0;
                actual = TETRONINUM[actual_tet][rotation];

            }
        } else { 
            rotation = 0; 
            actual = TETRONINUM[actual_tet][rotation];

            if( !is_pos_valid( c_x , c_y , buffer ) ) { 
                rotation = 1;
                actual = TETRONINUM[actual_tet][rotation];

            }

        }

    } else if( act > 3 ) {

        if( rotation < 3 ) {
             
            rotation++; 
            actual = TETRONINUM[actual_tet][rotation];

            if( !is_pos_valid( c_x , c_y , buffer ) ) { 
                rotation--;
                actual = TETRONINUM[actual_tet][rotation];

            }

        } else { 

            rotation = 0; 
            actual = TETRONINUM[actual_tet][rotation];

            if( !is_pos_valid( c_x , c_y , buffer ) ) {
                rotation = 4; 
                actual = TETRONINUM[actual_tet][rotation];

            }
        }

    }

}

void addscene( char** buffer ){
    /*
    add the moving blocks to the scene, turning them into static blocks
    */
    int lim = 4;

    if( actual_tet > 1 ){ lim = 3; }

    int tempy = c_y -1;

    for( int i=0 ; i<blocks_length[actual_tet] ; i++ ) {

        if( i % lim == 0 ) { tempy++; }

        if( actual[i] != ' ' ) { buffer[tempy][c_x + (i % lim)] = actual[i]; }

    }
}

void process_input( char** buffer ){
    /*
    process the player's inputs with CONIO.h extension
    */
    if( !kbhit() ){
        return;
    }

    int key;

    while( kbhit() ) {
        key = getche();

        switch ( key )
        {
        case 113: //Q
            move_horizontal( buffer , false );
            break;

        case 100: //D
            move_horizontal( buffer , true );
            break;

        case 115: //S
            move_down( buffer );
            break;

        case 114: //R
            rotate( actual_tet , buffer );
            break;
        
        default:
            break;
        }

    }

}