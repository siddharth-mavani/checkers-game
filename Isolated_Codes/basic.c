#include<stdio.h>
#include<string.h>

#define empty 0
#define white 1
#define black -1
#define white_king  2
#define black_king -2


struct change{
    char initial_char ;
    char final_char;
    int initial_int ;
    int final_int;
};


void init(int u[8][8]){
    for(int i=0;i<8;i++){
        for(int j=0 ;j<8;j++){
            u[i][j]=0;
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<8;j++){
            if((i+j)%2==1){u[i][j]=-1;
            u[7-i][7-j]=1;}
        }
    }
    
}



void print_num(int u[8][8]){
    for(int i=0;i<8;i++){
        for(int j=0 ;j<8;j++){
            printf("%2d ",u[i][j]);
        }
        printf("\n");
    }
}

void swap(int * a , int * b){
    int temp=*a;
    *a=*b;
    *b=temp;
}


void move(int u[8][8],int player){
    int flag=0;
    char c1;
    int d1;
    int cl1;
    do{
        if(flag){printf("WRONG INPUT\n");}    
        flag=1;
        scanf(" %c%d",&c1,&d1);
        if(c1<'A'||c1>'H'||d1<1||d1>8){continue;}
        cl1=c1-'A';
    d1--;}while((u[d1][cl1]*player)<=0);
    char s[9];
    scanf("%s",s);
    flag=0;
    char c2;
    int d2;
    int cl2;
    do{
        if(flag){printf("INVALID MOVE\n");}    
        flag=1;
        scanf(" %c%d",&c2,&d2);
        if(c2<'A'||c2>'H'||d2<1||d2>8){continue;}
        cl2=c2-'A';
        d2--;}while(u[d2][cl2]!=0);

    swap(&u[d1][cl1],&u[d2][cl2]);

}



int main(){
    int u[8][8];
    init(u);
    print_num(u);
    char s[100];
    int player=-1;
    while(1){
        scanf("%s",s);
        if(strcmp(s,"MOVE")==0){move(u,player);}
        print_num(u);
        player=-player;
        getchar();
    }
}
