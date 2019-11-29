#include <stdio.h>
#include <stdlib.h>
#include <my-ipc.h>
#include <client-side.h>
#include <redundant.h>
#include <public.h>

const char myName[] = "ex2";
const char deployment[] = "Bc8d8e8f8 Ca4a5a6 Ce0f0g0 Dc4c5 Dg6h6 Dh2i2 Sb1 Sh4 Sf2 Se6 ";

void respond_with_name(void)
{
  char *str = (char *)malloc(sizeof(myName));
  strcpy(str, myName);
  send_to_ref(str);
  free(str);
}

void respond_with_deployment(void)
{
  char *str = (char *)malloc(sizeof(deployment));
  strcpy(str, deployment);
  send_to_ref(str);
  free(str);
}
int r[9][9] = {{0}};
int is_rock(int x, int y){
  if ((x==0&&(y==0||y==1||y==7||y==8))||(x==1&&(y==0||y==8))||(x==7&&(y==0||y==8))||(x==8&&(y==0||y==1||y==7||y==8))) return 1;
  else return 0;
}
void respond_with_shot(void)
{
  char shot_string[MSG_LEN];
  int x, y;

  //=====kokokara========
do{
  x = rand()%9;
  if (x==8 || x == 0) y = (rand()%5 + 2);
  else if (x == 1 || x == 7) y = (rand()%7 +1);
  else y = rand()%9;
}while(is_rock(x,y) == 1);
 

  //=====kokomade========

  printf("[%s] shooting at %d%d ... ", myName, x, y);
  sprintf(shot_string, "%d%d", x, y);
  send_to_ref(shot_string);
}

void handle_messages(void)
{
  char line[MSG_LEN];

  srand(getpid());

  while (TRUE)
  {
    receive_from_ref(line);

    if(message_has_type(line, "name?"))
    {
      respond_with_name(); 
    }
    else if(message_has_type(line, "deployment?"))
    {
       respond_with_deployment(); 
    }
    else if(message_has_type(line, "shot?"))
    {
      respond_with_shot(); 
    }
    else if(message_has_type(line, "shot-result:"))
    {
     printf("[%s] result: %c\n", myName, line[13]);
    }
    else if(message_has_type(line, "end:"))
    {
      break;
    }
    else
    {
      printf("[%s] ignoring message: %s", myName, line);
    }
  }
}

int main()
{
  client_make_connection();
  handle_messages();
  client_close_connection();
  return 0;
}
