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

    Temp->Next = NULL;

    return Temp;
}

Game_Spec *Init_Game(int Auto_Rotate, int Compulsory_Capture, int Num_Moves, int Num_Black, int Num_White, int Num_Black_King, int Num_White_King){
    
    Game_Spec *Game = (Game_Spec *)malloc(sizeof(Game_Spec));
    assert(Game != NULL);

    Game->Auto_Rotate = Auto_Rotate;
    Game->Compulsory_Capture = Compulsory_Capture;
    Game->Num_Moves = Num_Moves;
    Game->Num_Black = Num_Black;
    Game->Num_White = Num_White;
    Game->Num_Black_King = Num_Black_King;
    Game->Num_White_King = Num_White_King;
    Game->Moves = Makenode();
    Game->Moves->Next = NULL;
    Game->Last_Move = Game->Moves;

    return Game;
}

void Insert_move(Game_Spec *Game, char Initial_Char, char Final_Char, int Initial_Int, int Final_Int, int Type, int Kill, int Kill_Type, int Change_To_King){
    

    printf("CHECK 1\n");

    Move_Node *Curr_Move = Makenode();

    Curr_Move->Initial_Char = Initial_Char;
    Curr_Move->Final_Char = Final_Char;
    Curr_Move->Initial_Int = Initial_Int;
    Curr_Move->Final_Int = Final_Int;
    Curr_Move->Type = Type;
    Curr_Move->Kill = Kill;
    Curr_Move->Kill_Type = Kill_Type;
    Curr_Move->Change_To_King = Change_To_King;

    Curr_Move->Next = NULL;
    Curr_Move->Prev = Game->Last_Move;
    Game->Last_Move->Next = Curr_Move;
    Game->Last_Move = Curr_Move;

    // if(Game->Last_Move == NULL)
    // {
    //     Game->Moves->Next = Curr_Move;
    //     Curr_Move->Prev = Game->Moves;
    //     Game->Last_Move = Curr_Move;
    // }
    // else{
    //     Game->Last_Move->Next = Curr_Move;
    //     Curr_Move->Prev = Game->Last_Move;
    // }

    Game->Num_Moves++;

    // needs attention here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // Game->num_black;
    // Game->num_black_king;
    // Game->num_white;
    // Game->Num_White_King;

    return ;
}

void Undo(int u[8][8], struct Game_Spec *G){

    if (G->Num_Moves == 0){
        printf("NO MOVES LEFT TO UNDO\n");
        return;
    }

    int A1 = G->Last_Move->Initial_Int;
    int B1 = G->Last_Move->Final_Int;
    char A2 = G->Last_Move->Initial_Char;
    char B2 = G->Last_Move->Final_Char;
    int A3 = A2 - 'A';
    int B3 = B2 - 'A';

    swap(&u[A1][A3], &u[B1][B3]);

    if (G->Last_Move->Kill == 1){
        u[(A1 + B1) / 2][(A3 + B3) / 2] = G->Last_Move->Kill_Type;
    }

    if (G->Last_Move->Change_To_King == 1 && u[A1][A3] == WHITE_KING){
        u[A1][A3] = WHITE;
    }

    if (G->Last_Move->Change_To_King == 1 && u[A1][A3] == BLACK_KING){
        u[A1][A3] = BLACK;
    }

    struct Change *Temp = G->Last_Move;

    G->Last_Move = Temp->Prev;
    G->Last_Move->Next = NULL;
    printf("CHECK\n");
    free(Temp);
    G->Num_Moves--;

    return ;
}

