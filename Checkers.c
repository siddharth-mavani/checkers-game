#include "Checkers.h"

void swap(int *a, int *b)
{

    int temp = *a;
    *a = *b;
    *b = temp;

    return;
}

// Initializes a 'Move' node and returns it.
Move_Node *Makenode(void)
{
    // Allocating the memory
    Move_Node *Temp = (Move_Node *)malloc(sizeof(Move_Node));
    assert(Temp != NULL);

    Temp -> Next = NULL;

    return Temp;
}

// Initializes and returns a new game with the settings and gata passed as variables.
Game_Spec *Init_Game(int Auto_Rotate, int Compulsory_Capture, int Num_Moves, int Num_Black, int Num_White, int Num_Black_King, int Num_White_King, int Board_Orientation, char Name_Of_Player1[NAME_SIZE], char Name_Of_Player2[NAME_SIZE])
{
    // Allocating the memory.
    Game_Spec *Game = (Game_Spec *)malloc(sizeof(Game_Spec));
    assert(Game != NULL);
    // Now assigning the values to the structure elements.
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
    Game -> Moves -> Next = NULL;
    Game -> Last_Move = Game -> Moves;

    return Game;
}

// A function to Insert the 'Move' Node to the doubly linked list of the moves stores in the game structure.
void Insert_move(Game_Spec *Game, char Initial_Char, char Final_Char, int Initial_Int, int Final_Int, int Type, int Kill, int Kill_Type, int Change_To_King)
{
    // Initialising a temporary 'Move' node.
    Move_Node *Curr_Move = Makenode();
    // Assigning values to the temporary 'Move' node.
    Curr_Move -> Initial_Char = Initial_Char;
    Curr_Move -> Final_Char = Final_Char;
    Curr_Move -> Initial_Int = Initial_Int;
    Curr_Move -> Final_Int = Final_Int;
    Curr_Move -> Type = Type;
    Curr_Move -> Kill = Kill;
    Curr_Move -> Kill_Type = Kill_Type;
    Curr_Move -> Change_To_King = Change_To_King;

    Curr_Move -> Next = NULL;
    Curr_Move -> Prev = Game -> Last_Move;
    Game -> Last_Move -> Next = Curr_Move;
    Game -> Last_Move = Curr_Move;

    Game -> Num_Moves++;

    return;
}

//THIS MOVES CHECKS IF ANY SUCCESSIVE CAPTURE IS POSSIBLE
int SuccessiveCapture(int u[BOARD_SIZE][BOARD_SIZE], int InitialInt, int InitialCharToInt, int Player)
{
    int num_kill_possible = 0;
    num_kill_possible += CheckMove(u, InitialInt, InitialCharToInt, InitialInt + 2, InitialCharToInt + 2, 0, Player);   //TOP LEFT DIAGONAL
    num_kill_possible += CheckMove(u, InitialInt, InitialCharToInt, InitialInt - 2, InitialCharToInt - 2, 0, Player);   //BOTTON RIGHT DIAGONAL
    num_kill_possible += CheckMove(u, InitialInt, InitialCharToInt, InitialInt + 2, InitialCharToInt - 2, 0, Player);   //TOP RIGHT DIAGONAL
    num_kill_possible += CheckMove(u, InitialInt, InitialCharToInt, InitialInt - 2, InitialCharToInt + 2, 0, Player);   //BOTTOM LEFT DIAGONAL
    return num_kill_possible / 2;
}


int Undo(int Board[BOARD_SIZE][BOARD_SIZE], struct Game_Spec *G, int *Player, int CallFromKmoves)
{

    if (G -> Num_Moves == 0)                        // if Num_Moves==0 we cant undo anymore
    {
        if(!CallFromKmoves)
        {
            printf("\t NO MOVES LEFT TO UNDO\n");
        }
        return 0;
    }

    int InitialInt = G -> Last_Move -> Initial_Int;
    int FinalInt = G -> Last_Move -> Final_Int;
    char InitialChar = G -> Last_Move -> Initial_Char;
    char FinalChar = G -> Last_Move -> Final_Char;
    int InitialCharToInt = InitialChar - 'A';
    int FinalCharToInt = FinalChar - 'A';

    swap(&Board[InitialInt][InitialCharToInt], &Board[FinalInt][FinalCharToInt]);  //here we are swapping the peices to their position before the move

    if (G -> Last_Move -> Kill == 1)         //here we check if this move involves any capture and if it did we place the capture peice
    {                                        //back at its position
        Board[(InitialInt + FinalInt) / 2][(InitialCharToInt + FinalCharToInt) / 2] = G -> Last_Move -> Kill_Type;
        if(G->Last_Move->Kill_Type==WHITE){G->Num_White++;}
        if(G->Last_Move->Kill_Type==WHITE_KING){G->Num_White_King++;}
        if(G->Last_Move->Kill_Type==BLACK){G->Num_Black++;}
        if(G->Last_Move->Kill_Type==BLACK_KING){G->Num_Black_King++;}
    }

    //now we are checking if any peice changed to king in this move and if it did we change it back
    if (G -> Last_Move -> Change_To_King == 1 && Board[InitialInt][InitialCharToInt] == WHITE_KING)
    {                               
        Board[InitialInt][InitialCharToInt] = WHITE;
        G->Num_White++;
        G->Num_White_King--;
    }

    if (G -> Last_Move -> Change_To_King == 1 && Board[InitialInt][InitialCharToInt] == BLACK_KING)
    {
        Board[InitialInt][InitialCharToInt] = BLACK;
        G->Num_Black++;
        G->Num_Black_King--;
    }

    struct Change *Temp = G -> Last_Move;

    G -> Last_Move = Temp -> Prev;              // here we remove the UNDOed move from the linked list containing all the moves
    G -> Last_Move -> Next = NULL;              // and free its memory

    free(Temp);         

    G -> Num_Moves--;

    if (G -> Last_Move -> Kill == 1 && CallFromKmoves == 0)     // after UNDOing if the previous step involved a capture we call  the move function
    {                                                           // from here in case any successive capture was possible

        *Player = -*Player;
        if (G -> Auto_Rotate)
        {
            G -> Board_Orientation = -G -> Board_Orientation;
        }
        if (Move(Board, Player, G, 1))
        {
            *Player = -*Player;
            if (G -> Auto_Rotate)
            {
                G -> Board_Orientation = -G -> Board_Orientation;
                return 1;
            }
            return 0;
        }
    }
    return 1;
}

int CheckMove(int u[BOARD_SIZE][BOARD_SIZE], int N1, int C1, int N2, int C2, int D, int Player)
{

    // C1 is letter1,C2 is letter 2, N1,N2 are the first and the second numbers
    //printf("initial %d %d    final  %d %d    val_ini %d  val_fin %d\n\n", N1, C1, N2, C2, u[N1][C1], u[N2][C2]);

    if (C1 < 0 || C1 > 7 || N1 < 0 || N1 > 7)
    {
        return 0;
    }
    if (C2 < 0 || C2 > 7 || N2 < 0 || N2 > 7)
    {
        return 0;
    }
    if ((u[N1][C1] * Player) <= 0)
    {
        return 0;
    }

    int Diff_Row = N1 - N2;
    int Diff_Coln = (C1 - C2);

    if (Diff_Coln < 0)
    {
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

    if (u[N1][C1] == WHITE || u[N1][C1] == BLACK)
    {
        if (u[N1][C1] * Diff_Row > 0)
        {
            if (Diff_Coln == 1)
                return 1;
            else
            { // checking if the middle piece is of opponent
                if (u[N1][C1] * u[(N1 + N2) / 2][(C1 + C2) / 2] < 0)
                    return 2; // if the Player has to play another move
                else
                    return 0;
            }
        }
    }

    if (u[N1][C1] == WHITE_KING || u[N1][C1] == BLACK_KING)
    {
        if (Diff_Coln == 1)
            return 1;
        else
        { // checking if the middle piece is of opponent
            if (u[N1][C1] * u[(N1 + N2) / 2][(C1 + C2) / 2] < 0)
                return 2; // if the Player has to play another move
            else
                return 0;
        }
    }

    return 0;
}

void Init(int Board[BOARD_SIZE][BOARD_SIZE])            // This function initialises the board
{

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            Board[i][j] = EMPTY;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if ((i + j) % 2 == 1)
            {
                Board[i][j] = BLACK;                    // here we place all the white and black peices at their initial positions
                Board[7 - i][7 - j] = WHITE;
            }
        }
    }

    return;
}
void print_ll(Game_Spec *g)         //this functino can be used to print all the past moves
{
    Move_Node *curr_move = g -> Moves;
    int i = 0;
    while (curr_move != NULL)
    {
        printf("%c%d-->%c%d  %d\n\n", curr_move -> Initial_Char, curr_move -> Initial_Int, curr_move -> Final_Char, curr_move -> Final_Int, i);
        i++;
        curr_move = curr_move -> Next;
    }
}


