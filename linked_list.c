/// linked list 

#include <stdio.h>

typedef struct change
{
    char initial_char ;
    char final_char;
    int initial_int ;
    int final_int;
    int type;                               //store the type of token which was moved
    int kill;                               // kill=1 , if that move involved any capture otherwise its 0
    int kill_type;                          //kill_type stores the type of token which was captured (this helps in the  undo func)
    struct change* next;                    // since its a linked list
    struct change* prev;
}Move_node;

                                                
typedef struct game_spec                    // this struct stores basic info
{
    int auto_rotate;
    int compulsory_capture;
    int num_moves;
    int num_black;
    int num_white;
    int num_black_king;
    int num_white_king; 
    struct change* moves;                 // this is the linked list which stores all the moves
    struct change* last_move;             // this points to the last move , (helps in UNDO func)  
}game_spec;


Move_node* Makenode(void)
{
    Move_node* temp = (Move_node*)malloc(sizeof(Move_node));
    assert(temp != NULL);

    temp->next = NULL;

    return temp;
}

game_spec* Init_game(int auto_rotate, int compulsory_capture, int num_moves, int num_black, int num_white, int num_black_king, int num_white_king)
{
    game_spec* game = (game_spec*)malloc(sizeof(game_spec));
    assert( game != NULL);

    game->auto_rotate = auto_rotate;
    game->compulsory_capture = compulsory_capture;
    game->num_moves = num_moves;
    game->num_black = num_black;
    game->num_white = num_white;
    game->num_black_king = num_black_king;
    game->num_white_king = num_white_king;

    game->moves = NULL;
    game->last_move = game->moves;
    
    return game;
}

void Insert_move(game_spec* game, char initial_char, char final_char, int initial_int, int final_int, int type, int kill, int kill_type)
{
    Move_node* curr_move = Makenode();

    curr_move->initial_char = initial_char;
    curr_move->final_char = final_char;
    curr_move->initial_int = initial_int;
    curr_move->final_int = final_int;
    curr_move->type = type;
    curr_move->kill = kill;
    curr_move->kill_type = kill_type;

    curr_move->next = NULL;

    if(game->last_move == NULL)
    {
        game->moves->next = curr_move;
        curr_move->prev = game->moves;
        game->last_move = curr_move;
    }
    else{
        game->last_move->next = curr_move;
        curr_move->prev = game->last_move;
    }

    game->num_moves++;
    

    // needs attention here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    game->num_black;
    game->num_black_king;
    game->num_white;
    game->num_white_king;
    
    return;
}

void Delete_game(game_spec** game)
{
    Move_node* tempPtr;

    tempPtr = (*game)->last_move->prev;

    while(1)
    {
        free((*game)->last_move);
        (*game)->last_move = tempPtr;
        tempPtr = (*game)->last_move->prev;

        if(tempPtr == (*game)->moves)
        {
            free((*game)->last_move);
            break;
        }
    }

    free(*game);

    return;
}

