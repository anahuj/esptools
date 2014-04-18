


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>

#include "mylib/filesdirs.h"
#include "mylib/mmapfile.h"
#include "mylib/buffer.h"


// Tree graph.

// File format --> Imported file

// Compound item which can be defined interactively. Perhaps
// by example.


typedef struct {
  char *type;
  void *next;
  void *prev;
  void *children;
  void *parent;
  // int loc; // Attributes.
  // int size; // Attributes.
  void *attributes;
  void *data;
} ty_item;

typedef struct {
  char *type;
  void *next;
  int loc;
} ty_attr_loc;

typedef struct {
  char *type;
  void *next;
  int size;
} ty_attr_size;

typedef struct {
  char *type;
  void *next;
  char *varname;
} ty_attr_varname;

typedef struct {
  char *type;
  void *next;
  char *varname;
} ty_attr_comment;

// Used for buffering.
typedef struct {
  char *type;
  int buffersize;
} ty_data_fixedbuffer;

typedef struct {
  char *type;
  int value;
} ty_data_basicint;

typedef struct {
  char *type;
  float value;
} ty_data_float;

typedef struct {
  char *type;
  char *s;
} ty_data_string;



#if 0

typedef struct {
  char *type;
  void *next;
  void *prev;
  void *children;
  void *parent;
  // int loc; // Attributes.
  // int size; // Attributes.
  void *attributes;
  void *data;
} ty_;

#endif

typedef struct {
  int loc;
  char *type; // "unknown" "int" "float" etc.
  int size;
  char *name;
} ty_entry;

ty_entry *list[10000];

int numlist;
int pickindex;
int printoffset;

void *b;

char tmps[1024];
char tmps2[1024];
chtype tmpchs[1024];
chtype chcursor[16];

#define C_INPUTLINE_SIZE 1024
char inputline[C_INPUTLINE_SIZE];
chtype inputlinech[C_INPUTLINE_SIZE];
int numinputline;
int textinputmode;

int xscreensize;
int yscreensize;
int cursorx;


void delete_entry(ty_entry *p)
{
  free(p->type);
  free(p->name);
  free(p);
}

ty_entry *create_new(int loc, char *s, int size, char *name)
{
  ty_entry *p;

  p = (ty_entry *)malloc(sizeof(ty_entry));
  p->loc = loc;
  p->type = strdup(s);
  p->size = size;
  if (name == NULL) {
    p->name = NULL;
  } else {
    p->name = strdup(name);
  }

  return p;
}

ty_entry *create_unknown(int loc, int size)
{
  ty_entry *p;

  p = (ty_entry *)malloc(sizeof(ty_entry));
  p->loc = loc;
  p->type = strdup("unknown");
  p->size = size;
  p->name = NULL;

  return p;
}

ty_entry *create_char(int loc)
{
  ty_entry *p;

  p = (ty_entry *)malloc(sizeof(ty_entry));
  p->loc = loc;
  p->type = strdup("char");
  p->size = 1;
  p->name = NULL;

  return p;
}

ty_entry *create_arrayofchars(int loc, int size)
{
  ty_entry *p;

  p = (ty_entry *)malloc(sizeof(ty_entry));
  p->loc = loc;
  p->type = strdup("arrayofchars");
  p->size = size;
  p->name = NULL;

  return p;
}

ty_entry *create_byte(int loc)
{
  ty_entry *p;

  p = (ty_entry *)malloc(sizeof(ty_entry));
  p->loc = loc;
  p->type = strdup("byte");
  p->size = 1;
  p->name = NULL;

  return p;
}

ty_entry *create_ubyte(int loc)
{
  ty_entry *p;

  p = (ty_entry *)malloc(sizeof(ty_entry));
  p->loc = loc;
  p->type = strdup("ubyte");
  p->size = 1;
  p->name = NULL;

  return p;
}

ty_entry *create_short(int loc)
{
  ty_entry *p;

  p = (ty_entry *)malloc(sizeof(ty_entry));
  p->loc = loc;
  p->type = strdup("short");
  p->size = 2;
  p->name = NULL;

  return p;
}

ty_entry *create_ushort(int loc)
{
  ty_entry *p;

  p = (ty_entry *)malloc(sizeof(ty_entry));
  p->loc = loc;
  p->type = strdup("ushort");
  p->size = 2;
  p->name = NULL;

  return p;
}

ty_entry *create_int(int loc)
{
  ty_entry *p;

  p = (ty_entry *)malloc(sizeof(ty_entry));
  p->loc = loc;
  p->type = strdup("int");
  p->size = 4;
  p->name = NULL;

  return p;
}