int Move(int Board[BOARD_SIZE][BOARD_SIZE], int *Player, Game_Spec *G, int Undo_Call)
{
    int Compul_Capture = 0;
    if (G -> Compulsory_Capture)
    {
        if (Capturepossible(Board, *Player))
        {
            Compul_Capture = 2;             // here we are assuring that we only consider a capture as a possible move (if a capture is possible)
        }                                   // This is only significant when compulsory capture is ON
    }                                       // Compul_Capture==2 implies we only consider captures as possible moves


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
    char Response_Char;


    if (Undo_Call)                          //if Move funnction is called from undo function we already have the initial coordinates
    {                                       // and undo function only calls moves function when a capture was involved in the previous move
        Compul_Capture = 2;                 // so now we only consider captures as possible moves
        FLAG = 2;
        InitialChar = G -> Last_Move -> Final_Char;
        InitialCharToInt = G -> Last_Move -> Final_Char - 'A';
        InitialInt = G -> Last_Move -> Final_Int;
    }


    do                                      // using a do-while loop as players can make successive captures
    {

        //FLAG=2 means a capture has been made in last turn so here we are asking the user for successive capture
        if (FLAG == 2 && G -> Compulsory_Capture == 0)
        {
            Print_Board(Board, G, *Player);
            if(Undo_Call){printf("\tPREVIOUS MOVE INVOVLED A CAPTURE\n");}
            printf("\t DO YOU WANT TO MAKE A SUCCESSIVE CAPTURE(ENTER Y OR N):  ");
            scanf("\n%c", &Response_Char);
            if (Response_Char == 'N')
            {
                return 1;
            }
            if (Response_Char == 'Y')
            {
                printf("\t ENTER CORDINATES OF THE FINAL SQUARE: ");
            }
        }

        // if compulsory capture is ON the player needs to make any possible capture so here we check that
        if (FLAG == 2 && G -> Compulsory_Capture == 1)
        {
            Compul_Capture = 2;
            int NumKillPossible = SuccessiveCapture(Board, InitialInt, InitialCharToInt, *Player);
            if (!NumKillPossible)
            {
                
                return 1;
            }
            Print_Board(Board, G, *Player);
            if(Undo_Call){printf("PREVIOUS MOVE INVOVLED A CAPTURE\n");}
            printf("\tCOMPULSIVE CAPTURE IS ON SO YOU NEED TO MAKE ANY POSSIBLE SUCCESSIVE CAPTURE\n");
            if (NumKillPossible == 1)
            {
                printf("\t1 POSSIBLE CAPTURE IS POSSIBLE\n");
            }
            if (NumKillPossible == 2)
            {
                printf("\t2 POSSIBLE CAPTURES ARE POSSIBLE\n");
            }
            if (NumKillPossible == 3)
            {
                printf("\t3 POSSIBLE CAPTURES ARE POSSIBLE\n");
            }
            printf("\tIF YOU WANT TO UNDO PREVIOUS CAPTUE ENTER \"U1\"\n");
            printf("\tENTER CORDINATES OF THE FINAL SQUARE: ");
        }

        // If FLAG!=2 we need to input the coordinates for the initial square , if FLAG=2 we can just use final cord. of last
        // turn as initial coordinates for current turn
        if (FLAG != 2)
        {
            scanf(" %c%d", &InitialChar, &InitialInt);
            InitialCharToInt = InitialChar - 'A';
            InitialInt--;
            char s[9];
            scanf("%s", s);
            char dummy;
        }

        // Asking for final coordinates
        char dummy_char;
        scanf("%c%c%d", &dummy_char, &FinalChar, &FinalInt);

        if (FinalChar == 'U' && FinalInt == 1)        // this function is used to UNDO a capture made in the current turn 
        {
            if (G -> Auto_Rotate)
            {
                G -> Board_Orientation = -G -> Board_Orientation;
            }
            *Player = -*Player;
            Undo(Board, G, Player, 0);
            return (1 - Undo_Call);                 // the return value here depends on the function calling the move function
        }
        FinalCharToInt = FinalChar - 'A';
        FinalInt--;

        // Checking whether move is correct or not and returning 0 is move is incorrect , we must not return if we are making
        // successive capture
        int val = CheckMove(Board, InitialInt, InitialCharToInt, FinalInt, FinalCharToInt, Compul_Capture, *Player);

        //here we check if the invalid move is invalid due to any possible capture
        if (val == 0 && FLAG != 2)
        {
            if (CheckMove(Board, InitialInt, InitialCharToInt, FinalInt, FinalCharToInt, 0, *Player))
            {
                printf("\t INVALID AS A CAPTURE MUST BE MADE\n");
                return 0;
            }
            printf("\t WRONG INPUT\n");
            return 0;
        }


        if (val == 0 && FLAG == 2)
        {
            printf("\t WRONG INPUT\n");
            continue;
        }


        //here we are checking if the moved coin transformed to king or not
        if (FinalInt == 0 && Board[InitialInt][InitialCharToInt] == WHITE)
        {
            Board[InitialInt][InitialCharToInt] = WHITE_KING;
            Change_To_King = 1;
            G -> Num_White_King++;
            G->Num_White--;
        }
        if (FinalInt == 7 && Board[InitialInt][InitialCharToInt] == BLACK)
        {
            Board[InitialInt][InitialCharToInt] = BLACK_KING;
            Change_To_King = 1;
            G -> Num_Black_King++;
            G->Num_Black--;
        }
 
        //here we check if a capture was made and modify the variables accordingly
        if (val == 2)
        {
            Kill_Type = Board[(InitialInt + FinalInt) / 2][(InitialCharToInt + FinalCharToInt) / 2];
            Kill = 1;
            if(Kill_Type==WHITE){G->Num_White--;}
            if(Kill_Type==WHITE_KING){G->Num_White_King--;}
            if(Kill_Type==BLACK){G->Num_Black--;}
            if(Kill_Type==BLACK_KING){G->Num_Black_King--;}
            
        }

        //here we insert the move in the linked list storing all the moves
        Insert_move(G, InitialChar, FinalChar, InitialInt, FinalInt, Board[InitialInt][InitialCharToInt], Kill, Kill_Type, Change_To_King);
       
        Change_To_King = 0;


        //here we are swapping the final and initial squares
        swap(&Board[InitialInt][InitialCharToInt], &Board[FinalInt][FinalCharToInt]);

        //here we check if a capture was made and modify the board accordingly
        if (val == 2)
        {
            
            Board[(InitialInt + FinalInt) / 2][(InitialCharToInt + FinalCharToInt) / 2] = EMPTY;
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
int Name_Is_Available(char Name_Of_Game[105])
{

    FILE *fp;

    fp = fopen(Name_Of_Game, "r");                                  // opens <Name_Of_Game> in read mode
    if (fp == NULL)
        return 0;                                                   // fp is NULL if <Name_Of_Game> is not available
    else
        return 1;                                                   // returns 1 [TRUE] if <Name_Of_Game> is available

    fclose(fp);
}

// Allows user to update an already saved game.
void Update_gamefile(int u[BOARD_SIZE][BOARD_SIZE], int Player, Game_Spec* G, char Name_Of_Game[NAME_SIZE])
{
    
    char dummy[NAME_SIZE];                                                        // Declaring a dummy string to store the name of the game entered.
    char final_name[NAME_SIZE];                                                   // Stores the final name of the game file.
    strcpy(dummy, Name_Of_Game);
    strcpy(final_name, dummy);
    strcat(dummy, ".txt");

    if(Name_Is_Available(dummy))                                            // Checking if the file with the entered name exists or not.
    {
        int delete = remove(dummy);                                         // Deletes the already saved files.                    
        Save(u, Player, G, Name_Of_Game);                                   // Makes and saves a file with the same name with updated moves.
    }
    else
    {
        while (!(Name_Is_Available(dummy)))                                 // Running a loop untill user inputs correct file name
        { 
            printf("\t THE GAME WITH THIS NAME DOES NOT EXIST, PLEASE ENTER ANOTHER NAME: ");
            scanf(" %s", dummy);
            strcpy(final_name, dummy);
            strcat(dummy, ".txt");                                          // Game will be stored as <Name_Of_Game>.txt
        }
        Save(u, Player, G, Name_Of_Game);
    }    
    return;
}

// This Functions allows the user to Save the Current Game
void Save(int u[BOARD_SIZE][BOARD_SIZE], int Player, Game_Spec *G, char Name_Of_Game[NAME_SIZE])
{

    strcat(Name_Of_Game, ".txt");                                   // Game will be stored as <Name_Of_Game>.txt

    // Checking if the Game exists
    while (Name_Is_Available(Name_Of_Game))                         // Running a loop untill user inputs correct file name
    { 
        printf("\t THE GAME DOES ALREADY EXISTS, PLEASE ENTER ANOTHER NAME: ");
        scanf(" %s", Name_Of_Game);

        strcat(Name_Of_Game, ".txt");                               // Game will be stored as <Name_Of_Game>.txt
    }

    FILE *fp;
    fp = fopen(Name_Of_Game, "w");                                  // opens <Name_Of_Game> in write mode


    // Storing the location of each token by writing the matrix into the file
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            fprintf(fp, "%d ", u[i][j]);
        }
    }

    fprintf(fp, "%d ", Player);                                     // Storing Players turn

    // Storing the Game-Specs
    fprintf(fp, "%d ", G -> Auto_Rotate);                           // Storing Auto-Rotate
    fprintf(fp, "%d ", G -> Compulsory_Capture);                    // Storing Compulsory Capture
    fprintf(fp, "%d ", G -> Num_Moves);                             // Storing Number of Moves made in the Game
    fprintf(fp, "%d ", G -> Num_Black);                             // Storing Number of Black Tokens
    fprintf(fp, "%d ", G -> Num_White);                             // Storing Number of White Tokens
    fprintf(fp, "%d ", G -> Num_Black_King);                        // Storing Number of Black King Tokens
    fprintf(fp, "%d ", G -> Num_White_King);                        // Storing Number of White King Tokens
    fprintf(fp, "%d ", G -> Board_Orientation);                     // Storing Board Orientation
    fprintf(fp, "%s ", G -> Name_Of_Player1);                       // Storing Name of Player 1
    fprintf(fp, "%s ", G -> Name_Of_Player2);                       // Storing Name of Player 2

    struct Change *Temp = G -> Last_Move;                           // Pointer to Doubly Linked List that stores Move History

    while (Temp -> Prev != NULL)
    {                                                               // Going to end of Linked List before stoing
        Temp = Temp -> Prev;                                        // because initally temp points to Latest move
    }                                                               // but we want to store the first move first

    Temp = Temp -> Next;                                            // Points Temp to the very first Move


    // Storing the Move History to allow UNDO Options in Saved Games
    while (Temp != NULL)                                            // Loop runs till Latest/Last Move of the Game
    { 

        fprintf(fp, "%c ", Temp -> Initial_Char);                    // Storing Initial Character of Coordinate of current Move
        fprintf(fp, "%c ", Temp -> Final_Char);                      // Storing Final Character of Coordinate of current Move
        fprintf(fp, "%d ", Temp -> Initial_Int);                     // Storing Initial Integer of Coordinate of current Move
        fprintf(fp, "%d ", Temp -> Final_Int);                       // Storing final Integer of Coordinate of current Move
        fprintf(fp, "%d ", Temp -> Type);                            // Storing Type of Token in Current Move
        fprintf(fp, "%d ", Temp -> Kill);                            // Storing if any Kills were made in Current Move
        fprintf(fp, "%d ", Temp -> Kill_Type);                       // Storing Kill Type of current Move
        fprintf(fp, "%d ", Temp -> Change_To_King);                  // Storing if any ordinary Token was changed to King Token

        Temp = Temp -> Next;                                         // Points to Next Move
    }

    fclose(fp);                                                      // Closing the File
    return;
}

// Allows user to Reload a Saved Game
Game_Spec *Load_Saved_Game(char Name_Of_Game[NAME_SIZE], int u[BOARD_SIZE][BOARD_SIZE], int *Player)
{

    FILE *fp;
    fp = fopen(Name_Of_Game, "r");                                  // opens <Name_Of_Game> in read mode

    // Reading the location of each token
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            fscanf(fp, "%d ", &u[i][j]);
        }
    }

    fscanf(fp, "%d", Player);                                       // Reads Player turn

    // Initialising Variables for Different Variations of the Game
    int Auto_Rotate, Compulsory_Capture, Board_Orientation;
    int Num_Black, Num_White, Num_White_Kings, Num_Black_Kings, Num_Moves;
    char Name_Of_Player1[NAME_SIZE], Name_Of_Player2[NAME_SIZE];

    // Reading Game-Specs;
    fscanf(fp, "%d ", &Auto_Rotate);                                // Reading Auto - Rotate
    fscanf(fp, "%d ", &Compulsory_Capture);                         // Reading Compulsory Capture
    fscanf(fp, "%d ", &Num_Moves);                                  // Reading Number of Moves made in the Game
    fscanf(fp, "%d ", &Num_Black);                                  // Reading Number of Black Tokens
    fscanf(fp, "%d ", &Num_White);                                  // Reading Number of White Tokens
    fscanf(fp, "%d ", &Num_Black_Kings);                            // Reading Number of Black King Tokens
    fscanf(fp, "%d ", &Num_White_Kings);                            // Reading Number of White King Tokens
    fscanf(fp, "%d ", &Board_Orientation);                          // Reading Board Orientation
    fscanf(fp, "%s ", Name_Of_Player1);                             // Reading Name of Player 1
    fscanf(fp, "%s ", Name_Of_Player2);                             // Reading Name of Player 2


    // Initialising Game Board
    Game_Spec *G;
    G = Init_Game(Auto_Rotate, Compulsory_Capture, 0, Num_Black, Num_White, Num_Black_Kings, Num_White_Kings, Board_Orientation, Name_Of_Player1, Name_Of_Player2);

    //Initialising Variables of Linked List
    char Initial_Char, Final_Char;
    int Initial_Int, Final_Int, Type, Kill, Kill_Type, Change_To_King;

    // Reading the Move History
    for (int i = 0; i < Num_Moves; i++)
    {

        fscanf(fp, "%c ", &Initial_Char);                           // Reading Initial Character of Coordinate of current Move
        fscanf(fp, "%c ", &Final_Char);                             // Reading Final Character of Coordinate of current Move
        fscanf(fp, "%d ", &Initial_Int);                            // Reading Initial Integer of Coordinate of current Move
        fscanf(fp, "%d ", &Final_Int);                              // Reading Final Integer of Coordinate of current Move
        fscanf(fp, "%d ", &Type);                                   // Reading Type of Token in Current Move
        fscanf(fp, "%d ", &Kill);                                   // Reading if any Kills were made in Current Move
        fscanf(fp, "%d ", &Kill_Type);                              // Reading Kill Type of current Move
        fscanf(fp, "%d ", &Change_To_King);                         // Reading if any ordinary Token was changed to King Token

        // Inserting Moves into the Linked List
        Insert_move(G, Initial_Char, Final_Char, Initial_Int, Final_Int, Type, Kill, Kill_Type, Change_To_King);
    }

    return G;                                                       // Returning Pointer to Game That was created
}

