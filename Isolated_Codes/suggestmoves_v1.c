#include <math.h>
#include <stdio.h>
#include <stdbool.h>


//takes the position character c and number x and the board as input and prints out the possible moves
//if there is no move the funtion returns false
bool PrintPossibleMoves(char c,int x, int board[8][8])
{
    bool flag=false; //to check if there are any moves possible
    bool capture=false; // to check the occurance of a capture
    x--;
    int y=c- 'A';
    if( abs(board[x][y])==1) // the input piece is not a king piece
    {
        int diag[4]; // to store the values of the 2 daigonals and the capturable squares
        diag[0]=board[x+ (-1)*board[x][y]][y+1]; //down/up right
        diag[1]=board[x + (-1)*board[x][y]][y-1]; //down/up left
        diag[2]=board[x+ (-2)*board[x][y]][y+2]; // down/up right capture
        diag[3]=board[x + (-2)*board[x][y]][y-2]; //down/up left capture


        if((diag[0]!=0 && diag[2]==0) || (diag[1]!=0 && diag[3]==0)) //to check if capture is taking place
        {
            capture=true;
        }


        if(diag[0]==0 && 0<=x+ (-1)*board[x][y]<8 && y<6)
        {
            if(!capture ){printf("%c%d\n",y+1+'A',x+ (-1)*board[x][y]+1);}
            flag=true;
        }
        else if(diag[2]==0 && (board[x][y]*diag[0])<0 && 0<=x+ (-2)*board[x][y]<8 && y<5)
        {
            printf("%c%d\n",y+2+'A',x+ (-2)*board[x][y]+1);
            flag=true;
        }



        if(diag[1]==0 && 0<=x+ (-1)*board[x][y]<8 && 0<y)
        {
            if(!capture) {printf("%c%d\n",y-1+'A',x+ (-1)*board[x][y]+1);}
            flag=true;
        }
        else if(diag[3]==0 && (board[x][y]*diag[1])<0 && 0<=x+ (-2)*board[x][y]<8 && y-1>0)
        { 
            printf("%c%d\n",y-2+'A',x+ (-2)*board[x][y]+1);
            flag=true;
            

        }


        
    }
    else if(abs(board[x][y])==2) // the input piece is a king piece
    {
        //printf("KINGGG");
        int diag[8]; // to store the 4 adjacent movable squares and the 4 capturable squares
        diag[0]=board[x-1][y-1]; //top left
        diag[1]=board[x-1][y+1]; //top right
        diag[2]=board[x+1][y-1]; //down left
        diag[3]=board[x+1][y+1]; //down right
        diag[4]=board[x-2][y-2]; //top left capture posn
        diag[5]=board[x-2][y+2]; //top right capture posn
        diag[6]=board[x+2][y-2]; //down left capture posn
        diag[7]=board[x+2][y+2]; //down right capture posn

        for(int i=0;i<4;i++)
        {
            if(diag[i]!=0 && diag[i+4]==0 )
            {
                capture=true;
                break;
            }
        }


        if(diag[0]==0 && x-1>=0 && y-1>=0)
        {
            if(!capture){printf("%c%d\n",y-1+'A',x);}
            flag=true;
        }
        else if(diag[4]==0 && x-2>=0 && y-2>=0 && (board[x][y]*diag[0])<0)
        {
            printf("%c%d\n",y-2+'A',x-1);
            flag=true;
        }

        if(diag[1]==0 && x-1>=0 && y+1<8)
        {
            if(!capture){printf("%c%d\n",y+1+'A',x);}
            flag=true;
        }
        else if(diag[5]==0 && x-2>=0 && y+2<8 && (board[x][y]*diag[1])<0)
        {
            printf("%c%d\n",y+2+'A',x-1);
            flag=true;
        }

        if(diag[2]==0 && x+1<8 && y-1>=0)
        {
            if(!capture){printf("%c%d\n",y-1+'A',x+2);}
            flag=true;
        }
        else if(diag[6]==0 && x+2<8 && y-2>=0 && (board[x][y]*diag[2])<0)
        {
            printf("%c%d\n",y-2+'A',x+3);
            flag=true;
        }

        if(diag[3]==0 && x+1<8 && y+1<8)
        {
            if(!capture){printf("%c%d\n",y+1+'A',x+2);}
            flag=true;
        }
        else if(diag[7]==0 && x+2<8 && y+2<8 && (board[x][y]*diag[3])<0)
        {
            printf("%c%d\n",y+2+'A',x+3);
            flag=true;
        }
    }
    return flag;
}

