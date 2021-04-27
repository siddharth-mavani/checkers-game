

struct change{                             // this struct stores individual moves , and pointer to the next and previous moves
    char initial_char ;
    char final_char;
    int initial_int ;
    int final_int;
    int type;                               //store the type of token which was moved
    int kill;                               // kill=1 , if that move involved any capture otherwise its 0
    int kill_type;                          //kill_type stores the type of token which was captured (this helps in the  undo func)
    struct change* next;                    // since its a linked list
    struct change* prev;
};

struct game_spec{                         // this struct stores basic info
    int auto_rotate;
    int compulsory_capture;
    int num_moves;
    int num_black;
    int num_white;
    int num_black_king;
    int num_white_king; 
    struct change* moves;                 // this is the linked list which stores all the moves
    struct change* last_move;             // this points to the last move , (helps in UNDO func)  
};

/* Feel free to add anything u want or even change the names of the variables , just let the other people know 
   also the function u are working on may need some extra informatino which isnt included yet , just assume u have that
   information and code it up , later we can include it in the structs */