// Allows user to review the game that is played before/ is currently been played
void game_review(struct Game_Spec *g, int *Player) // The Review Game Function.
{
    if (g  ->  Num_Moves == 0)                                                                  // Checking and returning if the moves in the game are 0.
    {
        printf("\t NO MOVES TILL THIS POINT\n");
        return;
    }
    int temp[8][8];                                                                             // Initialising a temporary array to store the position of the board for review.
    Init(temp);                                                                                 // Setting the board using the Init Function.
    char c;                                                                                     // Character to store the choice of player either to move to next/previous/quit.
    struct Change *curr = g  ->  Moves  ->  Next;                                               // Pointer to the current move (node) which keeps getting updated in throughout the function run-time.
    int orientation = g  ->  Board_Orientation;                                                 // Stores board-orientation, 1 for black's perspective, and -1 for white's perspective

    Print_Board(temp, g, *Player);
    printf("\t YOUR CHOICE: ");
    scanf(" %c", &c);

    if (!((c == 'P' || c == 'p') || (c == 'Q' || c == 'q') || (c == 'N' || c == 'n')))          // Checks if the character input is valid or not.
    {
        while (1)
        {
            printf("\t INVALID INPUT\n\n\t YOUR CHOICE: ");
            scanf(" %c", &c);
            if ((c == 'P' || c == 'p') || (c == 'Q' || c == 'q') || (c == 'N' || c == 'n'))
                break;
        }
    }
    if (c == 'P' || c == 'p')                                                                   // Checks if the character input is P and scans the character again and again till the character input is valid.
    {
        while (1)
        {
            printf("\n\t NO MORE PREVIOUS STEPS ARE LEFT\n\n");
            printf("\t COMMANDS:\n          \t ENTER N FOR NEXT STEP \n          \t ENTER Q TO STOP REVIEWING\n\n");
            printf("\t YOUR CHOICE: ");
            scanf(" %c", &c);

            if (!((c == 'Q' || c == 'q') || (c == 'N' || c == 'n')))                            // Checks for valid input with respect to the condition.
            {
                while (1)
                {
                    printf("\t INVALID INPUT\n\n\t YOUR CHOICE: ");
                    scanf(" %c", &c);
                    if ((c == 'Q' || c == 'q') || (c == 'N' || c == 'n'))
                        break;
                }
            }
            if (c != 'P' || c != 'p')
                break;
        }
    }
    if (c == 'Q' || c == 'q')                                                                   // Checks if user wants to quit reviewing.
    {
        return;
    }
    //orientation *= -1;
    while (curr != NULL)
    {
        int Initial_Int = curr  ->  Initial_Int;                                                // Stores the numeric part of co-ordinate of initial square.
        int Final_Int = curr -> Final_Int;                                                      // Stores the numeric part of co-ordinate of final square.
        char Initial_Char = curr -> Initial_Char;                                               // Stores the character part of co-ordinate of initial square.
        char Final_Char = curr -> Final_Char;                                                   // Stores the character part of co-ordinate of final square.
        int a = Initial_Char - 'A';                                                             // Stores the Initial_Char as an integer to be used in the array.
        int b = Final_Char - 'A';                                                               // Stores the Final_Char as an integer to be used in the array.

        // array change conditions: -

        if (curr -> Change_To_King && (c == 'N' || c == 'n'))                                 // Choice = 'Next Move' and Move involves a change of token to king.
        {
            temp[Initial_Int][a] = 2 * temp[Initial_Int][a];
        }
        if (curr -> Change_To_King && (c == 'P' || c == 'p'))                                 // Choice = 'Previous Move' and Move involves a change from king to a usual token.
        {
            temp[Final_Int][b] = temp[Final_Int][b] / 2;
        }
        if (curr -> Kill && (c == 'N' || c == 'n'))                                           // Choice = 'Next Move' and Move involves a kill.
        {
            temp[(Initial_Int + Final_Int) / 2][(a + b) / 2] = 0;
        }
        if (curr -> Kill && (c == 'P' || c == 'p'))                                           // Choice = 'Previous Move' and Move involves a kill.
        {
            temp[(Initial_Int + Final_Int) / 2][(a + b) / 2] = curr -> Kill_Type;
        }

        swap(&temp[Initial_Int][a], &temp[Final_Int][b]);                                   // Swapping the token on the initial co-ordinate (after updation) and final co-ordinate.
        Print_Board(temp, g, *Player);                                                      // Prints the Board.

        int flag = 0;                                                                       // It is used to keep track of the last choice and work the combinations of the next choice accordingly.
    H1:
        if ((c == 'N' || c == 'n'))
        {
            flag = 1;
        }

        printf("\t YOUR CHOICE: ");
        scanf(" %c", &c);                                                                   // Scanned the choice.
        
        if (!((c == 'P' || c == 'p') || (c == 'Q' || c == 'q') || (c == 'N' || c == 'n')))  // Checking if the character input is valid or not.              
        {
            while (1)
            {
                printf("\t INVALID INPUT\n\n\t YOUR CHOICE: ");
                scanf(" %c", &c);
                if ((c == 'P' || c == 'p') || (c == 'Q' || c == 'q') || (c == 'N' || c == 'n'))
                    break;
            }
        }

        if ((c == 'P' || c == 'p') && curr == g -> Moves -> Next && !flag)                      // Checking if the board is at its initial stage.
        {
            printf("\n\t NO MORE PREVIOUS STEPS ARE LEFT\n\n");
            printf("\t COMMANDS:\n          \t ENTER N FOR NEXT STEP \n          \t ENTER Q TO STOP REVIEWING\n\n");
            flag = 0;
            goto H1;
        }

        if ((c == 'N' || c == 'n') && flag)                                                 // Checks if the choice is the 'Next Move' and last choice was 'Next Move' as well.
        {
            if (curr -> Next == NULL)                                                         // Checking if the board is at its last played position.
            {
                char response;
                printf("\t THE BOARD IS AT THE CURRENT MOVE/SITUATION. \n\t WOULD YOU LIKE THE REVIEW TO END OR YOU WISH TO GO TO THE PREVIOUS MOVE?\n\n");
                printf("\t ENTER YOUR CHOICE(Q TO EXIT, and P TO GO TO THE PREVIOUS MOVE): ");
H2:             scanf(" %c", &response);
                if (response == 'Q' || response == 'q')
                {
                    return;
                }
                else if (response == 'P' || response == 'p')
                {
                    curr = curr;
                    c = 'P';
                }
                else
                {
                    printf("\t INVALID INPUT\n\n\t ENTER YOUR CHOICE(Q TO EXIT, and P TO GO TO THE PREVIOUS MOVE): ");
                    goto H2;
                }
            }
            else
                curr = curr -> Next;
        }
        else if ((c == 'N' || c == 'n') && !flag)                                           // Checking if the current choice is 'Next Move' and last choice was 'Previous Move'.
        {
            curr;
        }
        else if ((c == 'P' || c == 'p') && flag)                                            // Checking if the current choice is 'Previous Move' and the last choice was 'Next Move'.
        {
            curr = curr;
        }
        else if ((c == 'P' || c == 'p') && !flag)                                           // Checking if the current choice is 'Previous Move' and the last choice was 'Previous Move' as well.
        {

            curr = curr -> Prev;
        }
        if (c == 'Q' || c == 'q')                                                           // Checking if the choice is to Quit the review.
        {
            return;
        }
    }

    return;
}

