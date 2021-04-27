


void undo(int u[8][8] , struct game_spec* g){
    if(g->num_moves==0){printf("NO MOVES LEFT TO UNDO\n");return;}
    int a1 = g->last_move->initial_int;
    int b1 = g->last_move->final_int;
    char a2 = g->last_move->initial_char;
    char b2 = g->last_move->final_char;
    int a3=a2-'A';
    int b3=b2-'A';
    swap(&u[a1][a3],&u[b1][b3]);
    if(g->last_move->kill==1){u[(a1+b1)/2][(a3+b3)/2]=g->lastmove->kill_type;}
    struct change* temp = g->last_move;
    g->last_move=g->last_move->prev;
    g->last_move->next=NULL;
    free(temp);
    g->num_moves--;
}
