/* for util.c */

int other_player(int player);

int in_range(int position); 
int shipp(char code);
int rockp(char code);		     

int convert_pos_char(char schar);      

void init_ships_boards();

/*
int y_or_n(char *prompt);
int ret_or_q(char *prompt);
int ask_number(char *string);
void demand_confirmation(char *prompt);

char *standard_deployment(void);
char *prompt_for_deployment(void);
*/
