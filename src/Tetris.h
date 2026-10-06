#ifndef ___TERIS___
#define ___TERIS___

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

/* ___BLOCKS___ 

    The tetroninum are represented by an array, there is one array for every rotation
    TETRONINUM is a 3D array that contains every 2D arrays of every rotation of every single tetroninum
*/

char T1_O[12] = {' ','O','O',' ',' ','O','O',' ',' ',' ',' ',' '}; // O
char* T_O[1] = { T1_O };

char T1_I[16] = {' ','I',' ',' ',' ','I',' ',' ',' ','I',' ',' ',' ','I',' ',' '}; // I
char T2_I[16] = {' ',' ',' ',' ',' ',' ',' ',' ','I','I','I','I',' ',' ',' ',' '}; // I
char* T_I[2] = { T1_I , T2_I }; 

char T1_S[9] = {' ','S','S','S','S',' ',' ',' ',' '}; //S
char T2_S[9] = {' ','S',' ',' ','S','S',' ',' ','S'}; //S
char* T_S[2] = { T1_S , T2_S };

char T1_Z[9] = {'Z','Z',' ',' ','Z','Z',' ',' ',' '}; //Z
char T2_Z[9] = {' ','Z',' ','Z','Z',' ','Z',' ',' '}; //Z
char* T_Z[2] = { T1_Z , T2_Z };

char T1_T[9] = {' ',' ',' ','T','T','T',' ','T',' '}; //T
char T2_T[9] = {' ','T',' ','T','T',' ',' ','T',' '}; //T
char T3_T[9] = {' ','T',' ','T','T','T',' ',' ',' '}; //T
char T4_T[9] = {' ','T',' ',' ','T','T',' ','T',' '}; //T
char* T_T[4] = { T1_T , T2_T , T3_T , T4_T };

char T1_L[9] = {' ','L',' ',' ','L',' ',' ','L','L'}; //L
char T2_L[9] = {' ',' ',' ','L','L','L','L',' ',' '}; //L
char T3_L[9] = {'L','L',' ',' ','L',' ',' ','L',' '}; //L
char T4_L[9] = {' ',' ','L','L','L','L',' ',' ',' '}; //L
char* T_L[4] = { T1_L , T2_L , T3_L , T4_L };

char T1_J[9] = {' ','J',' ',' ','J',' ','J','J',' '}; //J
char T2_J[9] = {'J',' ',' ','J','J','J',' ',' ',' '}; //J
char T3_J[9] = {' ','J','J',' ','J',' ',' ','J',' '}; //J
char T4_J[9] = {' ',' ',' ','J','J','J',' ',' ','J'}; //J
char* T_J[4] = { T1_J , T2_J , T3_J , T4_J };

char** TETRONINUM[7] = { T_O , T_I , T_S , T_Z , T_T , T_L , T_J }; //all blocks are here
int blocks_length[7] = {12,16,9,9,9,9,9}; //the lenghts of the arrays of the blocks, same order as in TETRONINUM

/* ___CONST___ */

//size of the scene, can be edited but may cause bugs
const int HIGHT = 20, WIDTH = 12; 

//coordinate of the spawn point
const int i_currx = 4, i_curry = 0;

/* ___GLOBAL-VAR___ */

//actual coordinate of the moving block 
int c_y = i_curry, c_x = i_currx;

char* NEXT; //array of the NEXT tetroninum
char* actual = NULL; //array of the ACTUAL tetroninum
int SCORE = 0; //score of the player

bool GAME_OVER = false; //game continue while this variable is set to false

int actual_tet; //id of the ACTUAL tetroninum
int next_tet; //id of the NEXT tetroninum
int rotation = 0; //id of the actual rotation of the ACTUAL tetroninum

/* ___FUN___ */

void print_tetris( char** tab ); //print the scene and the ACTUAL tetroninum at the right coordinate( c_y , c_x )

bool is_pos_valid( int currx , int curry , char** buffer); //check if the area designed by the top left corner's coordinates can fit the ACTUAL tetroninum

void add_random_new_tet( char** buffer); //the moving blocks are not added to the scene, it contain only non moving blocks

bool move_down( char** buffer ); //move the block one block bellow but only if the block fit in the new place return true if success

char** innit_scene(); //allocate the memory for the scene

void free_scene( char** tab ); //free the memory of the scene

void process_input( char** buffer ); //process the player's inputs with CONIO.h extension

void rotate( int act , char** buffer ); //rotate the moving block if possible

void move_horizontal(char **scene, bool way); //move the block to the right or left if way is true or false but only if the block fit in the new place

void checklines( char** buffer ); //deal with full lines in the scene, increase the score by 1000 for every full line

void addscene( char** buffer ); //add the moving blocks to the scene, turning them into static blocks

#endif
