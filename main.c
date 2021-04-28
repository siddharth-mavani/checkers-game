#include "Checkers.h"

int main(){
    int u[8][8];
    Game_Spec* g ;
    g = Init_Game(0,0,0,12,12,0,0);
    Init(u);

    Print_Board(u,0);

    char s[100];
    int player=-1;
    while(1){
        scanf("%s",s);
        if(strcmp(s,"MOVE")==0){Move(u,&player,g);}
        if(strcmp(s,"UNDO")==0){Undo(u,g);}
        Print_Board(u,0);
        player=-player;
        getchar();
    }
}