// This Function simulates the Game
void Play_Game(int u[BOARD_SIZE][BOARD_SIZE], int *Player, Game_Spec *G)
{

    char Command[COMMAND_SIZE];

    printf("\n\n");
    Print_Board(u, G, *Player);                                             // Prints Board
    int Temp_Board_Orientation = G -> Board_Orientation;                    // This will give Orientation when User Switches ON Auto Rotate

    while (1)
    {
        printf("\t ENTER COMMAND: ");
        scanf("%s", Command);

        if (strcmp(Command, "MOVE") == 0)                                   // Checks if 'MOVE' is inputted
        { 

            if (Move(u, Player, G, 0))                                      // Checks if a valid Move was made
            { 

                if (endgame(G, u, -(*Player)))                              // Checks if Game has Ended
                { 

                    Print_Board(u, G, *Player);                             // Prints Board

                    if (*Player < 0)                                        // Black has won
                    { 

                        printf("\t %s HAS WON THE GAME!!!!!\nCONGRATULATIONS\n", G -> Name_Of_Player1);
                        printf("\t BETTER LUCK NEXT TIME %s\n", G -> Name_Of_Player2);
                    }
                    else                                                    // White has won
                    { 

                        printf("\t %s HAS WON THE GAME!!!!!\nCONGRATULATIONS\n", G -> Name_Of_Player2);
                        printf("\t BETTER LUCK NEXT TIME %s\n", G -> Name_Of_Player1);
                    }

                    return;
                }
                else
                {
                    
                    *Player = -*Player;                                     // Switches Player

                    if (G -> Auto_Rotate)
                    {                                                       // Checks if Auto-Rotate is on
                        G -> Board_Orientation = -G -> Board_Orientation;   // Toggles Board-Orientation
                    }

                    Temp_Board_Orientation = - Temp_Board_Orientation;      // Switches Temporary Board Orientation

                    Print_Board(u, G, *Player);                             // Prints Board
                }
            }
        }
        else if (strcmp(Command, "UNDO") == 0)                              // Checks if 'Undo' is inputted
        { 
            if (G -> Num_Moves == 0)                                        // Checks if Number of Moves are 0
            { 
                printf("\t NO MOVES LEFT TO UNDO\n");
            }
            else 
            { 

                char permission[5];

                if (*Player > 0)                                            // Checks for Player 2
                { 

                    printf("\t DO YOU AGREE TO UNDO THE CURRENT MOVE %s ? ", G -> Name_Of_Player1);
                    scanf(" %s", permission);

                    // Checks if Player 1 Agreed to Undo Current Move
                    if (strcmp(permission, "YES") == 0 || strcmp(permission, "Y") == 0 || strcmp(permission, "yes") == 0 || strcmp(permission, "y") == 0)
                    {

                        Undo(u, G, Player, 0);                              // Undo's the Current Move

                        *Player = -*Player;                                 // Switches Player

                        if (G -> Auto_Rotate)
                        {                                                       // Checks if Auto-Rotate is on
                            G -> Board_Orientation = -G -> Board_Orientation;   // Toggles Board-Orientation
                        }

                        Temp_Board_Orientation = - Temp_Board_Orientation;      // Switches Temporary Board Orientation
                        
                        Print_Board(u, G, *Player);                             // Prints Board
                    }
                    else
                    {
                        printf("\t SINCE %s DISAGREED, YOU CANNOT UNDO THE CURRENT MOVE %s \n", G -> Name_Of_Player1, G -> Name_Of_Player2);
                    }
                }
                else
                {

                    printf("\t DO YOU AGREE TO UNDO THE CURRENT MOVE %s ? ", G -> Name_Of_Player2);
                    scanf(" %s", permission);

                    // Checks if Player 2 Agreed to Undo Current Move
                    if (strcmp(permission, "YES") == 0 || strcmp(permission, "Y") == 0 || strcmp(permission, "yes") == 0 || strcmp(permission, "y") == 0)
                    {

                        Undo(u, G, Player, 0);                                  // Undo's the Current Move
                        *Player = -*Player;                                     // Switches Player

                        if (G -> Auto_Rotate)
                        {                                                       // Checks if Auto-Rotate is on
                            G -> Board_Orientation = -G -> Board_Orientation;   // Toggles Board-Orientation
                        }
                        
                        Temp_Board_Orientation = - Temp_Board_Orientation;      // Switches Temporary Board Orientation
                        
                        Print_Board(u, G, *Player);                             // Prints Board
                    }
                    else
                    {
                        printf("\t SINCE %s DISAGREED, YOU CANNOT UNDO THE CURRENT MOVE %s \n", G -> Name_Of_Player2, G -> Name_Of_Player1);
                    }
                }
            }
        }
        else if (strcmp(Command, "SETTINGS") == 0)                              // Checks if 'SETTINGS' is inputted
        {
            int choice;
            while(1){

                printf("\n\t\t 1. AUTO ROTATE: %s \n", (G -> Auto_Rotate > 0) ?  "ON" :  "OFF");                    // Prints if Auto Rotate is On or Off
                printf("\t\t 2. COMPULSORY CAPTURE: %s \n", (G -> Compulsory_Capture > 0) ?  "ON" :  "OFF");        // Prints if Compulsory Capture is On or Off
                printf("\t\t 3. BACK TO GAME \n\n");
                                                                                            
                printf("\t\t ENTER YOUR CHOICE: ");                                   
                scanf(" %d", &choice);

                printf("\n");

                if(choice == 1){

                        char s[5];
                        printf("\t\t DO YOU WANT AUTO ROTATE TO BE ON ? ");
                        scanf(" %s", s);
                        printf("\n");
                                            
                         // Checks if User wants Auto Rotate to be ON
                        if(strcmp(s, "YES") == 0 || strcmp(s, "Y") == 0 || strcmp(s, "yes") == 0 || strcmp(s, "y") == 0){
                                G -> Auto_Rotate = 1;
                                G -> Board_Orientation = Temp_Board_Orientation;            // Assigning Current Board Orientation to Game Specs
                        }
                        else
                        {
                                G -> Auto_Rotate = 0;
                        }
                }
                else if(choice == 2){

                        char permission[5];
                        printf("\t\t DO YOU WANT COMPULSORY CAPTURE TO BE ON ? ");
                        scanf(" %s", permission);
                        printf("\n");

                        // Checks if User wants Compulsory Capture to be ON
                        if(strcmp(permission, "YES") == 0 || strcmp(permission, "Y") == 0 || strcmp(permission, "yes") == 0 || strcmp(permission, "y") == 0){
                                G -> Compulsory_Capture = 1;
                        }
                        else{
                                G -> Compulsory_Capture = 0;
                        }
                }
                else{
                        break;
                }
            }
            printf("\n");
        }
        else if (strcmp(Command, "SAVE") == 0)                          // Checks if 'Save' is inputted
        {                        
            char Name_Of_Game[NAME_SIZE];

            printf("\t ENTER NAME OF THE GAME: ");
            scanf(" %s", Name_Of_Game);

            if(strcmp(Name_Of_Game, "BACK") == 0){                      // Checks if 'BACK' is inputted
                continue;                                               // Returns to Game 
            }                                 

            Save(u, *Player, G, Name_Of_Game);                          // Calls Function to Save Game
        }
        else if (strcmp(Command, "UPDATE") == 0)
        {
            char Name_Of_Game[NAME_SIZE];

            printf("\t ENTER NAME OF THE GAME: ");
            scanf(" %s", Name_Of_Game);

            if(strcmp(Name_Of_Game, "BACK") == 0){                      // Checks if 'BACK' is inputted
                continue;                                               // Returns to Game 
            } 

            Update_gamefile(u, *Player, G, Name_Of_Game);
            printf("\n\n");
        }
        else if (strcmp(Command, "NEXTK") == 0)                         // Checks if 'NextK' is inputted
        { 

            int K;

            printf("\t ENTER K: ");
            scanf("%d", &K);

            Next_K_Moves(u, *Player, K, G);                                     // Calls Function to Print Next K Moves
            
            printf("\t THE ABOVE ARE ALL THE POSSIBLE POSITIONS AFTER %d MOVES\n", K );

            Print_Board(u, G, *Player);                                         // Prints Board

        }
        else if (strcmp(Command, "REVIEW") == 0)                                // Checks if 'Review' is inputted
        {
            game_review(G, Player);                                             // Calls Function to Review the Game

            printf("\n\t THE REVIEW HAS BEEN COMPLETED AND THE CURRENT SITUATION OF THE BOARD IS:");
            Print_Board(u, G, *Player);                                         // Prints the game-board.
        }
        else if (strcmp(Command, "QUIT") == 0)                                  // Checks if 'QUIT' is inputted
        { 

            char permission[5];
            printf("\t DO YOU WANT TO SAVE/UPDATE GAME BEFORE QUITTING ? ");
            scanf(" %s", permission);

            // Checks is Player Agreed to Save Game before Quitting
            if (strcmp(permission, "YES") == 0 || strcmp(permission, "Y") == 0 || strcmp(permission, "yes") == 0 || strcmp(permission, "y") == 0)
            {
                char Name_Of_Game[NAME_SIZE];

                printf("\t ENTER NAME OF THE GAME: ");
                scanf(" %s", Name_Of_Game);

                if(strcmp(Name_Of_Game, "BACK") == 0){                      // Checks if 'BACK' is inputted
                    continue;                                               // Returns to Game 
                } 

                Save(u, *Player, G, Name_Of_Game);                          // Calls Function to Save Game
                return;
            }
            if(strcmp(permission, "UPDATE") == 0)
            {
                char Name_Of_Game[NAME_SIZE];

                printf("\t ENTER NAME OF THE GAME: ");
                scanf(" %s", Name_Of_Game);

                if(strcmp(Name_Of_Game, "BACK") == 0){                      // Checks if 'BACK' is inputted
                    continue;                                               // Returns to Game 
                } 

                Update_gamefile(u, *Player, G, Name_Of_Game);
                printf("\n\n");
            }
            
            return;
        }
        else if (strcmp(Command, "SUGGEST") == 0)                               // Checks if 'SUGGEST' is inputted
        {                           
            suggest(u, *Player, G);                                             // Calls the Function to Suggest Moves
        }

        fflush(stdin);                                                          // Clears the input buffer
    }

    return;
}

