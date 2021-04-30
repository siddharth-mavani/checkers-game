#include "Checkers.h"

// This function returns 1 if Game is availabe, 0 otherwise
int Name_Is_Available(char Name_Of_Game[105]){

    FILE* fp;                                                           // Pointer to file

    fp = fopen(Name_Of_Game, "r");                                      // Opens file in Read_Mode
    if(fp == NULL)      return 0;                                       // fp is NULL if <Name_Of_Game> is not available
    else                return 1;

    fclose(fp);                                                         // Closes file
}

int main()
{
    while(1){
    
        // Printing the Start Menu of the Game
        printf("\n\n\t\t Checkers Game\n\n");
        printf("\t 1. Start New Game\n");
        printf("\t 2. Continue Saved Game\n");
        printf("\t 3. Game Settings\n");
        printf("\t 4. Exit Game\n\n");

        int choice;                                                         // This variable will store the choice entered by the user
        printf("\t Enter your Choice: ");                                   // Asking user to enter choice
        scanf(" %d", &choice);                                              // Inputting user choice

        
        // Initialising Variables for Different Variations of the Game
        int Auto_Rotate = 0, Compulsory_Capture = 0, Player = -1;                                           
        int Num_Black = 12, Num_White = 12, Num_White_Kings = 0, Num_Black_Kings = 0;

        if(choice == 1){                                                    // Checks if User wants to Start New Game

                int u[8][8];                                                // Initialising the Game Board                            
                Game_Spec *G;                                               // This is pointer to Game_Spec, which is Linked List that Stores Game Data

                
                // Initialising Game
                G = Init_Game(Auto_Rotate, Compulsory_Capture, 0, Num_Black, Num_White, Num_Black_Kings, Num_White_Kings);
                Init(u);
                
                Play_Game(u, &Player, G);                                   // This Function simulates the Game

        }
        else if(choice == 2){                                               // Checks if User wants to Load a Saved Game

                int u[8][8];                                                // Initialising the Game Board and Player
                int Player;                                                 // Initialising Player
                Game_Spec* G;                                               // This is pointer to Game_Spec, which is Linked List that Stores Game Data

                char Name_Of_Game[105];                                     // This variable stores Game name
                printf("\t Enter Name of the Game: ");                      // Asking for Game Namae
                scanf(" %s", Name_Of_Game);                                 // Inputting the Game Name

                strcat(Name_Of_Game, ".txt");                               // ".txt" will be added to the end of <Name_Of_Game> 

                // Checking if the Game exists    
                while(!Name_Is_Available(Name_Of_Game)){

                        printf("\t The Game does not exist, please enter a valid name: ");
                        scanf(" %s", Name_Of_Game);                         // Inputting the Game Name

                        strcat(Name_Of_Game, ".txt");                       // ".txt" will be added to the end of <Name_Of_Game>  
                
                }

                G = Load_Saved_Game(Name_Of_Game, u, &Player);              // Calling the 'Load_Saved_Game' Function
                Play_Game(u, &Player, G);                                   // This Function simulates the Game
        
        }
        else if(choice == 4){                                               // Checks if User wants to Exit the Game

                printf("\t Thank you for playing this game, hope you enjoyed :) ");
                break;                                                    // Exits the loop

        }
    }

    printf("\n\n");
    return 0;
}
            
