#include <stdio.h>
#include <stdlib.h>
#include <my-ipc.h>
#include <client-side.h>
#include <redundant.h>
#include <public.h>

const char myName[] = "ex4";
const char deployment[] = "Ba3a4a5a6 Cc1c2c3 Cc5c6c7 De1e2 De4e5 De7e8 Sg1 Sg3 Sg5 Sg7 ";

// Bi2i3i4i5 Cd0d1d2 Cd6e6f6 Da5b5 Df3g3 Df8g8 Sb1 Sb3 Sd4 Sf1
enum ship {
  UNKNOWN,
  ROCK,
  SHOT
};

enum ship enemy_board[BD_SIZE][BD_SIZE];    // BD_SIZE is 9 (defined in public.h)

int is_not_rock(int x, int y){
  if ((x==0&&(y==0||y==1||y==7||y==8))||(x==1&&(y==0||y==8))||(x==7&&(y==0||y==8))||(x==8&&(y==0||y==1||y==7||y==8))) return 0;
  else return 1;
}

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

void init_board(void){
  int ix, iy;

  for(ix = 0; ix < (BD_SIZE); ix++)
  {
    for(iy = 0; iy < (BD_SIZE); iy++)
    {
      //======kokokara======


      //======kokomade======
    }
  }

  //rock is out of bound

  enemy_board[0][0] = ROCK;

  //======kokokara======


  //======kokomade======
}

int r[BD_SIZE][BD_SIZE];
void respond_with_shot(void)
{
  char shot_string[MSG_LEN];
  int x, y;
  
  while (TRUE)
  {
    x = rand() % BD_SIZE;
    y = rand() % BD_SIZE;
    //=====kokokara====	
    if (is_not_rock(x,y)==1){
      if (r[x][y] == 0){
	r[x][y] = 1;
	break;
      }
    }
	
    //=====kokomade=====
  }
  printf("[%s] shooting at %d%d ... ", myName, x, y);
  sprintf(shot_string, "%d%d", x, y);
  send_to_ref(shot_string);
}

void handle_messages(void)
{
  char line[MSG_LEN];

  srand(getpid());
  init_board();

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