/* 
    Given a coordinate checks if any moves exists, may print them.
*/
bool PossibleMoves(char coord_letter, int coord_no, int Board[BOARD_SIZE][BOARD_SIZE], int player, bool print, bool capture)
{
    /* 
        c and x together define the corrdinate of the piece for which we find all possible moves
        board is the 8 by 8 matrix of the current state of the board
        player is the integer representing which player's turn it is
        boolean print is a parameter to print the possible positions if it is true
        bool capture is toggled true if a capture exists forcing only the printing of those moves
    */
    bool flag = false;
    coord_no--;
    int y_coord = coord_letter - 'A';
    if (abs(Board[coord_no][y_coord]) == 1) // non king piece
    // by performing x-player we check the forward row for black pieces(-1) and the backward row for white pieces
    {
        if (CheckMove(Board, coord_no, y_coord, coord_no - player, y_coord + 1, 0, player) && y_coord + 1 < BOARD_SIZE && 0 <= coord_no - player < BOARD_SIZE && !capture) //forward/back right diagonal
        {
            if (print)
                printf("\t %c%d -> %c%d\n", coord_letter, coord_no + 1, y_coord + 1 + 'A', coord_no - player + 1);
            flag = true;
        }
        if (CheckMove(Board, coord_no, y_coord, coord_no - player, y_coord - 1, 0, player) && y_coord - 1 >= 0 && 0 <= coord_no - player < BOARD_SIZE && !capture) // forward/back left diagonal
        {
            if (print)
                printf("\t %c%d -> %c%d\n", coord_letter, coord_no + 1, y_coord - 1 + 'A', coord_no - player + 1);
            flag = true;
        }
        if (CheckMove(Board, coord_no, y_coord, coord_no - (2 * player), y_coord + 2, 0, player) && y_coord + 2 < BOARD_SIZE && 0 <= coord_no - (2 * player) < BOARD_SIZE) // forward/back right capture posn
        {
            if (print)
                printf("\t %c%d -> %c%d\n", coord_letter, coord_no + 1, y_coord + 2 + 'A', coord_no + (-2) * player + 1);
            flag = true;
        }
        if (CheckMove(Board, coord_no, y_coord, coord_no + (-2) * player, y_coord - 2, 0, player) && y_coord - 2 >= 0 && 0 <= coord_no - (2 * player) < BOARD_SIZE) // forward/back left capture posn
        {
            if (print)
                printf("\t %c%d -> %c%d\n", coord_letter, coord_no + 1, y_coord - 2 + 'A', coord_no + (-2) * player + 1);
            flag = true;
        }
    }
    else if (abs(Board[coord_no][y_coord]) == 2) //king piece
    {
        if (CheckMove(Board, coord_no, y_coord, coord_no - 1, y_coord - 1, 0, player) && 0 <= y_coord - 1 && 0 <= coord_no - 1 && !capture) // back left diagonal
        {
            if (print)
                printf("\t %c%d -> %c%d\n", coord_letter, coord_no + 1, y_coord - 1 + 'A', coord_no);
            flag = true;
        }
        if (CheckMove(Board, coord_no, y_coord, coord_no - 1, y_coord + 1, 0, player) && y_coord + 1 < BOARD_SIZE && 0 <= coord_no - 1 && !capture) // back right diagonal
        {
            if (print)
                printf("\t %c%d -> %c%d\n", coord_letter, coord_no + 1, y_coord + 1 + 'A', coord_no);
            flag = true;
        }
        if (CheckMove(Board, coord_no, y_coord, coord_no + 1, y_coord - 1, 0, player) && 0 <= y_coord - 1 && coord_no + 1 < BOARD_SIZE && !capture) // forward left diagonal
        {
            if (print)
                printf("\t %c%d -> %c%d\n", coord_letter, coord_no + 1, y_coord - 1 + 'A', coord_no + 2);
            flag = true;
        }
        if (CheckMove(Board, coord_no, y_coord, coord_no + 1, y_coord + 1, 0, player) && y_coord + 1 < BOARD_SIZE && coord_no + 1 < BOARD_SIZE && !capture) // forward right diagonal
        {
            if (print)
                printf("\t %c%d -> %c%d\n", coord_letter, coord_no + 1, y_coord + 1 + 'A', coord_no + 2);
            flag = true;
        }
        if (CheckMove(Board, coord_no, y_coord, coord_no - 2, y_coord - 2, 0, player) && 0 <= y_coord - 2 && 0 <= coord_no - 2) // back left capture posn
        {
            if (print)
                printf("\t %c%d -> %c%d\n", coord_letter, coord_no + 1, y_coord - 2 + 'A', coord_no - 1);
            flag = true;
        }
        if (CheckMove(Board, coord_no, y_coord, coord_no - 2, y_coord + 2, 0, player) && y_coord + 2 < BOARD_SIZE && 0 <= coord_no - 2) // back right capture posn
        {
            if (print)
                printf("\t %c%d -> %c%d\n", coord_letter, coord_no + 1, y_coord + 2 + 'A', coord_no - 1);
            flag = true;
        }
        if (CheckMove(Board, coord_no, y_coord, coord_no + 2, y_coord - 2, 0, player) && 0 <= y_coord - 2 && coord_no + 2 < BOARD_SIZE) // forward left capture posn
        {
            if (print)
                printf("\t %c%d -> %c%d\n", coord_letter, coord_no + 1, y_coord - 2 + 'A', coord_no + 3);
            flag = true;
        }
        if (CheckMove(Board, coord_no, y_coord, coord_no + 2, y_coord + 2, 0, player) && y_coord + 2 < BOARD_SIZE && coord_no + 2 < BOARD_SIZE) // forward right capture posn
        {
            if (print)
                printf("\t %c%d -> %c%d\n", coord_letter, coord_no + 1, y_coord + 2 + 'A', coord_no + 3);
            flag = true;
        }
    }
    return flag;
}

