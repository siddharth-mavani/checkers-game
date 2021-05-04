#include "Checkers.h"
#include<string.h>



void instruction(int i,char** gogopowerranger){
    char  ins[24][100];
    strcpy(ins[0], " \t\tINSTRUCTION\n");
    strcpy(ins[1], " \t\tINSTRUCT 2\n");
    strcpy(ins[2], "\t\tINSTRUCT 1\n");
    strcpy(ins[3], "\t\tINSTRUCT 1\n");
    strcpy(ins[4], "\t\tINSTRUCT 1\n");
    strcpy(ins[5], "\t\tINSTRUCT 1\n");
    strcpy(ins[6], "\t\tINSTRUCT 1\n");
    strcpy(ins[7], "\t\tINSTRUCT 1\n");
    strcpy(ins[8], "\t\tINSTRUCT 1\n");
    strcpy(ins[9], "\t\tINSTRUCT 1\n");
    strcpy(ins[10], "\t\tINSTRUCT 1\n");
    strcpy(ins[11], "\t\tINSTRUCT 2\n");
    strcpy(ins[12], "\t\tINSTRUCT 1\n");
    strcpy(ins[13], "\t\tINSTRUCT 1\n");
    strcpy(ins[14], "\t\tINSTRUCT 1\n");
    strcpy(ins[15], "\t\tINSTRUCT 1\n");
    strcpy(ins[16], "\t\tINSTRUCT 1\n");
    strcpy(ins[17], "\t\tINSTRUCT 1\n");
    strcpy(ins[18], "\t\tINSTRUCT 1\n");
    strcpy(ins[19], "\t\tINSTRUCT 1\n");
    strcpy(ins[20], "\t\tINSTRUCT 1\n");
    strcpy(ins[21], "\t\tINSTRUCT 2AAAA\n");
    strcpy(ins[22], "\t\tINSTRUCT 1\n");
    strcpy(ins[23], "\t\tINSTRUCT 1\n");
    strcpy(*gogopowerranger,ins[i]);
}



void print_row(int type){
    if(type==1){printf("\t  ▒▒▒▒▒░░░░░▒▒▒▒▒░░░░░▒▒▒▒▒░░░░░▒▒▒▒▒░░░░░");}
    if(type==2){printf("\t  ░░░░░▒▒▒▒▒░░░░░▒▒▒▒▒░░░░░▒▒▒▒▒░░░░░▒▒▒▒▒");}
}

void Print_Board(int u[8][8],int r){
    char* gogopowerranger;
    gogopowerranger = (char*)malloc(sizeof(char)*100);
    if(r==-1){
        printf("\t    A    B    C    D    E    F    G    H \n");
        for(int i =0 ; i<8 ;i++){
            if(i%2==0){print_row(1);}
            else{print_row(2);}
            instruction(3*i,&gogopowerranger);
            printf("%s",gogopowerranger);
            printf("\t%d ",i+1);
            for(int j = 0 ; j<8 ;j++){
                if((i+j)%2==1){
                    printf("░░");
                    if(u[i][j]==0){printf("░░░");}
                    if(u[i][j]==1){printf("\033[1;37m"); printf("█"); printf("\033[0m");printf("░░");}
                   if(u[i][j]==-1){printf("\033[1;30m"); printf("█"); printf("\033[0m");printf("░░");}
                    if(u[i][j]==2){printf("\033[1;37m"); printf("\b█"); printf("\033[0m");printf("░");
                                   printf("\033[1;37m"); printf("█"); printf("\033[0m");printf("░");}
                   if(u[i][j]==-2){printf("\033[1;30m"); printf("\b█"); printf("\033[0m");printf("░");
                                   printf("\033[1;30m"); printf("█"); printf("\033[0m");printf("░");}
                    
                }
                else{printf("▒▒▒▒▒");}
            }
            instruction(3*i+1,&gogopowerranger);
            printf(" %d",i+1);
            printf("%s",gogopowerranger);
            if(i%2==0){print_row(1);}
            else{print_row(2);}
            instruction(3*i+2,&gogopowerranger);
            printf("%s",gogopowerranger);
        }
        printf("\t    A    B    C    D    E    F    G    H \n");
    }


    if(r==1){
        printf("\t    H    G    F    E    D    C    B    A \n");
        for(int i =7 ; i>=0 ;i--){
            if(i%2==1){print_row(1);}
            else{print_row(2);}
            instruction(3*(7-i),&gogopowerranger);
            printf("%s",gogopowerranger);
            printf("\t%d ",i+1);
            for(int j = 7 ; j>=0 ;j--){
                if((i+j)%2==1){
                    printf("░░");
                    if(u[i][j]==0){printf("░░░");}
                    if(u[i][j]==1){printf("\033[1;37m"); printf("█"); printf("\033[0m");printf("░░");}
                   if(u[i][j]==-1){printf("\033[1;30m"); printf("█"); printf("\033[0m");printf("░░");}
                    if(u[i][j]==2){printf("\033[1;37m"); printf("\b█"); printf("\033[0m");printf("░");
                                   printf("\033[1;37m"); printf("█"); printf("\033[0m");printf("░");}
                   if(u[i][j]==-2){printf("\033[1;30m"); printf("\b█"); printf("\033[0m");printf("░");
                                   printf("\033[1;30m"); printf("█"); printf("\033[0m");printf("░");}
                    
                }
                else{printf("▒▒▒▒▒");}
            }
            printf(" %d",i+1);
            instruction(3*(7-i)+1,&gogopowerranger);
            printf("%s",gogopowerranger);
            if(i%2==1){print_row(1);}
            else{print_row(2);}
            instruction(3*(7-i)+2,&gogopowerranger);
            printf("%s",gogopowerranger);
        }
        printf("\t    H    G    F    E    D    C    B    A \n");
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