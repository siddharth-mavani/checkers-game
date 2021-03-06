#include "Checkers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>


// This Function returns a particular instruction
void get_instruction(int i, char** instruction){

    // Initialising Arrays to store instructions
    char  ins[24][INSTRUCTION_SIZE];

    // Storing all the instructions
    strcpy(ins[0], "\t\tINSTRUCTIONS\n");
    strcpy(ins[1], "\n");
    strcpy(ins[2], "\n");
    strcpy(ins[3], "\t\t - To Move a Token: MOVE <Initial Coordinate> TO <Final Coordinate>\n");
    strcpy(ins[4], "\t\t - To Review Game: REVIEW\n");
    strcpy(ins[5], "\t\t\t -> To View Next Step: N\n");
    strcpy(ins[6], "\t\t\t -> To View Previous Step: P\n");
    strcpy(ins[7], "\t\t\t -> To Quit: Q\n");
    strcpy(ins[8], "\t\t - To Undo a move: UNDO\n");
    strcpy(ins[9], "\t\t - To Save Game: SAVE\n");
    strcpy(ins[10], "\t\t - To Update an already saved game: UPDATE\n"); 
    strcpy(ins[11], "\t\t - To Suggest All Possible Moves: SUGGEST\n");
    strcpy(ins[12], "\t\t - To Change Game Settings: SETTINGS\n");
    strcpy(ins[13], "\t\t - To Quit Game: QUIT\n");
    strcpy(ins[14], "\t\t\t -> To Save Game: SAVE\n");
    strcpy(ins[15], "\t\t\t -> To Update Game: UPDATE\n");
    strcpy(ins[16], "\t\t\t -> To Quit Game: QUIT\n");
    strcpy(ins[17], "\t\t - To View Next K Steps: NEXTK\n");
    strcpy(ins[18], "\t\t\t -> <k>\n");
    strcpy(ins[19], "\n");
    strcpy(ins[20], "\n");
    strcpy(ins[21], "\n");
    strcpy(ins[22], "\n");
    strcpy(ins[23], "\n");
    
    strcpy(*instruction, ins[i]);
}

// Prints Rows of the Board
void print_row(int type){

    if(type == 1){
        printf("\t  ▒▒▒▒▒░░░░░▒▒▒▒▒░░░░░▒▒▒▒▒░░░░░▒▒▒▒▒░░░░░");         //rows  which start with lighter square
    }
    if(type == 2){
        printf("\t  ░░░░░▒▒▒▒▒░░░░░▒▒▒▒▒░░░░░▒▒▒▒▒░░░░░▒▒▒▒▒");         //rows which start with darker square
    }

    return ;
}