/*
    The suggest function prints all possible moves for a specific colour by calling the PossibleMoves
    function for each piece in the board.
*/
void suggest(int Board[BOARD_SIZE][BOARD_SIZE], int player, Game_Spec *G)
{
    /*
        we take in the current position of the board as input
        player is the number of the current player
        G contains details such as if compulsory capture is on which will alter the possible moves
    */
    bool isCapturePossible = false; //to check if a capture is possible, in which case we print only those values
    if (G -> Compulsory_Capture)
    {
        isCapturePossible = Capturepossible(Board, player);
    }
    bool flag;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 1; j <= BOARD_SIZE; j++)
        {
            flag = PossibleMoves(i + 'A', j, Board, player, true, isCapturePossible);
        }
    }
    printf("\n\n");
}

/*
    Checks if a capture is possible for the player
    Used in scenario when there is Compulsory Capture
*/
bool Capturepossible(int Board[BOARD_SIZE][BOARD_SIZE], int player)
{

    bool flag;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 1; j <= BOARD_SIZE; j++)
        {
            flag = PossibleMoves(i + 'A', j, Board, player, false, true); // we use the PossibleMoves function to see if moves are possible
            if (flag)
            {
                return flag;
            } // if there are captures possible we return true
        }
    }
    return flag;
}

/*
    This function runs after each move performed in the board and checks if the game has ended. The
    function checks the number of pieces for the case of having no more pieces on the board. For the 
    case of not having any moves possible we call the PossibleMoves function for each piece on the 
    board and if no moves exist then the game has ended. The game returns true if the game has 
    ended
*/
bool endgame(Game_Spec *G, int Board[BOARD_SIZE][BOARD_SIZE], int Player)
{
    /*
        we use details such as number of pieces left from the game-spec G
        u is the current position of the board
        player is the value of which player is playing
    */
    if (Player < 0 && (G -> Num_Black + G -> Num_Black_King) == 0) //black player has no more pieces
        return true;
    else if (Player > 0 && (G -> Num_White + G -> Num_White_King) == 0) //white player has no more pieces
        return true;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
            if (Board[i][j] == Player && PossibleMoves(j + 'A', i + 1, Board, Player, false, false)) //if any piece has possible moves PossibleMoves returns true and
                return false;                                                                //thus the game has not ended, hence we return false
    }
    return true; // no pieces of the colours has possible moves, game has ended
}

