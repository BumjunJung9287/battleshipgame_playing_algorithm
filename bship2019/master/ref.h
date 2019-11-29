/* file = ref.h */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server-side.h"

/* provided in ref.c, used by master.c */
void init_ships_boards(void); 
void init_shots_boards(void);
void init_revealed_boards(void);  /* what a player will know so far */
int deploy_ships(int pl, char *deployment);
void print_two_boards(void);
char process_shot(int pl, int shot[2], int print_shots, int noise);
int is_winner(int pl, char other_deployment[], char last_shot_result, int allp);

/* used in display.c and master.c */
char player_name[3][MSG_LEN];
int default_winner;   /* winner in case of timeout or no-pipe signal */

/* used in ref.c and display.c */
int  shots[2][BD_SIZE][BD_SIZE];
char ships[2][BD_SIZE][BD_SIZE];
/* for each square, contains what we last told the player was there,
   which may not be the same as what is actually there */
char revealed[2][BD_SIZE][BD_SIZE]; 
