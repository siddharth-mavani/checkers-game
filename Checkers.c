#include "Checkers.h"

void swap(int *a, int *b){

    int temp = *a;
    *a = *b;
    *b = temp;

    return ;
}

Move_Node *Makenode(void){

    Move_Node *Temp = (Move_Node *)malloc(sizeof(Move_Node));
    assert(Temp != NULL);

    Temp -> Next = NULL;

    return Temp;
}

Game_Spec *Init_Game(int Auto_Rotate, int Compulsory_Capture, int Num_Moves, int Num_Black, int Num_White, int Num_Black_King, int Num_White_King, int Board_Orientation, char Name_Of_Player1[100], char Name_Of_Player2[100]){
    
    Game_Spec *Game = (Game_Spec *)malloc(sizeof(Game_Spec));
    assert(Game != NULL);

    Game -> Auto_Rotate = Auto_Rotate;
    Game -> Compulsory_Capture = Compulsory_Capture;
    Game -> Num_Moves = Num_Moves;
    Game -> Num_Black = Num_Black;
    Game -> Num_White = Num_White;
    Game -> Num_Black_King = Num_Black_King;
    Game -> Num_White_King = Num_White_King;
    Game -> Board_Orientation = Board_Orientation;
    strcpy(Game -> Name_Of_Player1, Name_Of_Player1);
    strcpy(Game -> Name_Of_Player2, Name_Of_Player2);

    Game -> Moves = Makenode();
    Game -> Moves->Next = NULL;
    Game -> Last_Move = Game->Moves;

    return Game;
}

void Insert_move(Game_Spec *Game, char Initial_Char, char Final_Char, int Initial_Int, int Final_Int, int Type, int Kill, int Kill_Type, int Change_To_King){
    
    Move_Node *Curr_Move = Makenode();
    Curr_Move -> Initial_Char = Initial_Char;
    Curr_Move -> Final_Char = Final_Char;
    Curr_Move -> Initial_Int = Initial_Int;
    Curr_Move -> Final_Int = Final_Int;
    Curr_Move -> Type = Type;
    Curr_Move -> Kill = Kill;
    Curr_Move -> Kill_Type = Kill_Type;
    Curr_Move -> Change_To_King = Change_To_King;

    Curr_Move -> Next = NULL;
    Curr_Move -> Prev = Game->Last_Move;
    Game -> Last_Move->Next = Curr_Move;
    Game -> Last_Move = Curr_Move;

    Game->Num_Moves++;

    return ;
}

int Undo(int u[8][8], struct Game_Spec *G){

    if (G->Num_Moves == 0){
        printf("NO MOVES LEFT TO UNDO\n");
        return 0;
    }

    int InitialInt = G->Last_Move->Initial_Int;
    int FinalInt = G->Last_Move->Final_Int;
    char InitialChar = G->Last_Move->Initial_Char;
    char FinalChar = G->Last_Move->Final_Char;
    int InitialCharToInt = InitialChar - 'A';
    int FinalCharToInt = FinalChar - 'A';

    swap(&u[InitialInt][InitialCharToInt], &u[FinalInt][FinalCharToInt]);

    if (G->Last_Move->Kill == 1){
        u[(InitialInt + FinalInt) / 2][(InitialCharToInt + FinalCharToInt) / 2] = G->Last_Move->Kill_Type;
    }

    if (G->Last_Move->Change_To_King == 1 && u[InitialInt][InitialCharToInt] == WHITE_KING){
        u[InitialInt][InitialCharToInt] = WHITE;
    }

    if (G->Last_Move->Change_To_King == 1 && u[InitialInt][InitialCharToInt] == BLACK_KING){
        u[InitialInt][InitialCharToInt] = BLACK;
    }

    struct Change *Temp = G->Last_Move;

    G->Last_Move = Temp->Prev;
    G->Last_Move->Next = NULL;
    free(Temp);
    G->Num_Moves--;

    return 1;
}