void copy(int v[BOARD_SIZE ][BOARD_SIZE ], int u [BOARD_SIZE ][BOARD_SIZE ])
{
    for (int i = 0 ; i < BOARD_SIZE  ; i = i + 1)
    {
        for (int j = 0 ; j < BOARD_SIZE  ; j = j + 1)
        {
            v[i][j] = u[i][j] ;
        }
    }

    return ;
}

void move (int u[BOARD_SIZE ][BOARD_SIZE ], int row,int colm,int row_new ,int colm_new)
{
    if (abs(row_new - row) == 1)
    {
        u[row_new][colm_new] = u[row][colm] ;
        u[row][colm] = 0 ;
    }

    if (abs(row_new - row) == 2)
    {
        u[row_new][colm_new] = u[row][colm] ;
        u[row][colm] = 0 ;
        u[ ( row + row_new ) / 2][ ( colm + colm_new ) / 2] = 0 ;
    }

    return ;
}


int Change_To_King (int u[BOARD_SIZE ][BOARD_SIZE ], int player,int FinalRow, int InitialRow, int InitialColm, Vertex* V )
{   
    int change = 0;
        
    if (FinalRow == 0 && u[InitialRow][InitialColm] == WHITE)
    {
        u[InitialRow][InitialColm] = WHITE_KING;
        change = 1;
        V->G->Num_White_King++;
    }
    
    if (FinalRow == 7 && u[InitialRow][InitialColm] == BLACK)
    {
        u[InitialRow][InitialColm] = BLACK_KING;
        change = 1;
        V->G->Num_Black_King++;
       }

    return change ;
}


// after every move have to check if the game has ended.. -- Done
// need to keep int no of moves with final no of moves for the print_sequence function..
// need to convert to kings.. -- Done
void Print_K_Moves(int u[BOARD_SIZE ][BOARD_SIZE ], int player, int k, int count, Vertex* V,int constk)
{
    int v[BOARD_SIZE ][BOARD_SIZE ] = {0} ;
    int change = 0;

    bool is_capture_possible = false ;

    if (endgame(V->G,u,player) == true)
    {
        Print_Board(u,V->G,player) ;
        Undo(v,V->G,&player,1) ;
        return ;
    }
    

    for (int row = 0 ; row < BOARD_SIZE  ; row = row + 1)
    {
        for (int colm = 0 ; colm < BOARD_SIZE  ; colm = colm + 1)
        {
            if (player * u[row][colm] > 0)
                {
                     if (V->G->Compulsory_Capture )
                        is_capture_possible = Capturepossible(u,player) ;

                    int CC = 0 ;
                    if (is_capture_possible)
                        CC = 2;
            {   
                if (count != 2)

                

                if (CheckMove(u,row,colm,row+1,colm+1,CC,player))
                {
                        copy(v,u) ;// copies the state of board from u to v
                        move(v,row,colm,row+1,colm+1) ; // moves the piece from row,colm, to the next place

                        change = Change_To_King(u,player,row+1,row,colm,V) ;
                        Insert_move(V->G,colm + 'A',colm+1 + 'A',row,row+1,u[row][colm] , 0,0, change) ;

                    if ( k != 1)
                    {
                        Print_K_Moves(v,-player,k-1,0,V,constk) ;
                    }

                    if (k == 1)
                    {
                        Print_Board(v, V->G , player) ;// printing board
                        Undo(v,V->G,&player,1) ; //used to go back to last move
                        //return ;
                    }
                }

                if (CheckMove(u,row,colm,row-1,colm-1,CC,player))
                {
                        copy(v,u) ;// copies the state of board from u to v
                        move(v,row,colm,row-1,colm-1) ; // moves the piece from row,colm, to the next place

                        change = Change_To_King(u,player,row-1,row,colm,V) ;
                        Insert_move(V->G,colm + 'A',colm-1 + 'A',row,row-1,u[row][colm] , 0,0,change) ;

                    if ( k != 1)
                    {
                        Print_K_Moves(v,-player,k-1,0,V,constk) ;
                    }

                    if (k == 1)
                    {
                        Print_Board(v, V->G, player) ;// printing board
                        Undo(v,V->G,&player,1) ;//used to go back to last move
                        //return ;
                    }
                }

                if (CheckMove(u,row,colm,row+1,colm-1,CC,player))
                {
                        copy(v,u) ;// copies the state of board from u to v
                        move(v,row,colm,row+1,colm-1) ; // moves the piece from row,colm, to the next place

                        change = Change_To_King(u,player,row+1,row,colm,V) ;
                        Insert_move(V->G,colm + 'A',colm-1 + 'A',row,row+1,u[row][colm] , 0,0,change) ;

                    if ( k != 1)
                    {
                        Print_K_Moves(v,-player,k-1,0,V,constk) ;
                    }

                    if (k == 1)
                    {
                        Print_Board(v, V->G, player) ;// printing board
                        Undo(v,V->G,&player,1) ;//used to go back to last move
                        //return ;
                    }
                }


                if (CheckMove(u,row,colm,row-1,colm+1,CC,player))
                {
                        copy(v,u) ;// copies the state of board from u to v
                        move(v,row,colm,row-1,colm + 1) ; // moves the piece from row,colm, to the next place

                        change = Change_To_King(u,player,row-1,row,colm,V) ;
                        Insert_move(V->G,colm + 'A',colm+1 + 'A',row,row-1, u[row][colm], 0,0,change) ;

                    if ( k != 1)
                    {
                        Print_K_Moves(v,-player,k-1,0,V,constk) ;
                    }

                    if (k == 1)
                    {
                        Print_Board(v,V->G , player) ;// printing board
                        Undo(v,V->G,&player,1) ;//used to go back to last move
                        //return ;
                    }
                }

                }
            

                    if (CheckMove(u,row,colm,row+2,colm+2,CC,player) > 0)
                    {
                        copy(v,u) ;
                        move (v,row,colm,row+2,colm+2) ;
                        change = Change_To_King(u,player,row+2,row,colm,V) ;
                        Insert_move(V->G,colm + 'A',colm+2 + 'A',row,row+2,u[row][colm] ,1,u[(row + row + 2) / 2][(colm + colm + 2) / 2],change) ;
                        if (u[(row + row + 2) / 2][(colm + colm + 2) / 2] > 0)
                            V->Num_W_Capture++;
                        else if (u[(row + row + 2) / 2][(colm + colm + 2) / 2] < 0)
                            V->Num_B_Capture++;
                        
                        count = 2 ;
                        if (endgame(V->G,u,player) == true)
                        {
                            Print_Board(u,V->G,player) ;
                            Undo(v,V->G,&player,1) ;
                            return ;
                        }
                        Print_K_Moves(v,player,k,count,V,constk) ;
                        if (u[(row + row + 2) / 2][(colm + colm + 2) / 2] > 0)
                            V->Num_W_Capture--;
                        else if (u[(row + row + 2) / 2][(colm + colm + 2) / 2] < 0)
                            V->Num_B_Capture--;
                    }


                    if (CheckMove(u,row,colm,row-2,colm-2, CC , player) > 0)
                    {
                        copy(v,u) ;
                        move (v,row,colm,row-2,colm-2) ;
                        change = Change_To_King(u,player,row-2,row,colm,V) ;
                        Insert_move(V->G,colm + 'A',colm-2 + 'A', row,row-2, u[row][colm], 1,u[(row + row - 2) / 2][(colm + colm - 2) / 2],change) ;
                        if (u[(row + row + 2) / 2][(colm + colm + 2) / 2] > 0)
                            V->Num_W_Capture++;
                        else if (u[(row + row + 2) / 2][(colm + colm + 2) / 2] < 0)
                            V->Num_B_Capture++;

                        count = 2 ;
                        if (endgame(V->G,u,player) == true)
                        {
                            Print_Board(u,V->G,player) ;
                            Undo(v,V->G,&player,1) ;
                            return ;
                        }
                        Print_K_Moves(v,player,k,count,V,constk) ;
                        if (u[(row + row + 2) / 2][(colm + colm + 2) / 2] > 0)
                            V->Num_W_Capture--;
                        else if (u[(row + row + 2) / 2][(colm + colm + 2) / 2] < 0)
                            V->Num_B_Capture--;
                    }

                    
                    if (CheckMove(u,row,colm,row+2,colm-2, CC , player) > 0)
                    {
                        copy(v,u) ;
                        move (v,row,colm,row+2,colm-2) ;
                        change = Change_To_King(u,player,row+2,row,colm,V) ;
                        Insert_move(V->G,colm + 'A',colm-2 + 'A',row,row+2,u[row][colm] , 1,u[(row + row + 2) / 2][(colm + colm - 2) / 2], change) ;
                        if (u[(row + row + 2) / 2][(colm + colm + 2) / 2] > 0)
                            V->Num_W_Capture++;
                        else if (u[(row + row + 2) / 2][(colm + colm + 2) / 2] < 0)
                            V->Num_B_Capture++;

                        count = 2 ;
                        if (endgame(V->G,u,player) == true)
                        {
                            Print_Board(u,V->G,player) ;
                            Undo(v,V->G,&player,1) ;
                            return ;
                        }

                        Print_K_Moves(v,player,k,count,V,constk) ;
                        if (u[(row + row + 2) / 2][(colm + colm + 2) / 2] > 0)
                            V->Num_W_Capture--;
                        else if (u[(row + row + 2) / 2][(colm + colm + 2) / 2] < 0)
                            V->Num_B_Capture--;
                    }


                    if (CheckMove(u,row,colm,row-2,colm+2, CC ,player) > 0)
                    {
                        copy(v,u) ;
                        move (v,row,colm,row-2,colm+2) ;
                        change = Change_To_King(u,player,row-2,row,colm,V) ;
                        Insert_move(V->G,colm + 'A',colm+2 + 'A',row,row-2, u[row][colm], 1,u[(row + row -2) / 2 ][ ( colm + colm + 2 ) / 2],change) ;
                        
                        if (u[(row + row + 2) / 2][(colm + colm + 2) / 2] > 0)
                            V->Num_W_Capture++;
                        else if (u[(row + row + 2) / 2][(colm + colm + 2) / 2] < 0)
                            V->Num_B_Capture++;
                        count = 2 ;
                        if (endgame(V->G,u,player) == true)
                        {
                            Print_Board(u,V->G,player) ;
                            Undo(v,V->G,&player,1) ;
                            return ;
                        }

                        Print_K_Moves(v,player,k,count,V,constk) ;
                        if (u[(row + row + 2) / 2][(colm + colm + 2) / 2] > 0)
                            V->Num_W_Capture--;
                        else if (u[(row + row + 2) / 2][(colm + colm + 2) / 2] < 0)
                            V->Num_B_Capture--;
                    }


                   if (count == 2)                        // used to decide when to make next move in case of multiple capture..
                    {
                        copy(v,u) ;
                        // no need to check for king as it is already done in the previous step
                        //Insert_move(V->G,colm,colm+1,row,row+1,u[row][colm] , 0,0, 0) ;

                        if (k != 1)
                        {
                            Print_K_Moves(v,-player,k-1,0,V,constk) ;
                        }

                        if (k == 1)
                        {
                            Print_Board(v,V->G , player) ;// printing board
                        }
                    }

            }
        }
    }
    //if (k != constk)
        Undo(v,V->G,&player,1) ; //used to go back to last move ;
    return ;  

}