int CheckMove(int u[8][8], int N1, int C1, int N2, int C2, int D, int Player){ 
    
    // C1 is letter1,C2 is letter 2, N1,N2 are the first and the second numbers
    printf("initial %d %d    final  %d %d    val_ini %d  val_fin %d\n\n", N1, C1, N2, C2, u[N1][C1], u[N2][C2]);

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

void Move(int u[8][8], int *Player, Game_Spec *G){
    int FLAG = 0;
    char C1;
    int D1;
    int Cl1;
    char C2;
    int D2;
    int Cl2;
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
                return;
            }
            if (c == 'Y'){
                printf("ENTER CORDINATES OF THE FINAL SQUARE: ");
            }
        }

        // If FLAG!=2 we need to input the coordinates for the initial square , if FLAG=2 we can just use final cord. of last
        // turn as initial coordinates for current turn
        if (FLAG != 2){
            scanf(" %c%d", &C1, &D1);
            Cl1 = C1 - 'A';
            D1--;
            char s[9];
            scanf("%s", s);
        }

        // Asking for final coordinates
        scanf(" %c%d", &C2, &D2);
        Cl2 = C2 - 'A';
        D2--;

        // Checking whether move is correct or not and returning 0 is move is incorrect , we must not return if we are making 
        // successive capture
        int val = CheckMove(u, D1, Cl1, D2, Cl2, FLAG, *Player);
        printf("%d is value returned by CheckMove function \n\n", val);
        if (val == 0 && FLAG != 2){
            printf("WRONG INPUT\n");
            return;
        }
        if (val == 0 && FLAG == 2){
            printf("WRONG INPUT\n");
            continue;
        }

        //here we are checking if the moved coin transformed to king or not
        if (D2 == 0 && u[D1][Cl1] == WHITE){
            u[D1][Cl1] = WHITE_KING;
            Change_To_King = 1;
            G->Num_White_King++;
        }
        if (D2 == 7 && u[D1][Cl1] == BLACK){
            u[D1][Cl1] = BLACK_KING;
            Change_To_King = 1;
            G->Num_Black_King++;
        }

        if (val == 2){
            Kill_Type = u[(D1 + D2) / 2][(Cl1 + Cl2) / 2];
            Kill = 1;
        }

        Insert_move(G, C1, C2, D1, D2, u[D1][Cl1], Kill, Kill_Type, Change_To_King);

        //here we are swapping the final and initial squares
        swap(&u[D1][Cl1], &u[D2][Cl2]);

        if (val == 2){
            u[(D1 + D2) / 2][(Cl1 + Cl2) / 2] = EMPTY;
            FLAG = 2;
            Cl1 = Cl2;
            D1 = D2;
            continue;
        }

        Done = 1;
    } while (Done == 0);

    return ;
}



// This Functions allows the user to Save the Current Game 
void Save(int u[8][8], int Player, Game_Spec* G){

    char Name_Of_Game[106];                             // This variable stores the name of the game

    printf("Enter Name of the Game: ");                 // Asking for Game Namae
    scanf(" %s", Name_Of_Game);                         // Inputting the Game Name

    strcat(Name_Of_Game, ".txt");                       // Game will be stored as <Name_Of_Game>.txt 

    FILE *fp;                                           // Pointer to file
    fp = fopen(Name_Of_Game, "w");                      // Opening in write mode. Will write information of game to this file

    // Storing the location of each token by writing the matrix into file
    for (int i = 0; i < 8; i++){                        // Traverses Rows
        for (int j = 0; j < 8; j++){                    // Traverses Columns
            fprintf(fp, "%d ", u[i][j]);                // Writes Token Type
        }
    }

    fprintf(fp, "%d ", Player);                         // Storing Players turn

    // Storing the Game-Specs
    fprintf(fp, "%d ", G -> Auto_Rotate);               // Writes Auto Rotate Mode
    fprintf(fp, "%d ", G -> Compulsory_Capture);        // Writes Compulsory_Capture Mode
    fprintf(fp, "%d ", G -> Num_Moves);                 // Writes Number of Moves
    fprintf(fp, "%d ", G -> Num_Black);                 // Writes Number of Black Tokens
    fprintf(fp, "%d ", G -> Num_White);                 // Writes Number of White Tokens
    fprintf(fp, "%d ", G -> Num_Black_King);            // Writes Number of Black King Tokens
    fprintf(fp, "%d ", G -> Num_White_King);            // Writes Number of White King Tokens

    struct Change* Temp  = G -> Last_Move;              // Pointer to Doubly Linked List that stores Move History

    while(Temp -> Prev != NULL){                        // Going to end of Linked List before stoing 
        Temp = Temp -> Prev;                            // because initally temp points to Latest move
    }                                                   // but we want to store the first move first

    Temp = Temp -> Next;                                // Makes Temp point to First Move

    while(Temp != NULL){                                // Storing the Move History to allow UNDO Options in Saved Games
         
        fprintf(fp, "%c ", Temp -> Initial_Char);       // Writes Character of Inital Coordinate of token (A/B/C/...H)
        fprintf(fp, "%c ", Temp -> Final_Char);         // Writes Character of Final Coordinate of token (A/B/C/...H)
        fprintf(fp, "%d ", Temp -> Initial_Int);        // Writes Integer of Inital Coordinate of token (1/2/3/...8)
        fprintf(fp, "%d ", Temp -> Final_Int);          // Writes Integer of Final Coordinate of token (1/2/3/...8)
        fprintf(fp, "%d ", Temp -> Type);               // Writes the Type of token that is moved
        fprintf(fp, "%d ", Temp -> Kill);               // Writes whether a Kill was made in this move 
        fprintf(fp, "%d ", Temp -> Kill_Type);          // Writes the type of Kill
        fprintf(fp, "%d ", Temp -> Change_To_King);     // Writes whehther a regular token was changed to King

        Temp = Temp -> Next;                            // Going to Next Move
    }  

    fclose(fp);                                         // Closing the file 'fp'
    return ;
}