int CheckMove(int u[8][8], int N1, int C1, int N2, int C2, int D, int Player){ 
    
    // C1 is letter1,C2 is letter 2, N1,N2 are the first and the second numbers
    //printf("initial %d %d    final  %d %d    val_ini %d  val_fin %d\n\n", N1, C1, N2, C2, u[N1][C1], u[N2][C2]);

    if (C1 < 0 || C1 > 7 || N1 < 0 || N1 > 7){
        return 0;
    }
    if (C2 < 0 || C2 > 7 || N2 < 0 || N2 > 7){
        return 0;
    }
    if ((u[N1][C1] * Player) <= 0){
        return 0;
    }

    int Diff_Row = N1 - N2;
    int Diff_Coln = (C1 - C2);

    if (Diff_Coln < 0){
        Diff_Coln = -Diff_Coln;
    }

    if (D == 2 && Diff_Coln != 2) // when the Player is doing second turn he has to compulsary capture
        return 0;

    if (abs(Diff_Row) != Diff_Coln)
        return 0; // 0 is returned if the move made is wrong

    if (abs(Diff_Row) > 2 || abs(Diff_Row) < 1 || Diff_Coln > 2 || Diff_Coln < 1)
        return 0;

    if (u[N1][C1] == EMPTY || u[N2][C2] != EMPTY)
        return 0;

    if (u[N1][C1] == WHITE || u[N1][C1] == BLACK){
        if (u[N1][C1] * Diff_Row > 0){
            if (Diff_Coln == 1)
                return 1;
            else{ // checking if the middle piece is of opponent
                if (u[N1][C1] * u[(N1 + N2) / 2][(C1 + C2) / 2] < 0)
                    return 2; // if the Player has to play another move
                else
                    return 0;
            }
        }
    }

    if (u[N1][C1] == WHITE_KING || u[N1][C1] == BLACK_KING){
        if (Diff_Coln == 1)
            return 1;
        else{ // checking if the middle piece is of opponent
            if (u[N1][C1] * u[(N1 + N2) / 2][(C1 + C2) / 2] < 0)
                return 2; // if the Player has to play another move
            else
                return 0;
        }
    }

    return 0;
}

void Init(int u[8][8]){

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            u[i][j] = EMPTY;
        }
    }

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 8; j++){
            if ((i + j) % 2 == 1){
                u[i][j] = BLACK;
                u[7 - i][7 - j] = WHITE;
            }
        }
    }

    return ;
}
void print_ll(Game_Spec *g)
{
    Move_Node *curr = g->Moves;
    int i = 0;
    while (curr != NULL)
    {
        printf("%c%d   %c%d  %d\n\n", curr->Initial_Char, curr->Initial_Int, curr->Final_Char, curr->Final_Int, i);
        i++;
        curr = curr->Next;
    }
}

int Move(int u[8][8], int *Player, Game_Spec *G){
    int FLAG = 0;
    char InitialChar;
    int InitialInt;
    int InitialCharToInt;
    char FinalChar;
    int FinalInt;
    int FinalCharToInt;
    int Kill = 0;
    int Kill_Type = 0;
    int Change_To_King = 0;
    int Done = 0;
    char c;
    do{
        //FLAG=2 means a capture has been made in last turn so here we are asking the user for successive capture
        if (FLAG == 2 && G->Compulsory_Capture == 0){
            Print_Num(u);
            printf("DO YOU WANT TO MAKE A SUCCESSIVE CAPTURE(ENTER Y OR N):  ");
            scanf("\n%c", &c);
            if (c == 'N'){
                return 1;
            }
            if (c == 'Y'){
                printf("ENTER CORDINATES OF THE FINAL SQUARE: ");
            }
        }

        // If FLAG!=2 we need to input the coordinates for the initial square , if FLAG=2 we can just use final cord. of last
        // turn as initial coordinates for current turn
        if (FLAG != 2){
            scanf(" %c%d", &InitialChar, &InitialInt);
            InitialCharToInt = InitialChar - 'A';
            InitialInt--;
            char s[9];
            scanf("%s", s);
        }

        // Asking for final coordinates
        scanf(" %c%d", &FinalChar, &FinalInt);
        FinalCharToInt = FinalChar - 'A';
        FinalInt--;

        // Checking whether move is correct or not and returning 0 is move is incorrect , we must not return if we are making 
        // successive capture
        int val = CheckMove(u, InitialInt, InitialCharToInt, FinalInt, FinalCharToInt, FLAG, *Player);
        printf("%d is value returned by CheckMove function \n\n", val);
        if (val == 0 && FLAG != 2){
            printf("WRONG INPUT\n");
            return 0;
        }
        if (val == 0 && FLAG == 2){
            printf("WRONG INPUT\n");
            continue;
        }

        //here we are checking if the moved coin transformed to king or not
        if (FinalInt == 0 && u[InitialInt][InitialCharToInt] == WHITE){
            u[InitialInt][InitialCharToInt] = WHITE_KING;
            Change_To_King = 1;
            G->Num_White_King++;
        }
        if (FinalInt == 7 && u[InitialInt][InitialCharToInt] == BLACK){
            u[InitialInt][InitialCharToInt] = BLACK_KING;
            Change_To_King = 1;
            G->Num_Black_King++;
        }

        if (val == 2){
            Kill_Type = u[(InitialInt + FinalInt) / 2][(InitialCharToInt + FinalCharToInt) / 2];
            Kill = 1;
        }

        Insert_move(G, InitialChar, FinalChar, InitialInt, FinalInt, u[InitialInt][InitialCharToInt], Kill, Kill_Type, Change_To_King);

        //here we are swapping the final and initial squares
        swap(&u[InitialInt][InitialCharToInt], &u[FinalInt][FinalCharToInt]);

        if (val == 2){
            u[(InitialInt + FinalInt) / 2][(InitialCharToInt + FinalCharToInt) / 2] = EMPTY;
            FLAG = 2;
            InitialChar = FinalChar;
            InitialCharToInt = FinalCharToInt;
            InitialInt = FinalInt;
            continue;
        }

        Done = 1;
    } while (Done == 0);

    return 1;
}

