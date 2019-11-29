#include <stdio.h>
#include <stdlib.h>
#include <my-ipc.h>
#include <client-side.h>
#include <redundant.h>
#include <public.h>

const char myName[] = "ex3";
const char deployment[] = "Ba3a4a5a6 Cc1c2c3 Cc5c6c7 De1e2 De4e5 De7e8 Sg1 Sg3 Sg5 Sg7 ";

int pre_shot_x, pre_shot_y;

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

int i=0;
int j=0;
void respond_with_shot(void)
{
  char shot_string[MSG_LEN];
  int x, y;

  //=====kokokara========
  if (i==0 || i==8){
 	if (j < 2){ 
	j=2;
	}
	else if (j == 6){
	j = 1;
	i +=1;	
	}
	else {
	j += 1;	
  	}
  }
  else if (i==1 || i ==7){
	if (j==0) j=1;
	else if (j == 7) {
	if (i==1){
	j = 0;
	i += 1;
	}
	else {
	j = 2;
	i += 1;
	}
	}
	else {
	j += 1;
	}
  }
  else {
	if (j == 8) {
	j = 0;
	i += 1;
	}
	else { j+=1;}
  }
   
  x = i;
  y = j;

  //=====kokomade========

  printf("[%s] shooting at %d%d ... ", myName, y, x);
  sprintf(shot_string, "%d%d", y, x);
  send_to_ref(shot_string);
}

void handle_messages(void)
{
  char line[MSG_LEN];

  pre_shot_x = 0;
  pre_shot_y = 0;

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
