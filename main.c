#include "Tetris.c"
#include "renderer.c"

int main() {
    system("clear"); //clear screen
    srand(time(NULL)); //important pour rand()
    char** scene = innit_scene();

    next_tet = rand() % 7;
    NEXT = TETRONINUM[ next_tet ][rotation];
    actual = NEXT;
    actual_tet = next_tet;
    
    clock_t last = clock();

    while( !GAME_OVER ) {


        clock_t now = clock();
        clock_t diff = now - last;


        if( diff >= 500000 ) {
            SCORE+=1;

            last = now;

            process_input( scene );

            if( !move_down( scene ) ) {

                addscene( scene );
                checklines( scene );
                add_random_new_tet( scene );
            }

            print_tetris( scene );

        }
    }

    free_scene( scene );
    system("clear"); //cleaqddr screen
    printf("GAME OVER\nScore : %d\n",SCORE);
    
}