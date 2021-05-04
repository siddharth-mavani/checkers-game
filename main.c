#include "Checkers.h"

int main()
{
        // Initialising Variables for Different Variations of the Game
        int Auto_Rotate = 1, Compulsory_Capture = 0, Player = -1;                                           
        int Num_Black = 12, Num_White = 12, Num_White_Kings = 0, Num_Black_Kings = 0;
    while(1){
    
        // Printing the Start Menu of the Game
        printf("\n\n\t\t Checkers Game\n\n");
        printf("\t 1. Start New Game\n");
        printf("\t 2. Continue Saved Game\n");
        printf("\t 3. Game Settings\n");
        printf("\t 4. Exit Game\n\n");

        int choice;                                                        
        printf("\t Enter your Choice: ");                                   
        scanf(" %d", &choice);                                              
        printf("\n");
        

        if(choice == 1){                                                    
                
                // Initialising Game board and Linked List
                int u[8][8];                                                                        
                Game_Spec *G;
                
                // Initialising Game
                G = Init_Game(Auto_Rotate, Compulsory_Capture, 0, Num_Black, Num_White, Num_Black_Kings, Num_White_Kings);
                Init(u);
                
                Play_Game(u, &Player, G);                                   // This Function simulates the Game

        }
        else if(choice == 2){                                               

                // Initialising Game board and Linked List
                int u[8][8], Player;                                                 
                Game_Spec* G;

                char Name_Of_Game[105];                                     
                printf("\t Enter Name of the Game: ");                      
                scanf(" %s", Name_Of_Game);                                 

                strcat(Name_Of_Game, ".txt");                               

                // Checking if the Game exists    
                while(!Name_Is_Available(Name_Of_Game)){

                        printf("\t The Game does not exist, please enter a valid name: ");
                        scanf(" %s", Name_Of_Game);                         

                        strcat(Name_Of_Game, ".txt");                         
                
                }

                G = Load_Saved_Game(Name_Of_Game, u, &Player);              
                Play_Game(u, &Player, G);                                   // This Function simulates the Game
        
        }
        else if(choice == 3){

                 
                int choice;
                while(1){

                        printf("\t\t 1. Auto Rotatoe: %s \n", (Auto_Rotate > 0) ?  "ON" :  "OFF");
                        printf("\t\t 2. Compulsory Capture: %s \n", (Compulsory_Capture > 0) ?  "ON" :  "OFF");
                        printf("\t\t 3. Back to Main Menu \n\n");
                                                                                
                        printf("\t\t Enter your Choice: ");                                   
                        scanf(" %d", &choice);

                        if(choice == 1){

                                char s[5];
                                printf("\t\t Do you want Auto Rotate to be ON ? ");
                                scanf(" %s", s);
                                printf("\n");

                                if(strcmp(s, "YES") == 0 || strcmp(s, "Y") == 0 || strcmp(s, "yes") == 0 || strcmp(s, "y") == 0){
                                        Auto_Rotate = 1;
                                }
                                else
                                        Auto_Rotate = 0;
                        }
                        else if(choice == 2){

                                char s[5];
                                printf("\t\t Do you want Compulsory Capture to be ON ? ");
                                scanf(" %s", s);
                                printf("\n");

                                if(strcmp(s, "YES") == 0 || strcmp(s, "Y") == 0 || strcmp(s, "yes") == 0 || strcmp(s, "y") == 0){
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

                printf("\t Thank you for playing this game, hope you enjoyed :) ");
                break;                                                    

        }
    }

    printf("\n\n");
    return 0;
}
            