// This function returns 1 if Game is availabe, 0 otherwise
int Name_Is_Available(char Name_Of_Game[105]){

    FILE* fp;                                                           

    fp = fopen(Name_Of_Game, "r");                                      
    if(fp == NULL)      return 0;                                       // fp is NULL if <Name_Of_Game> is not available
    else                return 1;

    fclose(fp);                                                         
}

// This Functions allows the user to Save the Current Game 
void Save(int u[8][8], int Player, Game_Spec* G){

    char Name_Of_Game[106];                             

    printf("Enter Name of the Game: ");                 
    scanf(" %s", Name_Of_Game);                         

    strcat(Name_Of_Game, ".txt");                           // Game will be stored as <Name_Of_Game>.txt 

    // Checking if the Game exists    
    while(Name_Is_Available(Name_Of_Game)){

        printf("\t The Game does already exists, please enter another name: ");
        scanf(" %s", Name_Of_Game);                         

        strcat(Name_Of_Game, ".txt");                       
                
    }

    FILE *fp;                                           
    fp = fopen(Name_Of_Game, "w");                      

    // Storing the location of each token by writing the mtrix into file
    for (int i = 0; i < 8; i++){                        
        for (int j = 0; j < 8; j++){                    
            fprintf(fp, "%d ", u[i][j]);                
        }
    }

    fprintf(fp, "%d ", Player);                        // Storing Players turn

    // Storing the Game-Specs
    fprintf(fp, "%d ", G -> Auto_Rotate);               
    fprintf(fp, "%d ", G -> Compulsory_Capture);        
    fprintf(fp, "%d ", G -> Num_Moves);                 
    fprintf(fp, "%d ", G -> Num_Black);                 
    fprintf(fp, "%d ", G -> Num_White);                 
    fprintf(fp, "%d ", G -> Num_Black_King);            
    fprintf(fp, "%d ", G -> Num_White_King);
    fprintf(fp, "%d ", G -> Board_Orientation);
    fprintf(fp, "%s ", G -> Name_Of_Player1);
    fprintf(fp, "%s ", G -> Name_Of_Player2);            

    struct Change* Temp  = G -> Last_Move;              // Pointer to Doubly Linked List that stores Move History

    while(Temp -> Prev != NULL){                        // Going to end of Linked List before stoing 
        Temp = Temp -> Prev;                            // because initally temp points to Latest move
    }                                                   // but we want to store the first move first

    Temp = Temp -> Next;                                

    // Storing the Move History to allow UNDO Options in Saved Games
    while(Temp != NULL){                                
         
        fprintf(fp, "%c ", Temp -> Initial_Char);       
        fprintf(fp, "%c ", Temp -> Final_Char);         
        fprintf(fp, "%d ", Temp -> Initial_Int);        
        fprintf(fp, "%d ", Temp -> Final_Int);          
        fprintf(fp, "%d ", Temp -> Type);               
        fprintf(fp, "%d ", Temp -> Kill);               
        fprintf(fp, "%d ", Temp -> Kill_Type);          
        fprintf(fp, "%d ", Temp -> Change_To_King);     

        Temp = Temp -> Next;                            
    }  

    fclose(fp);                                        
    return ;
}



