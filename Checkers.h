#ifndef __CHECKERS_H__
#define __CHECKERS_H__

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

#define EMPTY 0
#define WHITE 1
#define BLACK -1
#define WHITE_KING  2
#define BLACK_KING -2


typedef struct Change
{
    char Initial_Char ;
    char Final_Char;
    int Initial_Int ;
    int Final_Int;
    int Type;                               //store the type of token which was moved
    int Kill;                               // kill=1 , if that move involved any capture otherwise its 0
    int Kill_Type;                          //kill_type stores the type of token which was captured (this helps in the  undo func)
    int Change_To_King ;
    struct Change* Next;                    // since its a linked list
    struct Change* Prev;

}Move_Node;
                                                
typedef struct Game_Spec                    // this struct stores basic info
{
    int Auto_Rotate;
    int Compulsory_Capture;
    int Num_Moves;
    int Num_Black;
    int Num_White;
    int Num_Black_King;
    int Num_White_King;
    int Board_Orientation;
    char Name_Of_Player1[100];
    char Name_Of_Player2[100]; 
    struct Change* Moves;                 // this is the linked list which stores all the moves
    struct Change* Last_Move;             // this points to the last move , (helps in UNDO func)  

}Game_Spec;


//checkers.c
Move_Node* Makenode(void);
Game_Spec* Init_Game(int Auto_Rotate, int Compulsory_Capture, int Num_Moves, int Num_Black, int Num_White, int Num_Black_King, int Num_White_King, int Board_Orientation, char Name_Of_Player1[100], char Name_Of_Player2[100]);
void Insert_move(Game_Spec* Game, char Initial_Char, char Final_Char, int Initial_Int, int Final_Int, int Type, int Kill, int Kill_type , int Change_To_King);

int Undo(int u[8][8], struct Game_Spec *G , int* Player);
int CheckMove(int u[8][8],int n1, int c1, int n2, int c2, int d, int player);    // c1 is letter1,c2 is letter 2, n1,n2 are the first and the second numbers
void Init(int u[8][8]);
int Move(int u[8][8],int* player, Game_Spec* G , int Undo_Call);
void Save(int u[8][8], int Player, Game_Spec* G);                                   // Allows user to Save the Current Game 
Game_Spec* Load_Saved_Game(char Name_Of_Game[105], int u[8][8], int *Player);       // Allows user to Reload a Saved Game
void Play_Game(int u[8][8], int *Player, Game_Spec *G);                             // This Function simulates the Game
int Name_Is_Available(char Name_Of_Game[105]);
void suggest(int u[8][8],int player);
bool PossibleMoves(char c,int x, int board[8][8],int player,bool print); //Checks if moves are possible for a specific piece and can print them 
bool endgame(Game_Spec* G,int u[8][8], int Player); //Checks if the game has ended

// Print_Board.c
void Print_Board(int u[8][8], Game_Spec* Game, int Player);
void Print_Num(int u[8][8]);
void print_ll(Game_Spec *g);

#endif