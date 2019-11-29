#include <stdio.h>
#include <stdlib.h>
#include <my-ipc.h>
#include <client-side.h>
#include <redundant.h>
#include <public.h>
#define TESTSIZE 21

const char myName[] = "03190276";
const char deployment[] = "Bc8d8e8f8 Ca4a5a6 Ce0f0g0 De4f4 Dg6h6 Dh2i2 Sb1 Sh4 Sf2 Se6 ";

int b,c,d = 0;
int bb[8] = {0};
int cc[6] = {0};
int dd[4] = {0};
int testint = 0;
int testintarr[TESTSIZE][2] =  { {0,2},{0,6},{2,8},{2,0}, {6,8},{6,0},{8,6},{8,2}, {1,1},{1,7},{7,1},{7,7}, {2,2},{6,2},{2,6},{6,6}, {4,4} };

enum ship {
  UNKNOWN,
  ROCK,
  NOSHIP,
  BSHIP,
  CSHIP,
  DSHIP,
  SSHIP
};

int cur_x,cur_y;
enum ship enemy_board[BD_SIZE][BD_SIZE];    // BD_SIZE is 9 (defined in public.h)


void it_was_s(int x, int y){
  if (x+1<9){
    enemy_board[x+1][y] = NOSHIP;
    if (y+1<9) enemy_board[x+1][y+1] = NOSHIP;
    if (y-1>=0) enemy_board[x+1][y-1] = NOSHIP;
  }
  if (x-1>=0){
    enemy_board[x-1][y] = NOSHIP;
    if (y+1 < 9) enemy_board[x-1][y+1] = NOSHIP;
    if (y-1 >= 0) enemy_board[x-1][y-1] = NOSHIP;
  }
  if (y+1<9) enemy_board[x][y+1] = NOSHIP;
  if (y-1>=0) enemy_board[x][y-1] = NOSHIP;
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

int is_rock(int x, int y){
  if ((x==0&&(y==0||y==1||y==7||y==8))||(x==1&&(y==0||y==8))||(x==7&&(y==0||y==8))||(x==8&&(y==0||y==1||y==7||y==8))) return 1;
  else return 0;
}

void init_board(void)
{
  //======kokokara======
  int i,j;
  for (i=0;i<9;i++){
    for (j=0;j<9;j++){
      if (is_rock(i,j) == 0){
	enemy_board[i][j] = UNKNOWN;	
      }
      else if(is_rock(i,j)==1){
	enemy_board[i][j] = ROCK;			
      }	
    }
  }

  //======kokomade======
}

void respond_with_shot(void)
{
  char shot_string[MSG_LEN];
  int x, y;
  
  while (TRUE)
    {
      
      if (b==0 && c==0 && d==0 && testint<TESTSIZE){
	
	x = testintarr[testint][0];
	y = testintarr[testint][1];
	testint ++;
	if (enemy_board[x][y] == UNKNOWN) break;
	else continue;
	/*if (testint == 0){
	  testint = 1;
	  x = 2;
	  y = 5;
	  if (enemy_board[x][y] == UNKNOWN) break;
	  else continue;
	  }
	if (testint == 1){
	  testint = 2;
	  x = 4;
	  y = 3;
	  if (enemy_board[x][y] == UNKNOWN) break;
	  else continue;
	  }
	if (testint == 2){
	  testint = 3;
	  x = 2;
	  y = 3;
	  if (enemy_board[x][y] == UNKNOWN) break;
	  else continue;
	  }*/
	
      } 
      
      
      x = rand() % BD_SIZE;
      y = rand() % BD_SIZE;
      //=====kokokara=====
      if (b==1){
	x = bb[4];
	y = bb[5];
	break;
      }
      else if (b==10){
	x = bb[6];
	y = bb[7];
	while (TRUE) { //fix this later
	  bb[6] = x;
	  bb[7] = y;
	  int r;
	  r = rand()%4;
	  
	  /*やってる途中、ここに最適な方向選択アルゴリズム入れること。*/
	// x,y 方向に３マスしかスペースがないとき異なる方向を決めるように。
	  if ( ( (x-1<0 || (x-1>=0 && enemy_board[x-1][y] != UNKNOWN)) && (x+3>=9 || (x+3<9 && enemy_board[x+3][y] != UNKNOWN)) ) || ( (x-2<0 || (x-2>=0 && enemy_board[x-2][y] != UNKNOWN)) && (x+2>=9 || (x+2<9 && enemy_board[x+2][y] != UNKNOWN)) ) || ( (x-3<0 || (x-3>=0 && enemy_board[x-3][y] != UNKNOWN)) && (x+1>=9 || (x+1<9 && enemy_board[x+1][y] != UNKNOWN)) ) ){
	    int rr;
	    rr = rand()%2;
	    if(rr==0 && y+1<9 && enemy_board[x][y+1] == UNKNOWN){
	      if (y+2>=9 || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)){
		continue;
	      }
	      bb[4] = x;
	      bb[5] = y+1;
	      b=1;
	      break;
	    }
	    else if (rr==1 && y-1>=0 && enemy_board[x][y-1] == UNKNOWN){
	      if (y-2<0 || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN)){
		continue;
	      }	
	      bb[4] = x;
	      bb[5] = y-1;
	      b=1;
	      break;
	    }
	    continue;
	  }
	  else if ( ( (y-1<0 || (y-1>=0 && enemy_board[x][y-1] != UNKNOWN)) && (y+3>=9 || (y+3<9 && enemy_board[x][y+3] != UNKNOWN)) ) || ( (y-2<0 || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN)) && (y+2>=9 || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)) ) || ( (y-3<0 || (y-3>=0 && enemy_board[x][y-3] != UNKNOWN)) && (y+1>=9 || (y+1<9 && enemy_board[x][y+1] != UNKNOWN)) ) ){
	    int rr;
	    rr = rand()%2;
	    if (rr==0 && x+1<9 && enemy_board[x+1][y] == UNKNOWN){
	      if (x+2>=9 || (x+2<9 && enemy_board[x+2][y] != UNKNOWN)){
		continue;
	      }
	      bb[4] = x+1;
	      bb[5] = y;
	      b=1;
	      break;
	    }
	    else if (rr==1 && x-1>=0 && enemy_board[x-1][y] == UNKNOWN){
	      if (x-2<0 || (x-2>=0 && enemy_board[x-2][y] != UNKNOWN)){
		continue;
	      }
	      bb[4] = x-1;
	      bb[5] = y;
	      b=1;
	      break;
	    }	
		continue;
	  }
	  
	  
	  
	  if(r==0 && y+1<9 && enemy_board[x][y+1] == UNKNOWN){
	    if (y+2>=9 || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)){
	      continue;
	    }
	    bb[4] = x;
	    bb[5] = y+1;
	    b=1;
	    break;
	  }
	  else if (r==1 && x+1<9 && enemy_board[x+1][y] == UNKNOWN){
	    if (x+2>=9 || (x+2<9 && enemy_board[x+2][y] != UNKNOWN)){
	      continue;
	    }
	    bb[4] = x+1;
	    bb[5] = y;
	    b=1;
	    break;
	  }
	  else if (r==2 && y-1>=0 && enemy_board[x][y-1] == UNKNOWN){
	    if (y-2<0 || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN)){
	      continue;
	    }
	    bb[4] = x;
	    bb[5] = y-1;
	    b=1;
	    break;
	  }
	  else if (r==3 && x-1>=0 && enemy_board[x-1][y] == UNKNOWN){
	    if (x-2<0 || (x-2>=0 && enemy_board[x-2][y] != UNKNOWN)){
	      continue;
	    }
	    bb[4] = x-1;
	    bb[5] = y;
	    b=1;
	    break;
	  }	
	  
	}
	b=1;
	x = bb[4];
	y = bb[5];
	break;
      }
      else if (b==2){
	x = bb[2];
	y = bb[3];
	break;
      }
      else if (b==3){
      x = bb[0];
      y = bb[1];
      break;
      }
      else if (b==4){
	it_was_s(bb[0],bb[1]);
	it_was_s(bb[2],bb[3]);
	it_was_s(bb[4],bb[5]);
	it_was_s(bb[6],bb[7]);
	enemy_board[bb[0]][bb[1]] = BSHIP;
	enemy_board[bb[2]][bb[3]] = BSHIP;
	enemy_board[bb[4]][bb[5]] = BSHIP;
	enemy_board[bb[6]][bb[7]] = BSHIP;
	b = 0;
	continue;
      }
      else if (b==8){
	int x2,y2,x3,y3;
	x2 = 2*bb[2] - bb[4];
	y2 = 2*bb[3] - bb[5];
	x3 = 2*bb[6] - bb[4];
	y3 = 2*bb[7] - bb[5];
	int x22,y22,x33,y33;
	x22 = 2*bb[4] - bb[6];
	y22 = 2*bb[5] - bb[7];
	x33 = 2*bb[2] - bb[6];
	y33 = 2*bb[3] - bb[7];
	if (bb[0] == x2 && bb[1] == y2){
	  bb[0] = x3;
	  bb[1] = y3;
	}
	else if (bb[0] == x3  && bb[1] == y3){
	  bb[0] = x2;
	  bb[1] = y2;
	}
	else if (bb[0] == x22 && bb[1] == y22){
	  bb[0] = x33;
	  bb[1] = y33;
	}
	else if (bb[0] == x33 && bb[1] == y33){
	  bb[0] = x22;
	  bb[1] = y22;
	}
	
	
	x = bb[0];
	y = bb[1];
	break;
      }
      else if(b==9 || b==7){
	it_was_s(bb[0],bb[1]);
	it_was_s(bb[2],bb[3]);
	it_was_s(bb[4],bb[5]);
	it_was_s(bb[6],bb[7]);
	enemy_board[bb[0]][bb[1]] = BSHIP;
	enemy_board[bb[2]][bb[3]] = BSHIP;
	enemy_board[bb[4]][bb[5]] = BSHIP;
	enemy_board[bb[6]][bb[7]] = BSHIP;
	b = 0;
	continue;
      }
      else if (b==5){
	int x2,y2,x3,y3;
	x2 = 2*bb[4] - bb[6];
	y2 = 2*bb[5] - bb[7];
	x3 = 2*bb[6] - bb[4];
	y3 = 2*bb[7] - bb[5];
	if (bb[2] == x2 && bb[3] == y3){
	  bb[2] = x3;
	  bb[3] = y3;
	  x = bb[2];
	  y = bb[3];
	  break;
	}
	else{
	  bb[2] = x2;
	  bb[3] = y2;
	  x = bb[2];
	  y = bb[3];
	  break;
	}
      }
      else if (b==6){
	int x2,y2,x3,y3;
	x2 = 2*bb[2] - bb[4];
	y2 = 2*bb[3] - bb[5];
	x3 = 2*bb[2] - bb[6];
	y3 = 2*bb[3] - bb[7];
	if (bb[4] == bb[2] + bb[6] && bb[5] == bb[3] + bb[7]){
	  bb[0] = x2;
	  bb[1] = y2;
	  x = bb[0];
	  y = bb[1];
	  break;
	}
	else if (bb[6] == bb[4] + bb[2] && bb[7] == bb[5] + bb[3]){
	  bb[0] = x3;
	  bb[1] = y3;
	  x = bb[0];
	  y = bb[1];
	  break;  //b=7のときのNOSHIP追加はb=9の分岐にまとめた。
	}
      }
      
      
      //bship end
      
      if (c==1){
	x = cc[2];
	y = cc[3];
	break;
      }
      else if (c==10){
	x = cc[4];
	y = cc[5];
	while(TRUE){
	  int r;
	  r = rand()%4;
	  
	  if ( ( (x+1>=9||(x+1<9&&enemy_board[x+1][y]!=UNKNOWN)) && (x-2<0 ||(x-2>=0 && enemy_board[x-2][y] != UNKNOWN)) ) || ( (x-1<0 ||(x-1>=0 &&enemy_board[x-1][y] != UNKNOWN)) && (x+2>=9 || (x+2<9 && enemy_board[x+2][y] != UNKNOWN)) ) ){
	    if (y+1<9 && enemy_board[x][y+1] == UNKNOWN){
	      cc[2] = x;
	      cc[3] = y+1;
	    }
	    else if (y-1>=0 && enemy_board[x][y-1] == UNKNOWN){
	      cc[2] = x;
	      cc[3] = y-1;
	    }
	    break;
	  }
	  else if ( ( (y+1>=9 || (y+1<9 && enemy_board[x][y+1] != UNKNOWN)) && (y-2<0 || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN)) ) || ( (y+2>=9 || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)) && (y-1<0 || (y-1>=0 &&enemy_board[x][y-1] != UNKNOWN)) ) ){
	    if (x+1<9 && enemy_board[x+1][y] == UNKNOWN){
	      cc[2] = x+1;
	      cc[3] = y;	
	    }
	    else if (x-1>=0 && enemy_board[x-1][y] == UNKNOWN){
	      cc[2] = x-1;
	      cc[3] = y;
	    }
	    break;
	  }
	  
	  if ((x+1 >= 9 || (x+1<9 && enemy_board[x+1][y]!=UNKNOWN))&& (x-1<0 ||(x-1>=0 &&enemy_board[x-1][y] != UNKNOWN)) && (y+2>=9 || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)) && (y-2<0 || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN))){
	    if (y+1<9 && enemy_board[x][y+1] == UNKNOWN){
	      cc[2] = x;
	      cc[3] = y+1;
	    }
	    else if (y-1>=0 && enemy_board[x][y-1] == UNKNOWN){
	      cc[2] = x;
	      cc[3] = y-1;
	    }
	    break;	
	  }
	  if ((y+1>=9 || (y+1<9 && enemy_board[x][y+1] != UNKNOWN)) && (y-1<0 || (y-1>=0 &&enemy_board[x][y-1] != UNKNOWN)) && (x+2>=9 || (x+2<9 && enemy_board[x+2][y] != UNKNOWN)) && (x-2<0 ||(x-2>=0 && enemy_board[x-2][y] != UNKNOWN))){
	    if (x+1<9 && enemy_board[x+1][y] == UNKNOWN){
	      cc[2] = x+1;
	      cc[3] = y;	
	    }
	    else if (x-1>=0 && enemy_board[x-1][y] == UNKNOWN){
	      cc[2] = x-1;
	      cc[3] = y;
	    }
	    break;
	  }
	  
	  
	  
	  else if (((x+1>=9||(x+1<9&&enemy_board[x+1][y]!=UNKNOWN)) && (x+2>=9||(x+2<9&&enemy_board[x+2][y]!=UNKNOWN)) && (y+2>=9 || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)) && (x-2<0 ||(x-2>=0 && enemy_board[x-2][y] != UNKNOWN)) && (y-2<0 || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN)))||((x-1<0 || (x-1>=0 && enemy_board[x-1][y] != UNKNOWN)) &&(x-2<0 ||(x-2>=0 && enemy_board[x-2][y] != UNKNOWN)) && (y+2>=9 || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)) && (x+2>=9 ||(x+2<9 && enemy_board[x+2][y] != UNKNOWN)) && (y-2<0 || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN)))){
	    if (y+1<9 && enemy_board[x][y+1] == UNKNOWN){
	      cc[2] = x;
	      cc[3] = y+1;
	    }
	    else if (y-1>=0 && enemy_board[x][y-1] == UNKNOWN){
	      cc[2] = x;
	      cc[3] = y-1;
	    }
	    break;
	  }
	  else if ((y+2>=9 || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)) && (x-2<0 ||(x-2>=0 && enemy_board[x-2][y] != UNKNOWN)) && (y-2<0 || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN)) && (x+2>=9||(x+2<9&&enemy_board[x+2][y]!=UNKNOWN))){
	    if (x+1<9 && enemy_board[x+1][y] == UNKNOWN){
	      cc[2] = x+1;
	      cc[3] = y;	
	    }
	    else if (x-1>=0 && enemy_board[x-1][y] == UNKNOWN){
	      cc[2] = x-1;
	      cc[3] = y;
	    }
	    break;
	  }
	  else if (((x+1>=9 || (x+1<9 && enemy_board[x+1][y] != UNKNOWN)) && (y+2>=9 || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)) && (x-2<0 ||(x-2>=0 && enemy_board[x-2][y] != UNKNOWN)) && (y-2<0 || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN)))||((x-1<0 || (x-1>=0 && enemy_board[x-1][y] != UNKNOWN)) && (y+2>=9 || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)) && (x+2>=9 ||(x+2<9 && enemy_board[x+2][y] != UNKNOWN)) && (y-2<0 || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN)))){
	    if (y+1<9 && enemy_board[x][y+1] == UNKNOWN){
	      cc[2] = x;
	      cc[3] = y+1;
	    }
	    else if (y-1>=0 && enemy_board[x][y-1] == UNKNOWN){
	      cc[2] = x;
	      cc[3] = y-1;
	    }
	    break;
	  }
	  else if (((y+1>=9 || (y+1<9 && enemy_board[x][y+1] != UNKNOWN)) && (x+2>=9 || (x+2<9 && enemy_board[x+2][y] != UNKNOWN)) && (x-2<0 ||(x-2>=0 && enemy_board[x-2][y] != UNKNOWN)) && (y-2<0 || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN)))||((y-1<0||(y-1>=0 && enemy_board[x][y-1] != UNKNOWN)) && (y+2>=9 || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)) && (x-2<0 ||(x-2>=0 && enemy_board[x-2][y] != UNKNOWN)) && (x+2>=9 || (x+2<9 && enemy_board[x+2][y] != UNKNOWN)))){
	    if (x+1<9 && enemy_board[x+1][y] == UNKNOWN){
	      cc[2] = x+1;
	      cc[3] = y;	
	    }
	    else if (x-1>=0 && enemy_board[x-1][y] == UNKNOWN){
	      cc[2] = x-1;
	      cc[3] = y;
	    }
	    break;
	  }
	  
	  
	  
	  
	  if (r==0 && y+1<9 && enemy_board[x][y+1] == UNKNOWN){
	    if (y+2>=9 || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)){
	      continue;
	    }
	    cc[2] = x;
	    cc[3] = y+1;
	    break;
	  }
	  if(r==1 && x-1>=0 && enemy_board[x-1][y] == UNKNOWN) {
	    if (x-2<0 || (x-2>=0 && enemy_board[x-2][y] != UNKNOWN)){
	      continue;
	    }
	    
	    cc[2] = x-1;
	    cc[3] = y;
	    break;
	  }
	  if (r==2 && y-1>=0 && enemy_board[x][y-1] == UNKNOWN){
	    if (y-2<0 || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN)){
	      continue;
	    }
	    cc[2] = x;
	    cc[3] = y-1;		
	    break;		
	  }
	  if (r==3 && x+1 <9 && enemy_board[x+1][y] == UNKNOWN){
	    if (x+2 >= 9 || (x+2<9 && enemy_board[x+2][y]!=UNKNOWN)){
	      continue;
	    }
	    cc[2] = x+1;
	    cc[3] = y;
	    break;
	  }
	  
	  
	}
	c=1;
	x = cc[2];
	y = cc[3];
	break;
      }
      else if (c==2){
	x = cc[0];
	y = cc[1];
	break;
      }
      else if (c==3){
	it_was_s(cc[0],cc[1]);
	it_was_s(cc[2],cc[3]);
	it_was_s(cc[4],cc[5]);
	enemy_board[cc[0]][cc[1]] = CSHIP;
	enemy_board[cc[2]][cc[3]] = CSHIP;
	enemy_board[cc[4]][cc[5]] = CSHIP;
	c = 0;
	continue;
      }
      else if (c == 4){
	if ((2*cc[2] == (cc[0] + cc[4])) && (2*cc[3] == (cc[1]+cc[5]))){
	  int x3,y3;
	  x3 = 2*cc[4] - cc[2];
	  y3 = 2*cc[5] - cc[3];
	  x = x3;
	  y = y3;
	  cc[0] = x3;
	  cc[1] = y3;
	  break;
	}
	else {
	  int x2,y2;
	  x2 = 2*cc[2] - cc[4];
	  y2 = 2*cc[3] - cc[5];
	  x = x2;
	  y = y2;
	  cc[0] = x2;
	  cc[1] = y2;
	  break;
	}
      }
      else if (c==5){
	it_was_s(cc[0],cc[1]);
	it_was_s(cc[2],cc[3]);
	it_was_s(cc[4],cc[5]);
	enemy_board[cc[0]][cc[1]] = CSHIP;
	enemy_board[cc[2]][cc[3]] = CSHIP;
	enemy_board[cc[4]][cc[5]] = CSHIP;
	c=0;
	continue;
      }
      
      //cship end
      
      if (d==1){
	x = dd[0];
	y = dd[1];
	break;
      }
      if (d==3){
	d=0;
	x = dd[2];
	y = dd[3];
	if (d==0){
	  while(TRUE){
	    int r;
	    r = rand()%4;
	    if (r==0 && y+1<9 && enemy_board[x][y+1] == UNKNOWN){
	      dd[0] = x;
	      dd[1] = y+1;
	      break;
	    }
	    if(r==1 && x-1>=0 && enemy_board[x-1][y] == UNKNOWN) {
	      dd[0] = x-1;
	      dd[1] = y;
	      break;
	    }
	    if (r==2 && y-1>=0 && enemy_board[x][y-1] == UNKNOWN){
	      dd[0] = x;
	      dd[1] = y-1;		
	      break;		
	    }
	    if (r==3 && x+1 <9 && enemy_board[x+1][y] == UNKNOWN){
	      dd[0] = x+1;
	      dd[1] = y;
	      break;
	    }
	  }
	  d=1;
	}	
	
	//it_was_d(dd[2],dd[3]);
	x = dd[0];
	y = dd[1];
	break;
      }
      if (d==2){
	it_was_s(dd[0],dd[1]);
	it_was_s(dd[2],dd[3]);
	enemy_board[dd[0]][dd[1]] = DSHIP;
	enemy_board[dd[2]][dd[3]] = DSHIP;
	d=0;
	continue;
      }
      
      //dship end
      if (x<0 || x>=9 || y<0 || y>=9){
	b=0;
	c=0;
	d = 0;
	c = 0;	
	x = rand() % BD_SIZE;
   	y = rand() % BD_SIZE;
      }
      
      
      if (enemy_board[x][y] == UNKNOWN){
	break;
      }
      
    }  //=====kokomade=====
  
  printf("[%s] shooting at %d%d ... ", myName, x, y);
  sprintf(shot_string, "%d%d", x, y);
  send_to_ref(shot_string);
  cur_x = x;
  cur_y = y;
}