// Allows user to Reload a Saved Game
Game_Spec* Load_Saved_Game(char Name_Of_Game[105], int u[8][8], int *Player){

    FILE* fp;                                           
    fp = fopen(Name_Of_Game, "r");                      


    // Reading the location of each token
    for (int i = 0; i < 8; i++){                        
        for (int j = 0; j < 8; j++){                    
            fscanf(fp, "%d ", &u[i][j]);                
        }
    }

    fscanf(fp, "%d", Player);                           // Reads Player turn

    // Initialising Variables for Different Variations of the Game
    int Auto_Rotate, Compulsory_Capture, Board_Orientation;                                           
    int Num_Black , Num_White , Num_White_Kings, Num_Black_Kings, Num_Moves;
    char Name_Of_Player1[100], Name_Of_Player2[100];                                    

    // Reading Game-Specs;
    fscanf(fp, "%d ", &Auto_Rotate);               
    fscanf(fp, "%d ", &Compulsory_Capture);        
    fscanf(fp, "%d ", &Num_Moves);                      
    fscanf(fp, "%d ", &Num_Black);                 
    fscanf(fp, "%d ", &Num_White);                 
    fscanf(fp, "%d ", &Num_Black_Kings);            
    fscanf(fp, "%d ", &Num_White_Kings);
    fscanf(fp, "%d ", &Board_Orientation);
    fscanf(fp, "%s ", Name_Of_Player1);
    fscanf(fp, "%s ", Name_Of_Player2); 

    // Initialising Game Board
    Game_Spec* G;                                       
    G = Init_Game(Auto_Rotate, Compulsory_Capture, 0, Num_Black, Num_White, Num_Black_Kings, Num_White_Kings, Board_Orientation, Name_Of_Player1, Name_Of_Player2);

    printf("Num_Moves: %d\n", G -> Num_Moves);


    //Initialising Variables of Linked List
    char Initial_Char, Final_Char;
    int Initial_Int, Final_Int, Type, Kill, Kill_Type, Change_To_King ;

    // Reading the Move History
    for(int i = 0; i < Num_Moves; i++){

        fscanf(fp, "%c ", &Initial_Char);               
        fscanf(fp, "%c ", &Final_Char);                 
        fscanf(fp, "%d ", &Initial_Int);                
        fscanf(fp, "%d ", &Final_Int);                  
        fscanf(fp, "%d ", &Type);                       
        fscanf(fp, "%d ", &Kill);                       
        fscanf(fp, "%d ", &Kill_Type);                  
        fscanf(fp, "%d ", &Change_To_King);             

        // Inserting Moves into the Linked List
        Insert_move(G, Initial_Char, Final_Char, Initial_Int, Final_Int, Type, Kill, Kill_Type, Change_To_King);
    }

    printf("Num_Moves: %d\n", G -> Num_Moves);

    return G;
}                 

