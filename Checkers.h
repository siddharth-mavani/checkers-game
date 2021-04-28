#ifndef __CHECKERS_H__
#define __CHECKERS_H__

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

#define empty 0
#define white 1
#define black -1
#define white_king  2
#define black_king -2


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
    struct Change* Moves;                 // this is the linked list which stores all the moves
    struct Change* Last_Move;             // this points to the last move , (helps in UNDO func)  
}Game_Spec;

//checkers.c
Move_Node* Makenode(void);
Game_Spec* Init_Game(int auto_rotate, int compulsory_capture, int num_moves, int num_black, int num_white, int num_black_king, int num_white_king);
void Insert_move(Game_Spec* game, char initial_char, char final_char, int initial_int, int final_int, int type, int Kill, int Kill_type , int Change_To_King);

void Undo(int u[8][8] , struct Game_Spec* g);
int CheckMove(int u[8][8],int n1, int c1, int n2, int c2, int d, int player);    // c1 is letter1,c2 is letter 2, n1,n2 are the first and the second numbers
void Init(int u[8][8]);
void Move(int u[8][8],int* player, Game_Spec* g);

void Print_Board(int u[8][8],int r);
void Print_Num(int u[8][8]);

#endif