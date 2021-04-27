int CheckMove(int u[8][8],int n1, int c1, int n2, int c2, int d, int player)// c1 is letter1,c2 is letter 2, n1,n2 are the first and the second numbers
{
    // for(int i=0;i<8;i++){
    //     for(int j=0 ;j<8;j++){
    //         printf("%2d %d %d     ",u[i][j],i,j);
    //     }
    //     printf("\n");
    // }
    printf("initial %d %d    final  %d %d    val_ini %d  val_fin %d\n\n",n1,c1,n2,c2,u[n1][c1],u[n2][c2]);
    if(c1<0||c1>7||n1<0||n1>7){return 0;}
    if(c2<0||c2>7||n2<0||n2>7){return 0;}
    if((u[n1][c1]*player)<=0){return 0;}
    int diff_row = n1 - n2 ;
    int diff_coln = (c1 - c2);
    if(diff_coln<0){diff_coln=-diff_coln;}

    if (d == 2 && diff_coln != 2)                       // when the player is doing second turn he has to compulsary capture
        return 0 ;

    if (abs (diff_row) != diff_coln)
        return 0 ;                                      // 0 is returned if the move made is wrong

    if (abs(diff_row) > 2 || abs (diff_row) < 1 || diff_coln > 2 || diff_coln < 1)
        return 0 ;

    if (u[n1][c1] == 0 || u [n2][c2] != 0)
        return 0 ;

    if (u[n1][c1] == 1 || u[n1][c1] == -1)
    {
        if (u[n1][c1] * diff_row > 0)
        {
            if (diff_coln == 1)
                return 1 ;
            else                                        // checking if the middle piece is of opponent
            {
                if (u[n1][c1] * u[(n1 + n2)/2][(c1+c2)/2] < 0)
                    return 2 ;                          // if the player has to play another move
                else 
                    return 0 ;
            }
        }
    }
}