void game_review(struct Game_Spec *g, int* Player)
{
    if (g->Num_Moves == 0)
    {
        printf("NO MOVES TILL THIS POINT\n");
        return;
    }
    int temp[8][8];
    Init(temp);
    char c;
    struct Change *curr = g->Moves->Next;
    int orientation = g->Board_Orientation;

    Print_Board(temp, g, *Player);
    printf("COMMANDS:\n          ENTER N FOR NEXT STEP \n          ENTER P FOR PREVIOUS STEP\n          ENTER Q TO STOP REVIEWING\n\n");
    printf("YOUR CHOICE: ");
    scanf(" %c", &c);

    if (c == 'P')
    {
        while (1)
        {
            printf("\nNO MORE PREVIOUS STEPS ARE LEFT\n\n");
            printf("COMMANDS:\n          ENTER N FOR NEXT STEP \n          ENTER P FOR PREVIOUS STEP\n          ENTER Q TO STOP REVIEWING\n\n");
            printf("YOUR CHOICE: ");
            scanf(" %c", &c);
            if(c != 'P')
                break;
        }
    }
    if (c == 'Q')
    {
        return;
    }
    //orientation *= -1;
    while (curr != NULL)
    {
        int a1 = curr->Initial_Int;
        int b1 = curr->Final_Int;
        char a2 = curr->Initial_Char;
        char b2 = curr->Final_Char;
        int a3 = a2 - 'A';
        int b3 = b2 - 'A';
        if (curr->Change_To_King && c == 'N')
        {
            temp[a1][a3] = 2 * temp[a1][a3];
        }
        if (curr->Change_To_King && c == 'P')
        {
            temp[b1][b3] = temp[b1][b3] / 2;
        }
        if (curr->Kill && c == 'N')
        {
            temp[(a1 + b1) / 2][(a3 + b3) / 2] = 0;
        }
        if (curr->Kill && c == 'P')
        {
            temp[(a1 + b1) / 2][(a3 + b3) / 2] = curr->Kill_Type;
        }
        swap(&temp[a1][a3], &temp[b1][b3]);
        Print_Board(temp, g, *Player);
        //orientation *= -1;

    H1:
        printf("COMMANDS:\n          ENTER N FOR NEXT STEP \n          ENTER P FOR PREVIOUS STEP\n          ENTER Q TO STOP REVIEWING\n\n");
        int flag = 0;
        if (c == 'N')
        {
            flag = 1;
        }
        printf("YOUR CHOICE: ");
        scanf(" %c", &c);
        if (c == 'P' && curr == g->Moves->Next && !flag)
        {
            printf("NO MORE PREVIOUS STEPS ARE LEFT\n");
            goto H1;
        }

        if (c == 'N' && flag)
        {
            if (curr->Next == NULL)
            {
                char response;
                printf("THE BOARD IS AT THE CURRENT MOVE/SITUATION. \nWOULD YOU LIKE THE REVIEW TO END OR YOU WISH TO GO TO THE PREVIOUS MOVE?\n");
                printf("ENTER YOUR CHOICE(Y TO EXIT, and P TO GO TO THE PREVIOUS MOVE: ");
                scanf(" %c", &response);
                if (response == 'Y')
                {
                    return;
                }
                if (response == 'P')
                {
                    curr = curr;
                    c = 'P';
                }
            }
            else
                curr = curr->Next;
        }
        else if (c == 'N' && !flag)
        {
            curr;
        }
        else if (c == 'P' && flag)
        {
            curr = curr;
        }
        else if (c == 'P' && !flag)
        {

            curr = curr->Prev;
        }
        if (c == 'Q')
        {
            return;
        }

        // swap(&temp[a1][a3], &temp[b1][b3]);
        // Print_Board(temp, orientation);
        //printf("RR  %c\n", c);
    }

    return;
}



// This Function simulates the Game
void Play_Game(int u[8][8], int *Player, Game_Spec *G){

    char Command[100];                                              

    printf("\n\n");                         
    Print_Board(u, G, *Player);                                              

    while (1){

        scanf("%s", Command);                                      

        if (strcmp(Command, "MOVE") == 0){  
            if(Move(u, Player, G)){
                if(endgame(G,u,-(*Player)))
                {
                    Print_Board(u,G,*Player);
                    if ( *Player<0) //black has won
                    { 
                    	printf("%s HAS WON THE GAME!!!!!\nCONGRATULATIONS\n",G->Name_Of_Player1);
                    	printf("BETTER LUCK NEXT TIME %s\n",G->Name_Of_Player2);
                    }
                    else 
                    {
                        printf("%s HAS WON THE GAME!!!!!\nCONGRATULATIONS\n",G->Name_Of_Player2);
                    	printf("BETTER LUCK NEXT TIME %s\n",G->Name_Of_Player1);
                    }
                    return;
                }
                else
                {
                    // Switches Player and Board-Orientation
                    *Player = -*Player;                                         
                    if(G->Auto_Rotate){                                         
                        G -> Board_Orientation = -G -> Board_Orientation;                                                 
		            }
		            Print_Board(u, G, *Player);
                } 
            }   
        }
        else if (strcmp(Command, "UNDO") == 0){   
            if(Undo(u, G)){

                // Switches Player and Board-Orientation
                *Player = -*Player;                                         
                if(G->Auto_Rotate){
                    G -> Board_Orientation = -G -> Board_Orientation;
                }
                Print_Board(u, G, *Player); 
            }   
        }
        else if (strcmp(Command, "SAVE") == 0){                     
            Save(u, *Player, G);                                     
        }
        else if(strcmp(Command, "REVIEW") == 0)
        {
            game_review(G, Player);
            printf("\nTHE REVIEW HAS BEEN COMPLETED AND THE CURRENT SITUATION OF THE BOARD IS:\n\n");
            Print_Board(u, G, *Player);
        }
        else if (strcmp(Command, "QUIT") == 0){                     

            char s[5];                                              
            printf("Do you want to Save the Game ? ");              
            scanf(" %s", s);                                        

            if(strcmp(s, "YES") == 0 || strcmp(s, "Y") == 0 || strcmp(s, "yes") == 0 || strcmp(s, "y") == 0){
                Save(u, *Player, G);                                 
                return ;                                            
            }

            return ;                                                
        }
        else if(strcmp(Command,"SUGGEST")==0)
        {
            char c;
            int x;
            //scanf(" %c%d",&c,&x);
            // if(!PossibleMoves(c,x,u,*Player,true))
            //     printf("No Moves Possible!!\n");
            suggest(u, *Player);
        }

        //print_ll(G);                                                

                                            
        getchar();                                                  
    }

    return ;
}

