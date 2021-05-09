#include "Checkers.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

void get_instruction(int i, char** instruction){

    char  ins[24][100];
    strcpy(ins[0], "\t\tINSTRUCTIONS\n");
    strcpy(ins[1], "\n");
    strcpy(ins[2], "\n");
    strcpy(ins[3], "\t\t - To Move a Token: MOVE <Initial Coordinate> TO <Final Coordinate>\n");
    strcpy(ins[4], "\t\t - To Review Game: REVIEW\n");
    strcpy(ins[5], "\t\t - To Undo a move: UNDO\n");
    strcpy(ins[6], "\t\t - To Save Game: SAVE\n");
    strcpy(ins[7], "\t\t - To Update an already saved game: UPDATE\n"); 
    strcpy(ins[8], "\t\t - To Suggest All Possible Moves: SUGGEST\n");
    strcpy(ins[9], "\t\t - To Change Game Settings: SETTINGS\n");
    strcpy(ins[10], "\t\t - To Quit Game: QUIT\n");
    strcpy(ins[11], "\n");
    strcpy(ins[12], "\n");
    strcpy(ins[13], "\n");
    strcpy(ins[14], "\n");
    strcpy(ins[15], "\n");
    strcpy(ins[16], "\n");
    strcpy(ins[17], "\n");
    strcpy(ins[18], "\n");
    strcpy(ins[19], "\n");
    strcpy(ins[20], "\n");
    strcpy(ins[21], "\n");
    strcpy(ins[22], "\n");
    strcpy(ins[23], "\n");
    
    strcpy(*instruction, ins[i]);
}

void print_row(int type){

    if(type == 1){
        printf("\t  ▒▒▒▒▒░░░░░▒▒▒▒▒░░░░░▒▒▒▒▒░░░░░▒▒▒▒▒░░░░░");
    }
    if(type == 2){
        printf("\t  ░░░░░▒▒▒▒▒░░░░░▒▒▒▒▒░░░░░▒▒▒▒▒░░░░░▒▒▒▒▒");
    }

    return ;
}

void Print_Board(int u[BOARD_SIZE][BOARD_SIZE], Game_Spec* G, int Player){
    printf("\n\n\n\n\n");
    char* instruction;
    instruction = (char*)malloc(sizeof(char)*100);

    if(G -> Board_Orientation == -1){

        printf("\t    A    B    C    D    E    F    G    H \n");

        for(int i = 0 ; i < BOARD_SIZE; i++){

            if(i % 2 == 0){
                print_row(1);
            }
            else{
                print_row(2);
            }

            get_instruction(3*i, &instruction);
            printf("%s", instruction);

            printf("\t%d ", i+1);
            for(int j = 0 ; j < BOARD_SIZE ; j++){

                if ((i + j) % 2 == 1){

                    printf("░░");
                    if (u[i][j] == 0){
                        printf("░░░");
                    }
                    if (u[i][j] == 1){
                        printf("\033[1;37m");
                        printf("█");
                        printf("\033[0m");
                        printf("░░");
                    }
                    if (u[i][j] == -1){
                        printf("\033[1;30m");
                        printf("█");
                        printf("\033[0m");
                        printf("░░");
                    }
                    if (u[i][j] == 2){
                        printf("\033[1;37m");
                        printf("\b█");
                        printf("\033[0m");
                        printf("░");
                        printf("\033[1;37m");
                        printf("█");
                        printf("\033[0m");
                        printf("░");
                    }
                    if (u[i][j] == -2){
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
                print_row(1);
            }
            else{
                print_row(2);
            }

            get_instruction(3*i+2,&instruction);
            printf("%s",instruction);

        }
        printf("\t    A    B    C    D    E    F    G    H \n");
    }
    else if(G -> Board_Orientation == 1){

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
                    if (u[i][j] == 0){
                        printf("░░░");
                    }
                    if (u[i][j] == 1){
                        printf("\033[1;37m");
                        printf("█");
                        printf("\033[0m");
                        printf("░░");
                    }
                    if (u[i][j] == -1){
                        printf("\033[1;30m");
                        printf("█");
                        printf("\033[0m");
                        printf("░░");
                    }
                    if (u[i][j] == 2){
                        printf("\033[1;37m");
                        printf("\b█");
                        printf("\033[0m");
                        printf("░");
                        printf("\033[1;37m");
                        printf("█");
                        printf("\033[0m");
                        printf("░");
                    }
                    if (u[i][j] == -2){
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


void Print_Num(int u[BOARD_SIZE][BOARD_SIZE]){

    printf("A  B  C  D  E  F  G  H\n");

    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j=0 ; j < BOARD_SIZE;j++){
            printf("%2d ",u[i][j]);
        }
        printf("\n");
    }

    return ;
}