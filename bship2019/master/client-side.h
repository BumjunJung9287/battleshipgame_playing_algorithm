/* this file = client-side.h */
#include "my-ipc.h"

/* all these functions are provided in client-side.c */
void client_make_connection(void);
void client_close_connection(void);
void send_to_ref(char *string);
void receive_from_ref(char *line);

int message_has_type(char *message, char *word);
