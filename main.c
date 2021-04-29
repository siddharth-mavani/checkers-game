#include "Checkers.h"

int main()
{
    
    // Printing the Start Menu of the Game
    printf("\n\n\t\t Checkers Game\n\n");
    printf("\t 1. Start New Game\n");
    printf("\t 2. Continue Saved Game\n");
    printf("\t 3. Game Settings\n\n");

    int choice;                                                         // This variable will store the choice entered by the user
    printf("\t Enter your Choice: ");                                   // Asking user to enter choice
    scanf(" %d", &choice);                                              // Inputting user choice

    
    // Initialising Variables for Different Variations of the Game
    int Auto_Rotate = 0, Compulsory_Capture = 0;                                           
    int Num_Black = 12, Num_White = 12, Num_White_Kings = 0, Num_Black_Kings = 0;

    if(choice == 1){                                                    // Checks if User wants to Start New Game

            int u[8][8];                                                // Initialising the Game Board                            
            Game_Spec *G;                                               // This is pointer to Game_Spec, which is Linked List that Stores Game Data

            // Initialising Game
            G = Init_Game(Auto_Rotate, Compulsory_Capture, 0, Num_Black, Num_White, Num_Black_Kings, Num_White_Kings);
            Init(u);
            
            printf("\n\n");                         
            Print_Board(u, 0);                                          // Printing Game Board

            char Command[100];                                          // This Variable Stores the Command entered by the User
            int Player = -1;                                            // This Variable Stores which Player is Playing the Game (1/-1)

            while (1){

                scanf("%s", Command);                                   // Inputting the Command from the User

                if (strcmp(Command, "MOVE") == 0){                      // Checks if input is 'MOVE'
                    Move(u, &Player, G);                                // If input is 'MOVE', it calls the 'Move' function
                }
                else if (strcmp(Command, "UNDO") == 0){                 // Checks if input is 'UNDO'
                    Undo(u, G);                                         // If input is 'UNDO', it calls the 'Undo' function
                }
                else if (strcmp(Command, "SAVE") == 0){                 // Checks if input is 'SAVE'
                    Save(u, Player, G);                                 // If input is 'SAVE', it calls the 'Save' function
                }
                else if (strcmp(Command, "QUIT") == 0){                 // Checks if input is 'QUIt'
                    
                    char s[5];                                          // This variable stores input
                    printf("Do you want to Save the Game ?");           // Ask the User if he wants to Save the Game 
                    scanf(" %s", s);                                    // Inputting user choice

                    if (strcmp(s, "YES") == 0){                         // Checks if input is 'YES'
                        Save(u, Player, G);                             // if input is 'YES', it calls the 'Save' function
                        return 0;                                       // Exits Game
                    }

                    return 0;                                           // Exits Game
                }

                Print_Board(u, 0);                                      // Prints Board at the end of each Command
                Player = -Player;                                       // Toggles player( 1 -> -1 and -1 -> 1 )
                getchar();                                              // Clears input buffer
            }
    }
    else if(choice == 2){                                               // Checks if User wants to Load a Saved Game

            int u[8][8];                                                // Initialising the Game Board and Player
            int Player;                                                 // Initialising Player
            Game_Spec* G;                                               // This is pointer to Game_Spec, which is Linked List that Stores Game Data

            char Name_Of_Game[105];                                     // This variable stores Game name
            printf("\t Enter Name of the Game: ");                      // Asking for Game Namae
            scanf(" %s", Name_Of_Game);                                 // Inputting the Game Name

            strcat(Name_Of_Game, ".txt");                               // Game will be stored as <Name_Of_Game>.txt 

            Load_Saved_Game(Name_Of_Game, G, u, &Player);               // Calling the 'Load_Saved_Game' Function

    }

    printf("\n\n");
    return 0;
}
            
