#include "Checkers.h"

void print_row(int type){
    if(type==1){printf("\t  ▒▒▒▒▒░░░░░▒▒▒▒▒░░░░░▒▒▒▒▒░░░░░▒▒▒▒▒░░░░░\n");}
    if(type==2){printf("\t  ░░░░░▒▒▒▒▒░░░░░▒▒▒▒▒░░░░░▒▒▒▒▒░░░░░▒▒▒▒▒\n");}
}

void Print_Board(int u[8][8],int r){
    if(r==0){
        printf("\t   A    B    C    D    E    F    G    H \n");
        for(int i =0 ; i<8 ;i++){
            if(i%2==0){print_row(1);}
            else{print_row(2);}
            printf("\t%d ",i+1);
            for(int j = 0 ; j<8 ;j++){
                if((i+j)%2==1){
                    printf("░░");
                    if(u[i][j]==0){printf("░");}
                    if(u[i][j]==1){printf("\033[1;37m"); printf("█"); printf("\033[0m");}
                   if(u[i][j]==-1){printf("\033[1;30m"); printf("█"); printf("\033[0m");}
                    if(u[i][j]==2){printf("\033[1;37m"); printf("█"); printf("\033[0m");}
                   if(u[i][j]==-2){printf("\033[1;37m"); printf("█"); printf("\033[0m");}
                    printf("░░");
                }
                else{printf("▒▒▒▒▒");}
            }
            printf(" %d",i+1);
            printf("\n");
            if(i%2==0){print_row(1);}
            else{print_row(2);}
        }
        printf("\t   A    B    C    D    E    F    G    H \n");
    }
}


void Print_Num(int u[8][8]){
    printf("A  B  C  D  E  F  G  H\n");
    for(int i=0;i<8;i++){
        for(int j=0 ;j<8;j++){
            printf("%2d ",u[i][j]);
        }
        printf("\n");
    }
}