void suggest(int u[8][8],int player)
{
    bool flag;
    for(int i=0;i<8;i++)
    {
        for(int j=1;j<=8;j++)
        {
            flag=PossibleMoves(i+'A',j,u,player,true);
        }

    }
}

bool PossibleMoves(char c,int x, int board[8][8],int player,bool print)
{
    // will print the possible positions for a piece if the print variable is true
    bool flag=false;
    x--;
    int y=c- 'A';
    if( abs(board[x][y])==1)
    {
        if(CheckMove(board,x,y,x-player,y+1,0,player) && y+1<8 && 0<=x-player<8)
        {
            if(print)printf("%c%d->%c%d\n",c,x+1,y+1+'A',x-player+1);
            flag=true;
        }
        if(CheckMove(board,x,y,x - player,y-1,0,player) && y-1>=0 && 0<=x-player<8)
        {
            if(print)printf("%c%d->%c%d\n",c,x+1,y-1+'A',x -player +1);
            flag=true;
        }
        if(CheckMove(board,x,y,x - (2*player),y+2,0,player) && y+2<8 && 0<=x - (2*player)<8)
        {
            if(print)printf("%c%d->%c%d\n",c,x+1,y+2+'A',x+ (-2)*player +1);
            flag=true;
        }
        if(CheckMove(board,x,y,x+ (-2)*player,y-2,0,player) && y-2>=0 && 0<= x- (2*player)<8)
        {
            if(print)printf("%c%d->%c%d\n",c,x+1,y-2+'A',x+ (-2)*player+1);
            flag=true;
        }
    }
    else if(abs(board[x][y])==2)
    {
        if(CheckMove(board,x,y,x-1,y-1,0,player) && 0<=y-1 && 0<=x-1)
        {
            if(print)printf("%c%d->%c%d\n",c,x+1,y-1+'A',x);
            flag=true;
        }
        if(CheckMove(board,x,y,x-1,y+1,0,player) && y+1<8 && 0<=x-1)
        {
            if(print)printf("%c%d->%c%d\n",c,x+1,y+1+'A',x);
            flag=true;
        }
        if(CheckMove(board,x,y,x+1,y-1,0,player) && 0<=y-1 && x+1<8)
        {
            if(print)printf("%c%d->%c%d\n",c,x+1,y-1+'A',x+2);
            flag=true;
        }
        if(CheckMove(board,x,y,x+1,y+1,0,player) && y+1<8 && x+1<8)
        {
            if(print)printf("%c%d->%c%d\n",c,x+1,y+1+'A',x+2);
            flag=true;
        }
        if(CheckMove(board,x,y,x-2,y-2,0,player) && 0<=y-2 && 0<=x-2)
        {
            if(print)printf("%c%d->%c%d\n",c,x+1,y-2+'A',x-1);
            flag=true;
        }
        if(CheckMove(board,x,y,x-2,y+2,0,player) && y+2<8 && 0<=x-2)
        {
            if(print)printf("%c%d->%c%d\n",c,x+1,y+2+'A',x-1);
            flag=true;
        }
        if(CheckMove(board,x,y,x+2,y-2,0,player) && 0<=y-2 && x+2<8)
        {
            if(print)printf("%c%d->%c%d\n",c,x+1,y-2+'A',x+3);
            flag=true;
        }
        if(CheckMove(board,x,y,x+2,y+2,0,player) && y+2<8 && x+2<8)
        {
            if(print)printf("%c%d->%c%d\n",c,x+1,y+2+'A',x+3);
            flag=true;
        }
    }
    return flag;
}

bool endgame(Game_Spec* G,int u[8][8], int Player)
{
    if (Player < 0 && (G->Num_Black+G->Num_Black_King)==0)
        return true;
    else if(Player > 0 && (G->Num_White+G->Num_White_King)==0)
        return true;
    
    //bool flag=false;
    int val=Player;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
            if(u[i][j]==val && PossibleMoves(j+'A',i+1,u,val,false))
                return false;
                //flag=true;
    }
    return true;
    

}
