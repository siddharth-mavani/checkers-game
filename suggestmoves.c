bool PrintPossibleMoves(char c,int x, int board[8][8],int player)
{
    bool flag=false;
    x--;
    int y=c- 'A';
    if( abs(board[x][y])==1)
    {
        if(CheckMove(board,x,y,x-player,y+1,0,player) && y+1<8 && 0<=x-player<8)
        {
            printf("%c%d\n",y+1+'A',x-player+1);
            flag=true;
        }
        if(CheckMove(board,x,y,x - player,y-1,0,player) && y-1>0 && 0<=x-player<8)
        {
            printf("%c%d\n",y-1+'A',x -player +1);
            flag=true;
        }
        if(CheckMove(board,x,y,x - (2*player),y+2,0,player) && y+2<8 && 0<=x - (2*player)<8)
        {
            printf("%c%d\n",y+2+'A',x+ (-2)*player +1);
            flag=true;
        }
        if(CheckMove(board,x,y,x+ (-2)*player,y-2,0,player) && y-2>=0 && 0<= x- (2*player)<8)
        {
            printf("%c%d\n",y-2+'A',x+ (-2)*player+1);
            flag=true;
        }
    }
    else if(abs(board[x][y])==2)
    {
        if(CheckMove(board,x,y,x-1,y-1,0,player) && 0<=y-1 && 0<=x-1)
        {
            printf("%c%d\n",y-1+'A',x);
            flag=true;
        }
        if(CheckMove(board,x,y,x-1,y+1,0,player) && y+1<8 && 0<=x-1)
        {
            printf("%c%d\n",y+1+'A',x);
            flag=true;
        }
        if(CheckMove(board,x,y,x+1,y-1,0,player) && 0<=y-1 && x+1<8)
        {
            printf("%c%d\n",y-1+'A',x+2);
            flag=true;
        }
        if(CheckMove(board,x,y,x+1,y+1,0,player) && y+1<8 && x+1<8)
        {
            printf("%c%d\n",y+1+'A',x+2);
            flag=true;
        }
        if(CheckMove(board,x,y,x-2,y-2,0,player) && 0<=y-2 && 0<=x-2)
        {
            printf("%c%d\n",y-2+'A',x-1);
            flag=true;
        }
        if(CheckMove(board,x,y,x-2,y+2,0,player) && y+2<8 && 0<=x-2)
        {
            printf("%c%d\n",y+2+'A',x-1);
            flag=true;
        }
        if(CheckMove(board,x,y,x+2,y-2,0,player) && 0<=y-2 && x+2<8)
        {
            printf("%c%d\n",y-2+'A',x+3);
            flag=true;
        }
        if(CheckMove(board,x,y,x+2,y+2,0,player) && y+2<8 && x+2<8)
        {
            printf("%c%d\n",y+2+'A',x+3);
            flag=true;
        }
    }
    return flag;
}