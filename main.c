#include "Checkers.h"

int main()
{
        // Initialising Variables for Different Variations of the Game
        int Auto_Rotate = 0, Compulsory_Capture = 1, Player = -1, Board_Orientation = 1;                                           
        int Num_Black = 12, Num_White = 12, Num_White_Kings = 0, Num_Black_Kings = 0, Num_Moves = 0;
        char Name_Of_Player1[NAME_SIZE], Name_Of_Player2[NAME_SIZE];

        while(1){
START:    
                // Printing the Start Menu of the Game
                printf("\n\n\t\t CHECKERS GAME\n\n");
                printf("\t 1. START NEW GAME\n");
                printf("\t 2. CONTINUE SAVED GAME\n");
                printf("\t 3. GAME SETTINGS\n");
                printf("\t 4. EXIT GAME\n\n");

                int choice;                                                        
                printf("\t ENTER YOUR CHOICE: ");                                   
                scanf(" %d", &choice);                                              
                printf("\n");
                

                if(choice == 1){                                                    
                        
                        // Initialising Game board and Linked List
                        int u[BOARD_SIZE][BOARD_SIZE];                                                                        
                        Game_Spec *G;

                        printf("\t ENTER NAME OF PLAYER 1: ");
                        scanf(" %s", Name_Of_Player1);
                        printf("\t ENTER NAME OF PLAYER 2: ");
                        scanf(" %s", Name_Of_Player2);
                        
                        // Initialising Game
                        G = Init_Game(Auto_Rotate, Compulsory_Capture, Num_Moves, Num_Black, Num_White, Num_Black_Kings, Num_White_Kings, Board_Orientation, Name_Of_Player1, Name_Of_Player2);
                        Init(u);

                        Play_Game(u, &Player, G);                                   // This Function simulates the Game

                }
                else if(choice == 2){                                               

                        // Initialising Game board and Linked List
                        int u[BOARD_SIZE][BOARD_SIZE], Player;                                                 
                        Game_Spec* G;

                        char Name_Of_Game[NAME_SIZE];                                     
                        printf("\t ENTER NAME OF GAME: ");                      
                        scanf(" %s", Name_Of_Game);

                        if(strcmp(Name_Of_Game, "BACK") == 0){                      // Checks if 'BACK' is inputted
                                continue;                                           // Goes Back to Main Menu    
                        }                                 

                        strcat(Name_Of_Game, ".txt");                               // Game will be stored as <Name_Of_Game>.txt

                        // Checking if the Game exists    
                        while(!Name_Is_Available(Name_Of_Game)){

                                printf("\t THE GAME DOES NOT EXIST, PLEASE ENTER A VALID NAME: ");
                                scanf(" %s", Name_Of_Game);

                                if(strcmp(Name_Of_Game, "BACK") == 0){              // Checks if 'BACK' is inputted 
                                        goto START;                                 // Goes Back to Main Menu    
                                }                                       

                                strcat(Name_Of_Game, ".txt");                       // Game will be stored as <Name_Of_Game>.txt
                        
                        }

                        G = Load_Saved_Game(Name_Of_Game, u, &Player);  
                        Play_Game(u, &Player, G);                                   // This Function simulates the Game
                
                }
                else if(choice == 3){

                        int choice;
                        while(1){

                                printf("\t\t 1. AUTO ROTATE: %s \n", (Auto_Rotate > 0) ?  "ON" :  "OFF");                      // Prints if Auto Rotate is On or Off
                                printf("\t\t 2. COMPULSORY CAPTURE: %s \n", (Compulsory_Capture > 0) ?  "ON" :  "OFF");         // Prints if Compulsory Capture is On or Off
                                printf("\t\t 3. BACK TO MAIN MEUNU\n\n");
                                                                                        
                                printf("\t\t ENTER YOUR CHOICE: ");                                   
                                scanf(" %d", &choice);

                                if(choice == 1){

                                        char s[5];
                                        printf("\t\t DO YOU WANT AUTO ROTATE TO BE ON ? ");
                                        scanf(" %s", s);
                                        printf("\n");
                                        
                                        // Checks if User wants Auto Rotate to be ON
                                        if(strcmp(s, "YES") == 0 || strcmp(s, "Y") == 0 || strcmp(s, "yes") == 0 || strcmp(s, "y") == 0){
                                                Auto_Rotate = 1;
                                        }
                                        else
                                                Auto_Rotate = 0;
                                }
                                else if(choice == 2){

                                        char permission[5];
                                        printf("\t\t DO YOU WANT COMPULSORY CAPTURE TO BE ON ? ");
                                        scanf(" %s", permission);
                                        printf("\n");

                                        // Checks if User wants Compulsory Capture to be ON
                                        if(strcmp(permission, "YES") == 0 || strcmp(permission, "Y") == 0 || strcmp(permission, "yes") == 0 || strcmp(permission, "y") == 0){
                                                Compulsory_Capture = 1;
                                        }
                                        else{
                                                Compulsory_Capture = 0;
                                        }

                                }
                                else{
                                        break;
                                }
                        }

                }
                else if(choice == 4){                                               

                        printf("\t THANK YOU FOR PLAYING THIS GAME, HOPE YOU ENJOYED :) ");
                        break;                                                    

                }
        }

    printf("\n\n");
    return 0;
}