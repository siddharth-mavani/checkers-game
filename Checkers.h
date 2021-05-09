#ifndef __CHECKERS_H__
#define __CHECKERS_H__

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

#define BOARD_SIZE 8

#define EMPTY 0
#define WHITE 1
#define BLACK -1
#define WHITE_KING  2
#define BLACK_KING -2


typedef struct Change                       // This structure stores the Moves as a node with all the necesaary data.
{
    char Initial_Char ;                     // The character co-ordinate of the initial square.
    char Final_Char;                        // The character co-ordinate of the final square.
    int Initial_Int ;                       // The integer co-ordinate of the initial square.
    int Final_Int;                          // The integer co-ordinate of the final square.
    int Type;                               // Store the type of token which was moved, that is, black/white/black king/white king.
    int Kill;                               // Kill = 1/0 , if that move involves any capture otherwise kill = 1 or else it is 0.
    int Kill_Type;                          // Kill_type stores the type of token which was captured (this helps in the UNDO func).
    int Change_To_King ;                    // Stores 1 if the move changed the token to a king.
    struct Change* Next;                    // Pointer to the next node(Move).
    struct Change* Prev;                    // Pointer to the previous node(MOVE).

}Move_Node;
                                                
typedef struct Game_Spec                    // this structure stores the game information.
{
    int Auto_Rotate;                        // Stores 1 if the auto-rotate feature of the game is ON, else it stores 0.
    int Compulsory_Capture;                 // Stores 1 if the compulsory capture setting is ON, else it stores 0.
    int Num_Moves;                          // Stores the number of moves played in the game.
    int Num_Black;                          // Stores the number of black tokens (not including black king).
    int Num_White;                          // Stores the number of white tokens (not including white king).
    int Num_Black_King;                     // Stores the number of black kings.
    int Num_White_King;                     // Stores the number of white kings.
    int Board_Orientation;                  // A variable used to set the board orientation either to white's perspective (stores 1)/ black's perspective (stores -1).
    char Name_Of_Player1[100];              // Stores the name of player 1.
    char Name_Of_Player2[100];              // Stores the name of player 2 .   
    struct Change* Moves;                   // Linked List pointing to the moves stored as DOUBLY LINKED LIST.
    struct Change* Last_Move;               // Pointer to the last node (Move)(helps in UNDO func).  

}Game_Spec;

typedef struct Node{
    int Num_B_Capture ;
    int Num_W_Capture ; 
    Game_Spec* G ;
} Vertex;



//checkers.c

Move_Node* Makenode(void);

Game_Spec* Init_Game(int Auto_Rotate, int Compulsory_Capture, int Num_Moves, int Num_Black, int Num_White, int Num_Black_King, int Num_White_King, int Board_Orientation, char Name_Of_Player1[100], char Name_Of_Player2[100]);

void Insert_move(Game_Spec* Game, char Initial_Char, char Final_Char, int Initial_Int, int Final_Int, int Type, int Kill, int Kill_type , int Change_To_King);

int Undo(int u[BOARD_SIZE][BOARD_SIZE], struct Game_Spec *G , int* Player, int CallNextKMoves);

int CheckMove(int u[BOARD_SIZE][BOARD_SIZE],int n1, int c1, int n2, int c2, int d, int player);                 // c1 is letter1,c2 is letter 2, n1,n2 are the first and the second numbers

void Init(int u[BOARD_SIZE][BOARD_SIZE]);

int Move(int u[BOARD_SIZE][BOARD_SIZE],int* player, Game_Spec* G , int Undo_Call );

void Save(int u[BOARD_SIZE][BOARD_SIZE], int Player, Game_Spec* G, char Name_Of_Game[106]);                     // Allows user to Save the Current Game

void Update_gamefile(int u[BOARD_SIZE][BOARD_SIZE], int Player, Game_Spec* G, char Name_Of_Game[106]);          // Allows user to Update an already saved game.                          

Game_Spec* Load_Saved_Game(char Name_Of_Game[105], int u[BOARD_SIZE][BOARD_SIZE], int *Player);                 // Allows user to Reload a Saved Game

void Play_Game(int u[BOARD_SIZE][BOARD_SIZE], int *Player, Game_Spec *G);                                       // This Function simulates the Game

int Name_Is_Available(char Name_Of_Game[105]);

void suggest(int u[BOARD_SIZE][BOARD_SIZE],int player,Game_Spec* G);

bool PossibleMoves(char c,int x, int board[BOARD_SIZE][BOARD_SIZE],int player,bool print,bool capture);         //Checks if moves are possible for a specific piece and can print them 

bool endgame(Game_Spec* G,int u[BOARD_SIZE][BOARD_SIZE], int Player);                                           //Checks if the game has ended

void Next_K_Moves(int u[BOARD_SIZE][BOARD_SIZE], int player,int k ,Game_Spec* G);

bool Capturepossible(int u[BOARD_SIZE][BOARD_SIZE],int player);

void game_review(struct Game_Spec *g, int* Player);


// Print_Board.c
void Print_Board(int u[BOARD_SIZE][BOARD_SIZE], Game_Spec* Game, int Player);

void Print_Num(int u[BOARD_SIZE][BOARD_SIZE]);

void print_ll(Game_Spec *g);

#endif