/* this file = server-side.h */
#include "my-ipc.h"  

#define CONNECT_TIMEOUT 60   /* seconds */
#define READ_TIMEOUT 25      /* seconds */

void make_socket(void);
void close_main_socket(void);
void accept_connection(int pnum, int timeout);

void server_close_connections(void);

void connection_timeout(int sig);
void read_timeout(int sig);
void pipe_gone(int sig);

void send_to_player(int player, char *string);
void read_from_player(int player, char *line);

/* system functions used in server-side.c, declared to satisfy gcc -Wall */
int unlink(char *path);
/* int bind(int socket, struct sockaddr_un *name, int namelen);
int listen(int socket, int backlog); */
int close(int fd);
/* int accept(int s, struct sockaddr_un *addr, int *addrlen); */
