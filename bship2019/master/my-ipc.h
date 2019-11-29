/* file = my-ipc.h */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

/* redandant declarations included to satisfy gcc -Wall */
/* int send(int socket, char *msg, int len, int flags);
int socket(int domain, int type, int protocol); */

/* items common to both client and server */
#define ADDRESS "bship-sct"
#define MSG_LEN 100