// This Function Prints the Current State of the Board
void Print_Board(int Board[BOARD_SIZE][BOARD_SIZE], Game_Spec* G, int Player){
    printf("\n\n\n\n\n");
    char* instruction;                                  // this string store the instruction printed on the right-side of board
    instruction = (char*)malloc(sizeof(char)*100);

    if(G -> Board_Orientation == -1){

        printf("\t    A    B    C    D    E    F    G    H \n");          //for  coordinates

        for(int i = 0 ; i < BOARD_SIZE; i++){

            if(i % 2 == 0){                                             //for every iteration of i we print 3 lines
                print_row(1);                                           // 1 line above the peices, 1 below
            }                                                           // here we check whether we need to prive line of type 1 or 2        
            else{
                print_row(2);
            }

            get_instruction(3*i, &instruction);                         // here we copy the instruction we need to print in the instruction sring
            printf("%s", instruction);                                  // we print instruction here

            printf("\t%d ", i+1);                                       
            for(int j = 0 ; j < BOARD_SIZE ; j++){

                if ((i + j) % 2 == 1){                                  // since we only ned to print the peices every alternate block   

                    printf("░░");                       
                    if (Board[i][j] == EMPTY){                          // we print different charachters for different type of peices
                        printf("░░░");
                    }
                    if (Board[i][j] == WHITE){
                        printf("\033[1;37m");
                        printf("█");
                        printf("\033[0m");
                        printf("░░");
                    }
                    if (Board[i][j] == BLACK){
                        printf("\033[1;30m");
                        printf("█");
                        printf("\033[0m");
                        printf("░░");
                    }
                    if (Board[i][j] == WHITE_KING){
                        printf("\033[1;37m");
                        printf("\b█");
                        printf("\033[0m");
                        printf("░");
                        printf("\033[1;37m");
                        printf("█");
                        printf("\033[0m");
                        printf("░");
                    }
                    if (Board[i][j] == BLACK_KING){
                        printf("\033[1;30m");
                        printf("\b█");
                        printf("\033[0m");
                        printf("░");
                        printf("\033[1;30m");
                        printf("█");
                        printf("\033[0m");
                        printf("░");
                    }
                }
                else{
                    printf("▒▒▒▒▒");
                }
            }

            get_instruction(3*i+1, &instruction);
            printf(" %d", i+1);
            printf("%s", instruction);

            if(i % 2 == 0){
                print_row(1);                   // here we print the line below the peices
            }
            else{
                print_row(2);
            }

            get_instruction(3*i+2,&instruction);        
            printf("%s",instruction);

        }
        printf("\t    A    B    C    D    E    F    G    H \n");
    }
    else if(G -> Board_Orientation == 1){                       // if we want to print inverted board we change board-orientation 
                                                                // traverse the board in reverse order
                                                                
        printf("\t    H    G    F    E    D    C    B    A \n");

        for(int i = BOARD_SIZE  - 1 ; i >= 0; i--){

            if(i % 2 == 1){
                print_row(1);
            }
            else{
                print_row(2);
            }

            get_instruction(3 * (BOARD_SIZE  - 1-i), &instruction);
            printf("%s", instruction);
            
            printf("\t%d ", i+1);
            for(int j = BOARD_SIZE  - 1; j >= 0; j--){

                if ((i + j) % 2 == 1)
                {
                    printf("░░");
                    if (Board[i][j] == EMPTY){
                        printf("░░░");
                    }
                    if (Board[i][j] == WHITE){
                        printf("\033[1;37m");
                        printf("█");
                        printf("\033[0m");
                        printf("░░");
                    }
                    if (Board[i][j] == BLACK){
                        printf("\033[1;30m");
                        printf("█");
                        printf("\033[0m");
                        printf("░░");
                    }
                    if (Board[i][j] == WHITE_KING){
                        printf("\033[1;37m");
                        printf("\b█");
                        printf("\033[0m");
                        printf("░");
                        printf("\033[1;37m");
                        printf("█");
                        printf("\033[0m");
                        printf("░");
                    }
                    if (Board[i][j] == BLACK_KING){
                        printf("\033[1;30m");
                        printf("\b█");
                        printf("\033[0m");
                        printf("░");
                        printf("\033[1;30m");
                        printf("█");
                        printf("\033[0m");
                        printf("░");
                    }
                }
                else{
                    printf("▒▒▒▒▒");
                }
            }

            printf(" %d", i+1);
            get_instruction(3 * (BOARD_SIZE -1 - i) + 1, &instruction);
            printf("%s",instruction);

            if(i%2==1){
                print_row(1);
            }
            else{
                print_row(2);
            }

            get_instruction(3 * (BOARD_SIZE  - 1 - i) + 2, &instruction);
            printf("%s", instruction);
        }
        printf("\t    H    G    F    E    D    C    B    A \n");
    }

    // Printing Player Turn
    if (Player > 0){
        printf("\n\t %s's Chance\t\t\t%s PLAYS WHITE \n", G -> Name_Of_Player2, G -> Name_Of_Player2);
    }
    else if (Player < 0){
        printf("\n\t %s's CHANCE\t\t\t%s PLAYS BLACK \n", G -> Name_Of_Player1, G -> Name_Of_Player1);
    }
    printf("\n\n\n\n\n");
    return ;
}