// p = create_item_int();
// item_set_attribute_loc(p,loc);
ty_item *create_item_int(int loc)
{
  ty_entry *p;

  p = (ty_entry *)malloc(sizeof(ty_entry));
  p->loc = loc;
  p->type = strdup("int");
  p->size = 4;
  p->name = NULL;

  return p;
}

ty_entry *create_uint(int loc)
{
  ty_entry *p;

  p = (ty_entry *)malloc(sizeof(ty_entry));
  p->loc = loc;
  p->type = strdup("uint");
  p->size = 4;
  p->name = NULL;

  return p;
}

ty_entry *create_float(int loc)
{
  ty_entry *p;

  p = (ty_entry *)malloc(sizeof(ty_entry));
  p->loc = loc;
  p->type = strdup("float");
  p->size = 4;
  p->name = NULL;

  return p;
}

ty_entry *create_hexdump(int loc, int size)
{
  ty_entry *p;

  p = (ty_entry *)malloc(sizeof(ty_entry));
  p->loc = loc;
  p->type = strdup("hexdump");
  p->size = size;
  p->name = NULL;

  return p;
}

void insertentry(ty_entry *p)
{
  int i;

  for (i = numlist; i > pickindex; i--) {
    list[i] = list[i-1];
  }
  list[pickindex] = p;
  numlist++;
  pickindex++;
}

void insertentry_stayatitem(ty_entry *p)
{
  int i;

  for (i = numlist; i > pickindex; i--) {
    list[i] = list[i-1];
  }
  list[pickindex] = p;
  numlist++;
  // pickindex++;
}

void insertentry_after(ty_entry *p)
{
  int i;

  for (i = numlist; i > pickindex + 1; i--) {
    list[i] = list[i-1];
  }
  list[pickindex + 1] = p;
  numlist++;
  // pickindex++;
}

void print_tmps()
{
  int i;
  int rr;

  for (i = 0; i < strlen(tmps); i++) {
    tmpchs[i] = tmps[i];
  }
  tmpchs[strlen(tmps)] = 0;
  rr = addchstr(tmpchs);
}

void print_inputline()
{
  int i;
  int rr;

  if (textinputmode == 1) {
    for (i = 0; i < strlen(inputline); i++) {
      inputlinech[i] = inputline[i];
    }
    inputlinech[strlen(inputline)] = 0;
    rr = addchstr(inputlinech);
  }
}

char global_printhexdump_hexes[1024];
char global_printhexdump_chars[1024];

void printlist_print()
{
  ty_entry *p;
  int i;
  int k;
  int y;
  int done;
  int r,rr;
  char *s2;
  int n;
  int kk;

  y = 0;
  k = printoffset;
  done = 0;
  do {
    if (k < numlist) { 
      r = move(y,0);
      if (r != ERR) {
	p = list[k];
	if (strcmp(p->type,"unknown") == 0) {
	  buffer_setloc(b,p->loc);
	  sprintf(tmps,"unknown %i bytes",p->size);
	} else if (strcmp(p->type,"char") == 0) {
	  buffer_setloc(b,p->loc);
	  sprintf(tmps,"char %c",buffer_read_char(b));
	} else if (strcmp(p->type,"arrayofchars") == 0) {
	  buffer_setloc(b,p->loc);
	  s2 = buffer_read_nstring(b,p->size);
	  sprintf(tmps,"arrayofchars %s",s2);
	  free(s2);
	} else if (strcmp(p->type,"byte") == 0) {
	  buffer_setloc(b,p->loc);
	  sprintf(tmps,"byte %i",buffer_read_byte(b));
	} else if (strcmp(p->type,"ubyte") == 0) {
	  buffer_setloc(b,p->loc);
	  sprintf(tmps,"ubyte %u",buffer_read_ubyte(b));
	} else if (strcmp(p->type,"short") == 0) {
	  buffer_setloc(b,p->loc);
	  sprintf(tmps,"short %i",buffer_read_short(b));
	} else if (strcmp(p->type,"ushort") == 0) {
	  buffer_setloc(b,p->loc);
	  sprintf(tmps,"ushort %u",buffer_read_ushort(b));
	} else if (strcmp(p->type,"int") == 0) {
	  buffer_setloc(b,p->loc);
	  sprintf(tmps,"int %i",buffer_read_int(b));
	} else if (strcmp(p->type,"uint") == 0) {
	  buffer_setloc(b,p->loc);
	  sprintf(tmps,"uint %u",buffer_read_uint(b));
	} else if (strcmp(p->type,"float") == 0) {
	  buffer_setloc(b,p->loc);
	  sprintf(tmps,"float %f",buffer_read_float(b));
	} else if (strcmp(p->type,"hexdump") == 0) {
	  buffer_setloc(b,p->loc);
	  kk = 0;
	  global_printhexdump_hexes[0] = '\0';
	  for (i = 0; i < p->size; i++) {
	    n = buffer_read_ubyte(b);
	    sprintf(tmps2," %2x",n);
	    strcat(global_printhexdump_hexes,tmps2);
	    if ((n >= 32) && (n <= 126)) {
	      global_printhexdump_chars[kk] = (char)n;
	    } else {
	      global_printhexdump_chars[kk] = '.';
	    }
	    kk++;
	  }
	  global_printhexdump_chars[kk] = '\0';
	  sprintf(tmps,"hexdump %s  %s",global_printhexdump_hexes,global_printhexdump_chars);
	} else {
	  sprintf(tmps,"Type unknown");
	}

#if 0
	// Add location and name.
	if (p->name != NULL) {
	  sprintf(tmps2,"  %i \"%s\"",p->loc,p->name);
	} else {
	  sprintf(tmps2,"  %i",p->loc);
	}
	strcat(tmps,tmps2);
#else
	// Add name.
	if (p->name != NULL) {
	  sprintf(tmps2,"  \"%s\"",p->name);
	  strcat(tmps,tmps2);
	}
#endif


	for (i = 0; i < strlen(tmps); i++) {
	  tmpchs[i] = (tmps)[i];
	}
	tmpchs[strlen(tmps)] = 0;
	rr = addchstr(tmpchs);
	y++; // One line was printed.
	k++; // One entry was printed.
      } else {
	done = 1;
      }
    } else {
      done = 1;
    }
  } while (done == 0);

#if 0
  r = move(pickindex-printoffset,0);
  if (r == ERR) {
    // printoffset++;
    // XXXX we should call printlist() here!!
    // XXXX Perhaps we should maintain the window size in variables.
  }

  refresh();
#endif
}