// Allows user to Reload a Saved Game
void Load_Saved_Game(char Name_Of_Game[105], Game_Spec* G, int u[8][8], int *Player){

    FILE* fp;                                           // Pointer to File
    fp = fopen(Name_Of_Game, "r");                      // Opens Saved File in Read Mode


    // Reading the location of each token
    for (int i = 0; i < 8; i++){                        // Traverses Rows
        for (int j = 0; j < 8; j++){                    // Traverses Columns
            fscanf(fp, "%d ", &u[i][j]);                // Reads Token Type and stores it in the 2-D Array 'u'
        }
    }

    fscanf(fp, "%d", Player);                           // Reads Player turn

    G = (Game_Spec *)malloc(sizeof(Game_Spec));         // Allocating memory for G
    assert(G != NULL);                                  // Checking if memory is available

    // Reading Game-Specs;
    fscanf(fp, "%d ", &G -> Auto_Rotate);               // Writes Auto Rotate Mode
    fscanf(fp, "%d ", &G -> Compulsory_Capture);        // Writes Compulsory_Capture Mode
    fscanf(fp, "%d ", &G -> Num_Moves);                 // Writes Number of Moves
    fscanf(fp, "%d ", &G -> Num_Black);                 // Writes Number of Black Tokens
    fscanf(fp, "%d ", &G -> Num_White);                 // Writes Number of White Tokens
    fscanf(fp, "%d ", &G -> Num_Black_King);            // Writes Number of Black King Tokens
    fscanf(fp, "%d ", &G -> Num_White_King);            // Writes Number of White King Tokens


    // Initialising Game Board
    G = Init_Game(G -> Auto_Rotate, G->Compulsory_Capture, G-> Num_Moves, G -> Num_Black, G->Num_White, G->Num_Black_King, G->Num_White_King);

    int Num_Moves = G -> Num_Moves;                     // This variable stores Number of Moves made in the Saved Game

    //Initialising Variables of Linked List
    char Initial_Char, Final_Char;
    int Initial_Int, Final_Int, Type, Kill, Kill_Type, Change_To_King ;

    for(int i = 0; i < Num_Moves; i++){

        fscanf(fp, "%c ", &Initial_Char);               // Writes Character of Inital Coordinate of token (A/B/C/...H)
        fscanf(fp, "%c ", &Final_Char);                 // Writes Character of Final Coordinate of token (A/B/C/...H)
        fscanf(fp, "%d ", &Initial_Int);                // Writes Integer of Inital Coordinate of token (1/2/3/...8)
        fscanf(fp, "%d ", &Final_Int);                  // Writes Integer of Final Coordinate of token (1/2/3/...8)
        fscanf(fp, "%d ", &Type);                       // Writes the Type of token that is moved
        fscanf(fp, "%d ", &Kill);                       // Writes whether a Kill was made in this move 
        fscanf(fp, "%d ", &Kill_Type);                  // Writes the type of Kill
        fscanf(fp, "%d ", &Change_To_King);             // Writes whehther a regular token was changed to King

        // Inserting Moves into the Linked List
        Insert_move(G, Initial_Char, Final_Char, Initial_Int, Final_Int, Type, Kill, Kill_Type, Change_To_King);
    }
    
    return ;
}                 