void record_result(int x,int y,char line[])
{
  printf("\n\n\n\n");
  if(line[13]=='B')
    {
      //====kokokara====
      enemy_board[x][y] = BSHIP;
      if (b == 0){
	while (TRUE) { //fix this later
	  bb[6] = x;
	  bb[7] = y;
	  int r;
	  r = rand()%4;
	  
	  /*やってる途中、ここに最適な方向選択アルゴリズム入れること。*/



	// x,y 方向に３マスしかスペースがないとき異なる方向を決めるように。
	  if ( ( (x-1<0 || (x-1>=0 && enemy_board[x-1][y] != UNKNOWN)) && (x+3>=9 || (x+3<9 && enemy_board[x+3][y] != UNKNOWN)) ) || ( (x-2<0 || (x-2>=0 && enemy_board[x-2][y] != UNKNOWN)) && (x+2>=9 || (x+2<9 && enemy_board[x+2][y] != UNKNOWN)) ) || ( (x-3<0 || (x-3>=0 && enemy_board[x-3][y] != UNKNOWN)) && (x+1>=9 || (x+1<9 && enemy_board[x+1][y] != UNKNOWN)) ) ){
	    int rr;
	    rr = rand()%2;
	    if(rr==0 && y+1<9 && enemy_board[x][y+1] == UNKNOWN){
	      if (y+2>=9 || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)){
		continue;
	      }
	      bb[4] = x;
	      bb[5] = y+1;
	      b=1;
	      break;
	    }
	    else if (rr==1 && y-1>=0 && enemy_board[x][y-1] == UNKNOWN){
	      if (y-2<0 || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN)){
		continue;
	      }	
	      bb[4] = x;
	      bb[5] = y-1;
	      b=1;
	      break;
	    }
	    continue;
	  }
	  else if ( ( (y-1<0 || (y-1>=0 && enemy_board[x][y-1] != UNKNOWN)) && (y+3>=9 || (y+3<9 && enemy_board[x][y+3] != UNKNOWN)) ) || ( (y-2<0 || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN)) && (y+2>=9 || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)) ) || ( (y-3<0 || (y-3>=0 && enemy_board[x][y-3] != UNKNOWN)) && (y+1>=9 || (y+1<9 && enemy_board[x][y+1] != UNKNOWN)) ) ){
	    int rr;
	    rr = rand()%2;
	    if (rr==0 && x+1<9 && enemy_board[x+1][y] == UNKNOWN){
	      if (x+2>=9 || (x+2<9 && enemy_board[x+2][y] != UNKNOWN)){
		continue;
	      }
	      bb[4] = x+1;
	      bb[5] = y;
	      b=1;
	      break;
	    }
	    else if (rr==1 && x-1>=0 && enemy_board[x-1][y] == UNKNOWN){
	      if (x-2<0 || (x-2>=0 && enemy_board[x-2][y] != UNKNOWN)){
		continue;
	      }
	      bb[4] = x-1;
	      bb[5] = y;
	      b=1;
	      break;
	    }
		continue;	
	  }
	  
	  
	  
	  if(r==0 && y+1<9 && enemy_board[x][y+1] == UNKNOWN){
	    if (y+2>=9 || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)){
	      continue;
	    }
	    bb[4] = x;
	    bb[5] = y+1;
	    b=1;
	    break;
	  }
	  else if (r==1 && x+1<9 && enemy_board[x+1][y] == UNKNOWN){
	    if (x+2>=9 || (x+2<9 && enemy_board[x+2][y] != UNKNOWN)){
	      continue;
	    }
	    bb[4] = x+1;
	    bb[5] = y;
	    b=1;
	    break;
	  }
	  else if (r==2 && y-1>=0 && enemy_board[x][y-1] == UNKNOWN){
	    if (y-2<0 || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN)){
	      continue;
	    }
	    bb[4] = x;
	    bb[5] = y-1;
	    b=1;
	    break;
	  }
	  else if (r==3 && x-1>=0 && enemy_board[x-1][y] == UNKNOWN){
	    if (x-2<0 || (x-2>=0 && enemy_board[x-2][y] != UNKNOWN)){
	      continue;
	    }
	    bb[4] = x-1;
	    bb[5] = y;
	    b=1;
	    break;
	  }
	  //printf("%d %d %d %d",bb[6],bb[7],bb[4],bb[5]);
	}
	b=1;
      }
      else if (b==1){
	b=2;
	int x2,y2,x3,y3; //方向を覚える（save the direction).. fix here
	int x22,y22; // 2マス先まで読んで方向を決める
	x2 = 2*x - bb[6];
	y2 = 2*y - bb[7];
	x22 = x2 -(bb[6] - x);
	y22 = y2 - (bb[7] - y);
	x3 = 2*bb[6] - x;
	y3 = 2*bb[7] - y;
	bb[4] = x;
	bb[5] = y;
	if ( (x2<0||x2>=9||y2<0||y2>=9) || (0<=x2 && x2<9 && 0<=y2 && y2<9 && enemy_board[x2][y2] != UNKNOWN) || (x22<0||x22>=9||y22<0||y22>=9) || (0<=x22 && x22<9 && 0<=y22 && y22<9 && enemy_board[x22][y22] != UNKNOWN) ){
	  bb[2] = x3;
	  bb[3] = y3;
	}
	else {
	  bb[2] = x2;
	  bb[3] = y2;
	}
      }
      else if (b==2){
	b=3;
	int x3,y3;
	x3 = bb[2] - (bb[6] - bb[2]);
	y3 = bb[3] - (bb[7] - bb[3]);
	if((2*bb[4] == bb[2] + bb[6]) && (2*bb[5] == bb[3] + bb[7])){
	  bb[0] = bb[2] - (bb[4] - bb[2]);
	  bb[1] = bb[3] - (bb[5] - bb[3]);
	}
	else if (0<=x3 && x3<9 && 0<=y3 && y3<9 && enemy_board[x3][y3] == UNKNOWN){
	  bb[0] = x3;
	  bb[1] = y3;
	}
	else{
	  bb[0] = 2*bb[4] - bb[6];
	  bb[1] = 2*bb[5] - bb[7];
	}
      }
      else if (b==3){
	b=4;
      }
      else if (b==8){
      b=9;
      }
      else if (b ==5){
	b=6;
      }
      else if (b==6){
	b = 7;
      }
      
      //bship end
      
      //====kokomade====
    }
  else if(line[13]=='C')
    {
      //====kokokara====
      enemy_board[x][y] = CSHIP;
      if (c == 0){
	while (TRUE) {
	  cc[4] = x;
	  cc[5] = y;
	  int r;
	  r = rand()%4;
	  
	  if ( ( (x+1>=9||(x+1<9&&enemy_board[x+1][y]!=UNKNOWN)) && (x-2<0 ||(x-2>=0 && enemy_board[x-2][y] != UNKNOWN)) ) || ( (x-1<0 ||(x-1>=0 &&enemy_board[x-1][y] != UNKNOWN)) && (x+2>=9 || (x+2<9 && enemy_board[x+2][y] != UNKNOWN)) ) ){
	    if (y+1<9 && enemy_board[x][y+1] == UNKNOWN){
	      cc[2] = x;
	      cc[3] = y+1;
	    }
	    else if (y-1>=0 && enemy_board[x][y-1] == UNKNOWN){
	      cc[2] = x;
	      cc[3] = y-1;
	    }
	    break;
	  }
	  else if ( ( (y+1>=9 || (y+1<9 && enemy_board[x][y+1] != UNKNOWN)) && (y-2<0 || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN)) ) || ( (y+2>=9 || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)) && (y-1<0 || (y-1>=0 &&enemy_board[x][y-1] != UNKNOWN)) ) ){
	    if (x+1<9 && enemy_board[x+1][y] == UNKNOWN){
	      cc[2] = x+1;
	      cc[3] = y;	
	    }
	    else if (x-1>=0 && enemy_board[x-1][y] == UNKNOWN){
	      cc[2] = x-1;
	      cc[3] = y;
	    }
	    break;
	  }
	  
	  if ((x+1 >= 9 || (x+1<9 && enemy_board[x+1][y]!=UNKNOWN))&& (x-1<0 ||(x-1>=0 &&enemy_board[x-1][y] != UNKNOWN)) && (y+2>=9 || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)) && (y-2<0 || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN))){
	    if (y+1<9 && enemy_board[x][y+1] == UNKNOWN){
	      cc[2] = x;
	      cc[3] = y+1;
	    }
	    else if (y-1>=0 && enemy_board[x][y-1] == UNKNOWN){
	      cc[2] = x;
	      cc[3] = y-1;
	    }
	    break;	
	  }
	  if ((y+1>=9 || (y+1<9 && enemy_board[x][y+1] != UNKNOWN)) && (y-1<0 || (y-1>=0 && enemy_board[x][y-1] != UNKNOWN)) && (x+2>=9 || (x+2<9 && enemy_board[x+2][y] != UNKNOWN)) && (x-2<0 ||(x-2>=0 && enemy_board[x-2][y] != UNKNOWN))){
	    if (x+1<9 && enemy_board[x+1][y] == UNKNOWN){
	      cc[2] = x+1;
	      cc[3] = y;	
	    }
	    else if (x-1>=0 && enemy_board[x-1][y] == UNKNOWN){
	      cc[2] = x-1;
	      cc[3] = y;
	    }
	    break;
	  }
	  
	  
	  else if (((x+1>=9||(x+1<9&&enemy_board[x+1][y]!=UNKNOWN)) && (x+2>=9||(x+2<9&&enemy_board[x+2][y]!=UNKNOWN)) && (y+2>=9 || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)) && (x-2<0 ||(x-2>=0 && enemy_board[x-2][y] != UNKNOWN)) && (y-2<0 || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN)))||((x-1<0 || (x-1>=0 && enemy_board[x-1][y] != UNKNOWN)) &&(x-2<0 ||(x-2>=0 && enemy_board[x-2][y] != UNKNOWN)) && (y+2>=9 || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)) && (x+2>=9 ||(x+2<9 && enemy_board[x+2][y] != UNKNOWN)) && (y-2<0 || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN)))){
	    if (y+1<9 && enemy_board[x][y+1] == UNKNOWN){
	      cc[2] = x;
	      cc[3] = y+1;
	    }
	    else if (y-1>=0 && enemy_board[x][y-1] == UNKNOWN){
	      cc[2] = x;
	      cc[3] = y-1;
	    }
	    break; 
	  }
	  else if ((y+2>=9 || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)) && (x-2<0 ||(x-2>=0 && enemy_board[x-2][y] != UNKNOWN)) && (y-2<0 || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN)) && (x+2>=9||(x+2<9&&enemy_board[x+2][y]!=UNKNOWN))){
	    if (x+1<9 && enemy_board[x+1][y] == UNKNOWN){
	      cc[2] = x+1;
	      cc[3] = y;	
	    }
	    else if (x-1>=0 && enemy_board[x-1][y] == UNKNOWN){
	      cc[2] = x-1;
	      cc[3] = y;
	    }
	    break;
	  }
	  else if (((x+1>=9 || (x+1<9 && enemy_board[x+1][y] != UNKNOWN)) && (y+2>=9 || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)) && (x-2<0 ||(x-2>=0 && enemy_board[x-2][y] != UNKNOWN)) && (y-2<0 || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN)))||((x-1<0 || (x-1>=0 && enemy_board[x-1][y] != UNKNOWN)) && (y+2>=9 || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)) && (x+2>=9 ||(x+2<9 && enemy_board[x+2][y] != UNKNOWN)) && (y-2<0 || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN)))){
	    if (y+1<9 && enemy_board[x][y+1] == UNKNOWN){
	      cc[2] = x;
	      cc[3] = y+1;
	    }
	    else if (y-1>=0 && enemy_board[x][y-1] == UNKNOWN){
	      cc[2] = x;
	      cc[3] = y-1;
	    }
	    break;
	  }
	  else if (( (y+1>=9 || (y+1<9 && enemy_board[x][y+1] != UNKNOWN)) && (x+2>=9 || (x+2<9 && enemy_board[x+2][y] != UNKNOWN)) && (x-2<0 ||(x-2>=0 && enemy_board[x-2][y] != UNKNOWN)) && (y-2<0 || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN)) ) || ( (y-1<0||(y-1>=0 && enemy_board[x][y-1] != UNKNOWN)) && (y+2>=9 || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)) && (x-2<0 ||(x-2>=0 && enemy_board[x-2][y] != UNKNOWN)) && (x+2>=9 || (x+2<9 && enemy_board[x+2][y] != UNKNOWN)))){
	    if (x+1<9 && enemy_board[x+1][y] == UNKNOWN){
	      cc[2] = x+1;
	      cc[3] = y;	
	    }
	    else if (x-1>=0 && enemy_board[x-1][y] == UNKNOWN){
	      cc[2] = x-1;
	      cc[3] = y;
	    }
	    break;
	  }
	  
	  
	  
	  if (r==0 && y+1<9 && enemy_board[x][y+1] == UNKNOWN){
	    if ((y+2>=9) || (y+2<9 && enemy_board[x][y+2] != UNKNOWN)){
	      continue;
	    }
	    cc[2] = x;
	    cc[3] = y+1;
	    c = 1;
	    break;
	  }
	  if (r==1 && x-1>=0 && enemy_board[x-1][y] == UNKNOWN){
	    if ((x-2<0) || (x-2>=0 && enemy_board[x-2][y] != UNKNOWN)){
	      //printf("if is working1\n");
	      continue;
	    }
	    cc[2] = x-1;
	    cc[3] = y;
	    c = 1;
	    //printf("continue is not working ... \n");
	    break;
	  }
	  if (r==2 && y-1>=0 && enemy_board[x][y-1] == UNKNOWN){
	    if ((y-2<0) || (y-2>=0 && enemy_board[x][y-2] != UNKNOWN)){
	      continue;
	    }
	    cc[2] = x;
	    cc[3] = y-1;
	    c = 1;
	    break;
	  }
	  if (r==3 && x+1<9 && enemy_board[x+1][y] == UNKNOWN){
	    if (x+2>=9 || (x+2<9 && enemy_board[x+2][y] != UNKNOWN)){
	      continue;
	    }
	    cc[2] = x+1;
	    cc[3] = y;
	    c = 1;
	    break;       //ランダムに決めてc=1で次に！
	  }
	}
	c = 1;
      }
      else if (c==1){
	c=2;
	int x2,x3,y2,y3;
	x2 = 2*x - cc[4];
	y2 = 2*y - cc[5];
	x3 = 2*cc[4] - cc[2];
	y3 = 2*cc[5] - cc[3];
	cc[2] = x;
	cc[3] = y;
	if (0<=x2 && x2<9 && 0<=y2 && y2<9 && enemy_board[x2][y2]==UNKNOWN){ //順方向
	  cc[0] = x2;
	  cc[1] = y2;  
	}
	else if  (0<=x3 && x3<9 && 0<=y3 && y3<9 && enemy_board[x3][y3] == UNKNOWN){ //逆方向
	  cc[0] = x3;
	  cc[1] = y3;
	}
      }
      else if (c==2) c=3;
      else if (c==4) c=5;
      
      
      
      //====kokomade====
    }
  else if(line[13]=='D')
    {
      //====kokokara====
      enemy_board[x][y] = DSHIP;
      if (d==1) d=2;
      if (d==0){
	while (TRUE) {
	  dd[2] = x;
	  dd[3] = y;
	  int r;
	  r = rand()%4;
	  if (r==0 && y+1<9 && enemy_board[x][y+1] == UNKNOWN){
	    dd[0] = x;
	    dd[1] = y+1;
	    d=1;
	    break;
	  }
	  if(r==1 && x-1>=0 && enemy_board[x-1][y] == UNKNOWN) {
	    dd[0] = x-1;
	    dd[1] = y;
	    d=1;
	    break;
	  }
	  if (r==2 && y-1>=0 && enemy_board[x][y-1] == UNKNOWN){
	    dd[0] = x;
	    dd[1] = y-1;		
	    d=1;
	    break;		
	  }
	  if (r==3 && x+1 <9 && enemy_board[x+1][y] == UNKNOWN){
	    dd[0] = x+1;
	    dd[1] = y;
	    d=1;
	    break;
	  }
	}
      }	
      //====kokomade====
    }
  else if(line[13]=='S')
    {
      //====kokokara====
      enemy_board[x][y] = SSHIP;
      it_was_s(x,y);
      
      //====kokomade====
    }
  else if(line[13]=='R')
    {
      //====kokokara====
      enemy_board[x][y] = ROCK;
      
      //====kokomade====
    }
  else
    {
      //====kokokara====
      enemy_board[x][y] = NOSHIP;
      if (b==1){
	b=10;
      }
      else if (b==3){
	b = 8;
      }
      else if (b==2){
	b=5;
      }
      
      //bship end
      
      if (c==1){
	c = 10;
      }
      else if (c==2){
	c = 4;
      }
      
      //cship end
      
      if (d==1){
	d=3;
      }
      //dship end
      if (x<0 || x>=9 || y<0 || y>=9){
	b=0;
	c=0;
	d = 0;
	c = 0;	
      }
      
      
      //====kokomade====
    }
}

void print_board(void){
  int ix, iy;
  
  for (iy = BD_SIZE - 1; iy >= 0; iy--)
    {
      printf("%2d ", iy);
      for (ix = 0; ix < BD_SIZE; ix++)
	{
	  switch(enemy_board[ix][iy])
	    {
	    case UNKNOWN:
	      printf("U ");
	      break;
	    case NOSHIP:
	      printf("N ");
	      break;
	    case ROCK:
	      printf("R ");
	      break;
	    case BSHIP:
	      printf("B ");
	      break;
	    case CSHIP:
	      printf("C ");
	      break;
	    case DSHIP:
	      printf("D ");
	      break;
	    case SSHIP:
	      printf("S ");
	      break;
	    default:
	      break;
	    }
	}
      printf("\n");
    }
  
  printf("  ");
  for (ix = 0; ix < BD_SIZE; ix++)
    {
      printf("%2d", ix);
    }
  printf("\n\n");
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
	  record_result(cur_x,cur_y,line);
	  printf("[%s] result: %c\n", myName, line[13]);
	  print_board();
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
