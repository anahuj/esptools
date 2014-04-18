


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>

// #include "mylib/filesdirs.h"

char tmps[1024];
chtype tmpchs[1024];
chtype chcursor[16];

int main(int ac, char **av)
{
  int i;
  int key;
  int r,rr,rrr;
  int x,y;
  int xold,yold;
  int xsave,ysave;

#if 0
  for (i = 0; i < strlen(av[1]); i++) {
    tmpchs[i] = (av[1])[i];
  }
  tmpchs[strlen(av[1])] = 0;
#endif
  
  initscr();
  cbreak();
  noecho();
  nonl();
  intrflush(stdscr, FALSE);
  keypad(stdscr, TRUE);
  nodelay(stdscr, FALSE);

#if 0
  r = addchstr(tmpchs);
#endif

  refresh();

  chcursor[0] = 'x';
  chcursor[1] = 0;

  x = 0;
  y = 0;

  while ((key = getch()) != (int)'q') {
    xold = x;
    yold = y;
    if (key == KEY_UP) y--;
    if (key == KEY_DOWN) y++;
    if (key == KEY_LEFT) x--;
    if (key == KEY_RIGHT) x++;

    if ((x != xold) || (y != yold)) {
      r = move(y,x);
      if (r != ERR) {
	rr = addchstr(chcursor);

#if 0
	// Print status line.
	getyx(stdscr,ysave,xsave);
	move(0,0);
	sprintf(tmps,"x = %3i y = %3i rr = %i",x,y,rr);
	for (i = 0; i < strlen(tmps); i++) {
	  tmpchs[i] = (tmps)[i];
	}
	tmpchs[strlen(tmps)] = 0;
	rrr = addchstr(tmpchs);
	move(ysave,xsave);
#endif

	refresh();
      } else {
	x = xold;
	y = yold;
	r = move(y,x);
      }
    }
  }

  endwin();

  return 1;
}