void printlist()
{
  ty_entry *p;
  int i;
  int k;
  int y;
  int done;
  int r,rr;
  int h,v;

  getmaxyx(stdscr,yscreensize,xscreensize);

  // erase();
  clear();

  // Test cursor position.
  r = move(pickindex-printoffset,0);
  if (r == ERR) {
    if (pickindex-printoffset < 0) {
      // printoffset = pickindex;
      // printoffset = printoffset - (pickindex-printoffset)/2;
      printoffset = printoffset - yscreensize/2;
      if (printoffset < 0) printoffset = 0;
    } else {
      // printoffset = printoffset + (pickindex-printoffset)/2;
      printoffset = printoffset + yscreensize/2;
    }
  }



  // Debug lines.
  h = 60;
  move(0,h); sprintf(tmps,"Debug:"); print_tmps();
  move(1,h+2);
  sprintf(tmps,"printoffset %i pickindex %i",printoffset,pickindex);
  print_tmps();
  move(2,h+2);
  sprintf(tmps,"item location %i size %i",list[pickindex]->loc,list[pickindex]->size);
  print_tmps();

  // Help.
  v = 7;
  move(v,h); sprintf(tmps,"Help:"); print_tmps();
  v++;
  move(v,h+2); sprintf(tmps,"q = quit"); print_tmps();
  v++;
  move(v,h+2); sprintf(tmps,"up = move up in the list"); print_tmps();
  v++;
  move(v,h+2); sprintf(tmps,"down = move down in the list"); print_tmps();
  v++;

  move(v,h+2); sprintf(tmps,"c = insert char"); print_tmps();
  v++;
  move(v,h+2); sprintf(tmps,"a = insert arrayofchars"); print_tmps();
  v++;
  move(v,h+4); sprintf(tmps,"+ = increase length of arrayofchars"); print_tmps();
  v++;
  move(v,h+4); sprintf(tmps,"- = decrease length of arrayofchars"); print_tmps();
  v++;
  move(v,h+2); sprintf(tmps,"r = insert byte"); print_tmps();
  v++;
  move(v,h+2); sprintf(tmps,"4 = insert ubyte"); print_tmps();
  v++;
  move(v,h+2); sprintf(tmps,"t = insert short"); print_tmps();
  v++;
  move(v,h+2); sprintf(tmps,"5 = insert ushort"); print_tmps();
  v++;
  move(v,h+2); sprintf(tmps,"y = insert int = i"); print_tmps();
  v++;
  move(v,h+2); sprintf(tmps,"6 = insert uint"); print_tmps();
  v++;
  move(v,h+2); sprintf(tmps,"f = insert float"); print_tmps();
  v++;
  move(v,h+2); sprintf(tmps,"h = insert hexdump (12 bytes or less)"); print_tmps();
  v++;
  move(v,h+4); sprintf(tmps,"left = move left on the hexdump line"); print_tmps();
  v++;
  move(v,h+4); sprintf(tmps,"right = move right on the hexdump line"); print_tmps();
  v++;
  move(v,h+4); sprintf(tmps,"enter = split the hexdump line to two lines"); print_tmps();
  v++;
  move(v,h+4); sprintf(tmps,"m = merge two hexdumps"); print_tmps();
  v++;
  move(v,h+4); sprintf(tmps,"a = change hexdump to arrayofchars"); print_tmps();
  v++;
  move(v,h+2); sprintf(tmps,"u = change item to unknown"); print_tmps();
  v++;
  move(v,h+4); sprintf(tmps,"m = merge two unknowns"); print_tmps();
  v++;
  move(v,h+2); sprintf(tmps,"p = type name in the inputline (at bottom)"); print_tmps();
  v++;
  move(v,h+2); sprintf(tmps,"w = save to \"savefile\""); print_tmps();
  v++;
  move(v,h+2); sprintf(tmps,"2 = load from \"savefile\""); print_tmps();


  // Print inputline.
  v += 2;
  move(v,h);
  print_inputline();

  printlist_print();

  r = move(pickindex-printoffset,cursorx);
  if (r == ERR) {
    // printoffset++;
    // XXXX we should call printlist() here!!
    // XXXX Perhaps we should maintain the window size in variables.
  }

  refresh();
}