void Next_K_Moves(int u[BOARD_SIZE ][BOARD_SIZE ], int player,int k ,Game_Spec* G)
{
    bool is_capture_possible = false ;
    
    Vertex* V = (Vertex*) malloc (sizeof(Vertex)) ;

    V->Num_B_Capture = 0;
    V->Num_W_Capture = 0;
    V->G = G ;
    int count ;
    int change ;
    int v[8][8] ;

    if (k == 1)
    {
        for (int row = 0 ; row < 8 ; row = row + 1)
        {
            for (int colm = 0 ; colm < 8 ; colm = colm + 1)
            {
               count = 0 ;
               if (u[row][colm] * player > 0)
               {

                    if (V->G->Compulsory_Capture )
                        is_capture_possible = Capturepossible(u,player) ;

                    int CC = 0 ;
                    if (is_capture_possible)
                        CC = 2;

                    if (CheckMove(u,row,colm,row+1,colm+1,CC,player))
                    {   
                        change = Change_To_King(u,player,row+1,row,colm,V) ;
                        copy(v,u) ;
                        move(v,row,colm,row + 1,colm+1) ;
                        Insert_move(V->G,colm + 'A',colm + 1 + 'A',row,row+1,u[row][colm],0,0,change) ;
                        Print_Board(v,V->G,player) ;
                        Undo(v,V->G,&player,1) ;
                    }
                   if (CheckMove(u,row,colm,row-1,colm-1,CC,player))
                    {   
                        change = Change_To_King(u,player,row-1,row,colm,V) ;
                        copy(v,u) ;
                        move(v,row,colm,row - 1,colm-1) ;
                        Insert_move(V->G,colm + 'A',colm - 1 + 'A',row,row - 1 ,u[row][colm],0,0,change) ;
                        Print_Board(v,V->G,player) ;
                        Undo(v,V->G,&player,1) ;
                    }
                    if (CheckMove(u,row,colm,row+1,colm-1,CC,player))
                    {   
                        change = Change_To_King(u,player,row+1,row,colm,V) ;
                        copy(v,u) ;
                        move(v,row,colm,row + 1,colm-1) ;
                        Insert_move(V->G,colm + 'A',colm - 1 + 'A',row,row + 1 ,u[row][colm],0,0,change) ;
                        Print_Board(v,V->G,player) ;
                        Undo(v,V->G,&player,1) ;
                    }
                    if (CheckMove(u,row,colm,row-1,colm+1,CC,player))
                    {   
                        change = Change_To_King(u,player,row-1,row,colm,V) ;
                        copy(v,u) ;
                        move(v,row,colm,row - 1,colm+1) ;
                        Insert_move(V->G,colm + 'A',colm + 1 + 'A',row,row - 1 ,u[row][colm],0,0,change) ;
                        Print_Board(v,V->G,player) ;
                        Undo(v,V->G,&player,1) ;
                    }

                    

                    
                    if (CheckMove(u,row,colm,row+2,colm+2,CC,player))
                    {   
                        change = Change_To_King(u,player,row+2,row,colm,V) ;
                        copy(v,u) ;
                        move(v,row,colm,row + 2,colm+2) ;
                        Insert_move(V->G,colm + 'A',colm + 2 + 'A',row,row + 2 ,u[row][colm],1,u[row][colm],change) ;
                        Print_Board(v,V->G,player) ;
                        Undo(v,V->G,&player,1) ;
                    }
                    
                    if (CheckMove(u,row,colm,row-2,colm+2,CC,player))
                    {   
                        change = Change_To_King(u,player,row-2,row,colm,V) ;
                        copy(v,u) ;
                        move(v,row,colm,row - 2,colm+2) ;
                        Insert_move(V->G,colm + 'A',colm + 2 + 'A',row,row - 2 ,u[row][colm],1,u[row][colm],change) ;
                        Print_Board(v,V->G,player) ;
                        Undo(v,V->G,&player,1) ;
                    }


                    if (CheckMove(u,row,colm,row+2,colm-2,CC,player))
                    {   
                        change = Change_To_King(u,player,row+2,row,colm,V) ;
                        copy(v,u) ;
                        move(v,row,colm,row + 2,colm-2) ;
                        Insert_move(V->G,colm + 'A',colm - 2 + 'A',row,row + 2 ,u[row][colm],1,u[row][colm],change) ;
                        Print_Board(v,V->G,player) ;
                        Undo(v,V->G,&player,1) ;
                    }


                    if (CheckMove(u,row,colm,row-2,colm-2,CC,player))
                    {   
                        change = Change_To_King(u,player,row-2,row,colm,V) ;
                        copy(v,u) ;
                        move(v,row,colm,row - 2,colm-2) ;
                        Insert_move(V->G,colm + 'A',colm - 2 + 'A',row,row - 2 ,u[row][colm],1,u[row][colm],change) ;
                        Print_Board(v,V->G,player) ;
                        Undo(v,V->G,&player,1) ;
                    }
               } 
            }
        }
    }

    else
    {
        Print_K_Moves(u,player,k,0,V,k) ;
    }

    free(V) ;

    return ;

}