int main(int ac, char **av)
{
  FILE *fp;
  void *m;
  // void *b;
  unsigned char *buffer;
  int buflen;
  int i,n;
  int key;
  int r,rr,rrr;
  int x,y;
  int xold,yold;
  int xsave,ysave;
  ty_entry *newentry;
  ty_entry *pickentry;
  int loc;
  int newsize;
  int hexdumpposition;
  int ishexdump1,ishexdump2;
  int done;

#if 0
  for (i = 0; i < strlen(av[1]); i++) {
    tmpchs[i] = (av[1])[i];
  }
  tmpchs[strlen(av[1])] = 0;
#endif

  if (ac < 1) {
    fprintf(stderr,"Usage: decoder <file>\n");
    exit(-1);
  }

  m = mmapfile_open_r(av[1]);
  buffer = mmapfile_getbuf(m);
  buflen = mmapfile_getsize(m);

  b = buffer_new(buffer,buflen);

  numlist = 0;
  pickindex = 0;
  printoffset = 0;
  cursorx = 0;


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

  list[numlist] = create_unknown(buffer_getloc(b),buffer_getlen(b));
  // list[numlist] = strdup("unknown");
  numlist++;
  printlist();

  hexdumpposition = 0;

  x = 0;
  y = 0;

  textinputmode = 0;
  numinputline = 0;
  inputline[numinputline] = '\0';

  done = 0;
  // while ((key = getch()) != (int)'q') {
  while (done == 0) {

    key = getch();

    // XXXX mode % 0 decoder 1 text input 2 list selector
    // List selector is used for selecting variable names, subblock names.

    if ((textinputmode == 1) && (key == 13)) {
      textinputmode = 0;
      pickentry = list[pickindex];
      if (pickentry->name != NULL) {
	free(pickentry->name);
      }
      pickentry->name = strdup(inputline);
      numinputline = 0;
      inputline[numinputline] = '\0';
      printlist();
    }

    if (textinputmode == 1) {
      if (key == KEY_BACKSPACE) {
	if (numinputline > 0) {
	  numinputline--;
	  inputline[numinputline] = '\0';
	}
      } else {
	if (numinputline < C_INPUTLINE_SIZE-1) {
	  inputline[numinputline] = key;
	  numinputline++;
	  inputline[numinputline] = '\0';
	}
      }
      key = -key;
      printlist();
    }

    if (key == (int)'p') {
      textinputmode = 1;
      printlist();
    }

    if (key == (int)'q') {
      done = 1;
    }

    // Move between items.
    // pickindex = 0 at start.
    if (key == KEY_UP) {
      ishexdump1 = strcmp(list[pickindex]->type,"hexdump");
      if (pickindex > 0) pickindex--;
      ishexdump2 = strcmp(list[pickindex]->type,"hexdump");
      if ((ishexdump1 == 0) && (ishexdump2 == 0)) {
	// Do nothing.
      } else {
	// hexdumpposition = 0; // Change 20100501.
	cursorx = 0;
      }
      // Change 20100501.
      if (ishexdump2 == 0) {
	cursorx = 0;
	if (hexdumpposition > 0) {
	  n = hexdumpposition;
	  // If a hexdump line is shorter than other hexdump lines.
	  if (n > list[pickindex]->size) n = list[pickindex]->size;
	  cursorx = 8 + n*3;
	}
      }
      printlist();
    }

    if (key == KEY_DOWN) {
      ishexdump1 = strcmp(list[pickindex]->type,"hexdump");
      if (pickindex < numlist-1) pickindex++;
      ishexdump2 = strcmp(list[pickindex]->type,"hexdump");
      if ((ishexdump1 == 0) && (ishexdump2 == 0)) {
	// Do nothing.
      } else {
	// hexdumpposition = 0; // Change 20100501.
	cursorx = 0;
      }
      // Change 20100501.
      if (ishexdump2 == 0) {
	cursorx = 0;
	if (hexdumpposition > 0) {
	  n = hexdumpposition;
	  // If a hexdump line is shorter than other hexdump lines.
	  if (n > list[pickindex]->size) n = list[pickindex]->size;
	  cursorx = 8 + n*3;
	}
      }
      printlist();
    }

    if (key == KEY_PPAGE) {
      getmaxyx(stdscr,yscreensize,xscreensize);
      ishexdump1 = strcmp(list[pickindex]->type,"hexdump");

      // if (pickindex - yscreensize/2 >= 0) pickindex -= yscreensize/2;
      pickindex -= yscreensize/2;
      if (pickindex < 0) pickindex = 0;

      ishexdump2 = strcmp(list[pickindex]->type,"hexdump");
      if ((ishexdump1 == 0) && (ishexdump2 == 0)) {
	// Do nothing.
      } else {
	// hexdumpposition = 0; // Change 20100501.
	cursorx = 0;
      }
      // Change 20100501.
      if (ishexdump2 == 0) {
	cursorx = 0;
	if (hexdumpposition > 0) {
	  n = hexdumpposition;
	  // If a hexdump line is shorter than other hexdump lines.
	  if (n > list[pickindex]->size) n = list[pickindex]->size;
	  cursorx = 8 + n*3;
	}
      }
      printlist();
    }

    if (key == KEY_NPAGE) {
      getmaxyx(stdscr,yscreensize,xscreensize);
      ishexdump1 = strcmp(list[pickindex]->type,"hexdump");

      // if (pickindex + yscreensize/2 <= numlist-1) pickindex += yscreensize/2;
      pickindex += yscreensize/2;
      // XXXX assumes that a list entry is onw row
      if (pickindex > numlist-1) pickindex = numlist-1;

      ishexdump2 = strcmp(list[pickindex]->type,"hexdump");
      if ((ishexdump1 == 0) && (ishexdump2 == 0)) {
	// Do nothing.
      } else {
	// hexdumpposition = 0; // Change 20100501.
	cursorx = 0;
      }
      // Change 20100501.
      if (ishexdump2 == 0) {
	cursorx = 0;
	if (hexdumpposition > 0) {
	  n = hexdumpposition;
	  // If a hexdump line is shorter than other hexdump lines.
	  if (n > list[pickindex]->size) n = list[pickindex]->size;
	  cursorx = 8 + n*3;
	}
      }
      printlist();
    }



    // Add char.
    // New entry is added if the pick point has unknown entry
    // and if it is large enough.
    // Unknown entry is split and the tail is left as unknown.
    if (key == (int)'c') {
      pickentry = list[pickindex];
      if (strcmp(pickentry->type,"unknown") == 0) {
	if (pickentry->size >= 1) {
	  loc = pickentry->loc;
	  newentry = create_char(loc);
	  pickentry->loc += 1;
	  pickentry->size -= 1;
	  if (pickentry->size > 0) {
	    insertentry(newentry);
	  } else {
	    delete_entry(pickentry);
	    list[pickindex] = newentry;
	  }
	  printlist();
	}
      }
    }

    // Array of chars. Resizeable.
    // Change hexdump to arrayofchars.
    if (key == (int)'a') {
      pickentry = list[pickindex];
      if (strcmp(pickentry->type,"unknown") == 0) {
	if (pickentry->size >= 1) {
	  loc = pickentry->loc;
	  newentry = create_arrayofchars(loc,1);
	  pickentry->loc += 1;
	  pickentry->size -= 1;
	  if (pickentry->size > 0) {
	    insertentry_stayatitem(newentry);
	  } else {
	    delete_entry(pickentry);
	    list[pickindex] = newentry;
	  }
	  printlist();
	}
      } else if (strcmp(pickentry->type,"hexdump") == 0) {
	if (pickentry->size >= 1) {
	  newentry = create_arrayofchars(pickentry->loc,pickentry->size);
	  delete_entry(pickentry);
	  list[pickindex] = newentry;
	  cursorx = 0; // We could calculate equivalent location in arrayofchars.
	  printlist();
	}
      }
    }

    if (key == (int)'+') {
      pickentry = list[pickindex];
      if (strcmp(pickentry->type,"arrayofchars") == 0) {
	if (pickindex < numlist - 1) {
	  if (strcmp(list[pickindex+1]->type,"unknown") == 0) {
	    if (list[pickindex+1]->size > 1) {
	      pickentry->size++;
	      list[pickindex+1]->loc++;
	      list[pickindex+1]->size--;
	    } else {
	      pickentry->size++;
	      // Delete the unknown.
	      delete_entry(list[pickindex+1]);
	      for (i = pickindex + 1; i < numlist - 1; i++) {
		list[i] = list[i+1];
	      }
	      numlist--;
	    }
	    printlist();
	  }
	}
      }
    }

    if (key == (int)'-') {
      pickentry = list[pickindex];
      if (strcmp(pickentry->type,"arrayofchars") == 0) {
	if (pickentry->size > 1) {
	  if (pickindex < numlist - 1) {
	    if (strcmp(list[pickindex+1]->type,"unknown") == 0) {
	      pickentry->size--;
	      list[pickindex+1]->loc--;
	      list[pickindex+1]->size++;
	      printlist();
	    } else {
	      // Create unknown.
	      loc = pickentry->loc + pickentry->size - 1;
	      newentry = create_unknown(loc,1);
	      insertentry_after(newentry);
	      // Decrease arrayofchars.
	      pickentry->size--;
	      printlist();
	    }
	  } else {
	    // pickindex == numlist - 1
	    // Create unknown.
	    loc = pickentry->loc + pickentry->size - 1;
	    newentry = create_unknown(loc,1);
	    insertentry_after(newentry);
	    // Decrease arrayofchars.
	    pickentry->size--;
	    printlist();
	  }
	}
      }
    }

    // Add byte.
    if (key == (int)'r') {
      pickentry = list[pickindex];
      if (strcmp(pickentry->type,"unknown") == 0) {
	if (pickentry->size >= 1) {
	  loc = pickentry->loc;
	  newentry = create_byte(loc);
	  pickentry->loc += 1;
	  pickentry->size -= 1;
	  if (pickentry->size > 0) {
	    insertentry(newentry);
	  } else {
	    delete_entry(pickentry);
	    list[pickindex] = newentry;
	  }
	  printlist();
	}
      }
    }

    // Add ubyte.
    if (key == (int)'4') {
      pickentry = list[pickindex];
      if (strcmp(pickentry->type,"unknown") == 0) {
	if (pickentry->size >= 1) {
	  loc = pickentry->loc;
	  newentry = create_ubyte(loc);
	  pickentry->loc += 1;
	  pickentry->size -= 1;
	  if (pickentry->size > 0) {
	    insertentry(newentry);
	  } else {
	    delete_entry(pickentry);
	    list[pickindex] = newentry;
	  }
	  printlist();
	}
      }
    }

    // Add short.
    if (key == (int)'t') {
      pickentry = list[pickindex];
      if (strcmp(pickentry->type,"unknown") == 0) {
	if (pickentry->size >= 2) {
	  loc = pickentry->loc;
	  newentry = create_short(loc);
	  pickentry->loc += 2;
	  pickentry->size -= 2;
	  if (pickentry->size > 0) {
	    insertentry(newentry);
	  } else {
	    delete_entry(pickentry);
	    list[pickindex] = newentry;
	  }
	  printlist();
	}
      }
    }

    // Add ushort.
    if (key == (int)'5') {
      pickentry = list[pickindex];
      if (strcmp(pickentry->type,"unknown") == 0) {
	if (pickentry->size >= 2) {
	  loc = pickentry->loc;
	  newentry = create_ushort(loc);
	  pickentry->loc += 2;
	  pickentry->size -= 2;
	  if (pickentry->size > 0) {
	    insertentry(newentry);
	  } else {
	    delete_entry(pickentry);
	    list[pickindex] = newentry;
	  }
	  printlist();
	}
      }
    }

    // Add int.
    if ((key == (int)'y') || (key == (int)'i')) {
      pickentry = list[pickindex];
      if (strcmp(pickentry->type,"unknown") == 0) {
	if (pickentry->size >= 4) {
	  loc = pickentry->loc;
	  newentry = create_int(loc);
	  pickentry->loc += 4;
	  pickentry->size -= 4;
	  if (pickentry->size > 0) {
	    insertentry(newentry);
	  } else {
	    delete_entry(pickentry);
	    list[pickindex] = newentry;
	  }
	  printlist();
	}
      }
    }

    // Add uint.
    if (key == (int)'6') {
      pickentry = list[pickindex];
      if (strcmp(pickentry->type,"unknown") == 0) {
	if (pickentry->size >= 4) {
	  loc = pickentry->loc;
	  newentry = create_uint(loc);
	  pickentry->loc += 4;
	  pickentry->size -= 4;
	  if (pickentry->size > 0) {
	    insertentry(newentry);
	  } else {
	    delete_entry(pickentry);
	    list[pickindex] = newentry;
	  }
	  printlist();
	}
      }
    }

    // Add float.
    if (key == (int)'f') {
      pickentry = list[pickindex];
      if (strcmp(pickentry->type,"unknown") == 0) {
	if (pickentry->size >= 4) {
	  loc = pickentry->loc;
	  newentry = create_float(loc);
	  pickentry->loc += 4;
	  pickentry->size -= 4;
	  if (pickentry->size > 0) {
	    insertentry(newentry);
	  } else {
	    delete_entry(pickentry);
	    list[pickindex] = newentry;
	  }
	  printlist();
	}
      }
    }

    // Hexdump format. Subeditable.
    if (key == (int)'h') {
      pickentry = list[pickindex];
      if (strcmp(pickentry->type,"unknown") == 0) {
	if (pickentry->size >= 1) {
	  loc = pickentry->loc;
	  newsize = 12;
	  if (newsize > pickentry->size) newsize = pickentry->size;
	  newentry = create_hexdump(loc,newsize);
	  pickentry->loc += newsize;
	  pickentry->size -= newsize;
	  if (pickentry->size > 0) {
	    insertentry(newentry);
	  } else {
	    delete_entry(pickentry);
	    list[pickindex] = newentry;
	  }
	  printlist();
	}
      }
    }

    if (key == KEY_RIGHT) {
      pickentry = list[pickindex];
      if (strcmp(pickentry->type,"hexdump") == 0) {
	// If we are on a hexdump line which was shorted than other
	// hexdump lines and position was larger than the shorter line,
	// we must jump to the correct position first.
	if (hexdumpposition > pickentry->size) hexdumpposition = pickentry->size;
	// Move cursor to right. Skip the word "hexdump" and
	// jump from hex to hex.
	if (hexdumpposition < pickentry->size) {
	  hexdumpposition++;
	  cursorx = 0;
	  if (hexdumpposition > 0) {
	    cursorx = 8 + hexdumpposition*3;
	  }
	} else if (hexdumpposition == pickentry->size) {
	  // Move to next hexdump at position = 1.
	}
      }
      printlist();
    }

    if (key == KEY_LEFT) {
      pickentry = list[pickindex];
      if (strcmp(pickentry->type,"hexdump") == 0) {
	// If we are on a hexdump line which was shorted than other
	// hexdump lines and position was larger than the shorter line,
	// we must jump to the correct position first.
	if (hexdumpposition > pickentry->size) hexdumpposition = pickentry->size;
	// Move cursor to left. Skip the word "hexdump" and
	// jump from hex to hex.
	if (hexdumpposition > 0) {
	  hexdumpposition--;
	  cursorx = 0;
	  if (hexdumpposition > 0) {
	    cursorx = 8 + hexdumpposition*3;
	  }
	} else if (hexdumpposition == 0) {
	  // Move to previous hexdump at max position.
	  // XXXX Should cursor be kept always at position >= 1
	  // when in hexdumps? (i) if cursor is at position 1
	  // when user moved to hexdump, it indicates that something
	  // can be done, (ii) there is no real use for position 0.
	  // (iii) bad: user may follow the cursor when moving up and
	  // down; a sudden jump right by  
	}
      }
      printlist();
    }

    // Split hexdump line at cursor.
    if (key == 13) {
      pickentry = list[pickindex];
      if (strcmp(pickentry->type,"hexdump") == 0) {
#if 0
	// Not needed for split.
	// If we are on a hexdump line which was shorted than other
	// hexdump lines and position was larger than the shorter line,
	// we must jump to the correct position first.
	if (hexdumpposition > pickentry->size) hexdumpposition = pickentry->size;
#endif
	// Split.
	// This test handles also the case pickentry->size == 1.
	if ((hexdumpposition > 0) && (hexdumpposition < pickentry->size)) {
	  loc = pickentry->loc + hexdumpposition;
	  newsize = pickentry->size - hexdumpposition;
	  newentry = create_hexdump(loc,newsize);
	  pickentry->size -= newsize;
	  insertentry_after(newentry);
	  // hexdumpposition = newsize;
	  // Cursor update not needed.
	  cursorx = 0;
	  if (hexdumpposition > 0) {
	    cursorx = 8 + hexdumpposition*3;
	  }
	  printlist();
	}
      }
    }

    // Change existing entry to unknown.
    if (key == (int)'u') {
      pickentry = list[pickindex];
      if (strcmp(pickentry->type,"unknown") != 0) {
	if (pickentry->size > 0) {
	  loc = pickentry->loc;
	  newentry = create_unknown(loc,pickentry->size);
	  delete_entry(pickentry);
	  // insertentry(newentry); XXXX wrong
	  list[pickindex] = newentry;
	  cursorx = 0;
	  printlist();
	}
      }
    }

    // Merge unknown entries.
    // Merge hexdump entries.
    if (key == (int)'m') {
      pickentry = list[pickindex];
      if (strcmp(pickentry->type,"unknown") == 0) {
	if (pickindex < numlist - 1) {
	  if (strcmp(list[pickindex+1]->type,"unknown") == 0) {
	    pickentry->size += list[pickindex+1]->size;
	    delete_entry(list[pickindex+1]);
	    for (i = pickindex + 1; i < numlist - 1; i++) {
	      list[i] = list[i+1];
	    }
	    numlist--;
	    printlist();
	  }
	}
      } else if (strcmp(pickentry->type,"hexdump") == 0) {
	if (pickindex < numlist - 1) {
	  if (strcmp(list[pickindex+1]->type,"hexdump") == 0) {
	    // If we are on a hexdump line which was shorted than other
	    // hexdump lines and position was larger than the shorter line,
	    // we must jump to the correct position first.
	    if (hexdumpposition > pickentry->size) hexdumpposition = pickentry->size;
	    n = 12-pickentry->size; // Max bytes to move to first hexdump item.
	    if (n > 0) {
	      // How many bytes can be moved.
	      if (n > list[pickindex+1]->size) n = list[pickindex+1]->size;
	      // Move n bytes.
	      pickentry->size += n;
	      // Fix the second hexdump.
	      list[pickindex+1]->loc += n;
	      list[pickindex+1]->size -= n;
	      if (list[pickindex+1]->size == 0) {
		delete_entry(list[pickindex+1]);
		for (i = pickindex + 1; i < numlist - 1; i++) {
		  list[i] = list[i+1];
		}
		numlist--;
	      }
	      cursorx = 0;
	      if (hexdumpposition > 0) {
		cursorx = 8 + hexdumpposition*3;
	      }
	      printlist();
	    }
	  }
	}
      }
    }

    // Add mark to location given in this location.

    // Split to two unknowns.

    // Split hexdump. Left-right subediting for splitpoint.

    // Save.
    if (key == (int)'w') {
      fp = fopen("savefile","w");
      if (fp != NULL) {
	fprintf(fp,"numlist %i\n",numlist);
	for (i = 0; i < numlist; i++) {
	  fprintf(fp,"%i %s %i %s\n",list[i]->loc,list[i]->type,list[i]->size,list[i]->name);
	}
	fclose(fp);
      }
    }

    // Load.
    if (key == (int)'2') {
      fp = fopen("savefile","r");
      if (fp != NULL) {
	fscanf(fp,"numlist %i\n",&numlist);
	for (i = 0; i < numlist; i++) {
	  n = fscanf(fp,"%i %s %i %s\n",&loc,tmps,&newsize,tmps2);
	  if (n == 3) {
	    list[i] = create_new(loc,tmps,newsize,NULL);
	  } else {
	    if (strcmp(tmps2,"(null)") == 0) {
	      list[i] = create_new(loc,tmps,newsize,NULL);
	    } else {
	      list[i] = create_new(loc,tmps,newsize,tmps2);
	    }
	  }
	}
	fclose(fp);
	pickindex = 0;
	cursorx = 0;
	hexdumpposition = 0;
	printlist();
      }
    }

    // This is last so that it is not overwritten, or the screen cleared.
    // fprintf(stderr,"key = %i\n",key);

  }

  endwin();

  return 1;
}

