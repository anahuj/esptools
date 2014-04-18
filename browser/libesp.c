


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>
#include <zlib.h>

#include "mylib/filesdirs.h"
#include "mylib/mmapfile.h"
#include "mylib/buffer.h"
#include "mylib/parray.h"


// State of the current print and the browser.
// At update or when returning (stack pop), the gamefile data
// is reread and the print recreated.
typedef struct {
  void *b;
  int loc;
  int pickindex;
  int printoffset;
  int cursorlocation;
  int iscompressed;
  unsigned char *uncompbuffer;
  void *compb; // original compressed buffer
  int insidetype;
  char recordtype[5]; // string4; recordtype/subrecordtype
  int size; // Size of the group or record that is being entered, prior possible uncompression.
} ty_printinfo;

ty_printinfo printinfostack[20];
int printinfostack_n = 0;

typedef struct {
  int maxnumlines;
  int numlines;
  char **lines;
  int *locations;
  int *formidindex; // Index to global_records[], if line has FormID.
  // Separate error print.
  int numerrors;
  char **errors;
} ty_printblock;

typedef struct {
  int loc;
  char *type; // "unknown" "int" "float" etc.
  int size;
  char *name;
} ty_entry;

ty_entry *list[1024];
// char *list[1024];
int numlist;
// int pickindex;
// int printoffset;

void *b = NULL;     // current buffer.
void *rootb = NULL; // buffer for advancing through FormIDs
void *pb = NULL; // printblock
ty_printinfo pi; // printinfo


char global_inrecord_type[1024];

char *global_progname;
int global_headersize;

typedef struct {
  int loc;
  unsigned int formid;
} ty_records;

ty_records global_records[2000000];
int global_numrecords;

FILE *gf;


char tmp_s[65536]; // largest nstring BOOK/DESC 41583

char tmps[65536];
char tmps2[65536];
chtype tmpchs[65536];
chtype chcursor[16];

#define C_INPUTLINE_SIZE 1024
char inputline[C_INPUTLINE_SIZE];
chtype inputlinech[C_INPUTLINE_SIZE];
int numinputline;
int textinputmode;

int xscreensize;
int yscreensize;
int cursorx;

void printinfo_init0()
{
  pi.b = b;
  pi.loc = 0;
  pi.pickindex = 0;
  pi.printoffset = 0;
  pi.cursorlocation = 0;
  pi.iscompressed = 0;
  pi.uncompbuffer = NULL;
  pi.compb = NULL;
  pi.insidetype = 0;
  sprintf(pi.recordtype,"%s","GRUP"); // Root level. Not a real GRUP.
  pi.size = 0;
}

void printinfo_init1()
{
  pi.b = b;
  pi.loc = 0;
  pi.pickindex = 0;
  pi.printoffset = 0;
  pi.cursorlocation = 0;
  pi.iscompressed = 0;
  pi.uncompbuffer = NULL;
  pi.compb = NULL;
  pi.insidetype = 0;
  sprintf(pi.recordtype,"%s","");
  pi.size = 0;
}

void printinfo_copy(ty_printinfo *source, ty_printinfo *target)
{
  target->b = source->b;
  target->loc = source->loc;
  target->pickindex = source->pickindex;
  target->printoffset = source->printoffset;
  target->cursorlocation = source->cursorlocation;
  target->iscompressed = source->iscompressed;
  target->uncompbuffer = source->uncompbuffer;
  target->compb = source->compb;
  target->insidetype = source->insidetype;
  strcpy(target->recordtype,source->recordtype);
  target->size = source->size;
}

void printinfo_print()
{
  fprintf(stderr,"%x\n",pi.b);
  fprintf(stderr,"%i\n",pi.loc);
  fprintf(stderr,"%i\n",pi.pickindex);
  fprintf(stderr,"%i\n",pi.printoffset);
  fprintf(stderr,"%i\n",pi.cursorlocation);
  fprintf(stderr,"%i\n",pi.iscompressed);
  fprintf(stderr,"%x\n",pi.uncompbuffer);
  fprintf(stderr,"%x\n",pi.compb);
  fprintf(stderr,"%i\n",pi.insidetype);
  fprintf(stderr,"%s\n",pi.recordtype);
  fprintf(stderr,"%i\n",pi.size);
}

void printinfo_printlog()
{
  fprintf(gf,"%x\n",pi.b);
  fprintf(gf,"%i\n",pi.loc);
  fprintf(gf,"%i\n",pi.pickindex);
  fprintf(gf,"%i\n",pi.printoffset);
  fprintf(gf,"%i\n",pi.cursorlocation);
  fprintf(gf,"%i\n",pi.iscompressed);
  fprintf(gf,"%x\n",pi.uncompbuffer);
  fprintf(gf,"%x\n",pi.compb);
  fprintf(gf,"%i\n",pi.insidetype);
  fprintf(gf,"%s\n",pi.recordtype);
  fprintf(gf,"%i\n",pi.size);
  fflush(gf);
}


void *printblock_new()
{
  ty_printblock *p;
  int i;

  p = (ty_printblock *)malloc(sizeof(ty_printblock));
  p->maxnumlines = 400000;
  p->lines = (char **)malloc(p->maxnumlines*sizeof(char *));
  p->locations = (int *)malloc(p->maxnumlines*sizeof(int));
  p->formidindex = (int *)malloc(p->maxnumlines*sizeof(int));
  for (i = 0; i < p->maxnumlines; i++) {
    p->lines[i] = NULL;
    p->locations[i] = -1;
    p->formidindex[i] = -1;
  }
  p->numlines = 0;

  p->numerrors = 10;
  p->errors = (char **)malloc(p->numerrors*sizeof(char *));
  for (i = 0; i < p->numerrors; i++) {
    p->errors[i] = NULL;
  }

  return (void *)p;
}

void printblock_free(void *pp)
{
  ty_printblock *p;
  int i;

  p = pp;
  for (i = 0; i < p->maxnumlines; i++) {
    if (p->lines[i] != NULL) {
      free(p->lines[i]);
    }
  }
  free(p->lines);
  free(p->locations);
  free(p->formidindex);
  free(p);
}

void printblock_delete(void *pp)
{
  ty_printblock *p;
  int i;

  p = pp;
  for (i = 0; i < p->maxnumlines; i++) {
    if (p->lines[i] != NULL) {
      free(p->lines[i]);
    }
  }
  free(p->lines);
  free(p->locations);
  free(p->formidindex);
  free(p);
}

void printblock_add(void *pp, char *s)
{
  ty_printblock *p;

  p = pp;
  if (p->numlines < p->maxnumlines) {
    p->lines[p->numlines] = strdup(s);
    p->numlines++;
  } else {
    // Temporary coding. Dynamic enlargement later.
    fprintf(stderr,"printblock too small, %i\n",p->maxnumlines);
    exit(-1);
  }
}

void printblock_add_loc(void *pp, char *s, int loc)
{
  ty_printblock *p;

  p = pp;
  if (p->numlines < p->maxnumlines) {
    p->lines[p->numlines] = strdup(s);
    p->locations[p->numlines] = loc;
    p->numlines++;
  } else {
    // Temporary coding. Dynamic enlargement later.
    fprintf(stderr,"printblock too small, %i\n",p->maxnumlines);
    exit(-1);
  }
}

void printblock_add_loc_formidindex(void *pp, char *s, int loc, int formidindex)
{
  ty_printblock *p;

  p = pp;
  if (p->numlines < p->maxnumlines) {
    p->lines[p->numlines] = strdup(s);
    p->locations[p->numlines] = loc;
    p->formidindex[p->numlines] = formidindex;
    p->numlines++;
  } else {
    // Temporary coding. Dynamic enlargement later.
    fprintf(stderr,"printblock too small, %i\n",p->maxnumlines);
    exit(-1);
  }
}

int printblock_get_numlines(void *pp)
{
  ty_printblock *p;

  p = pp;
  return p->numlines;
}

char *printblock_get_line(void *pp, int k)
{
  ty_printblock *p;

  p = pp;
  return p->lines[k];
}

int printblock_get_location(void *pp, int k)
{
  ty_printblock *p;

  p = pp;
  return p->locations[k];
}

int printblock_get_formidindex(void *pp, int k)
{
  ty_printblock *p;

  p = pp;
  return p->formidindex[k];
}

void printblock_put_line_strdup(void *pp, int k, char *s)
{
  ty_printblock *p;

  p = pp;
  if (p->lines[k] != NULL) {
    free(p->lines[k]);
  }
  p->lines[k] = strdup(s);
}

void printblock_print(void *pp)
{
  ty_printblock *p;
  int i;

  p = pp;
  for (i = 0; i < p->numlines; i++) {
    if (p->lines[i] != NULL) {
      printf("%s",p->lines[i]);
    } else {
      printf("NULL line %i",i);
    }
  }
}

int printblock_get_numerrors(void *pp)
{
  ty_printblock *p;

  p = pp;
  return p->numerrors;
}

char *printblock_get_error(void *pp, int n)
{
  ty_printblock *p;

  p = pp;
  return p->errors[n];
}

void printblock_add_error(void *pp, char *s)
{
  ty_printblock *p;
  int i;

  p = pp;
  for (i = 0; i < p->numerrors; i++) {
    if (p->errors[i] == NULL) {
      p->errors[i] = strdup(s);
      return;
    }
  }
  free(p->errors[0]);
  for (i = 0; i < p->numerrors-1; i++) {
    p->errors[i] = p->errors[i+1];
  }
  p->errors[p->numerrors-1] = strdup(s);
}



#if 0
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
#endif

typedef struct {
  int opcode;
  char scan2[5]; // OF Om mF
  char *scan3; // printed
} ty_condfunc;

ty_condfunc global_condfunclist[1024];
int global_numcondfunc = 0;

void cf_init()
{
  global_numcondfunc = 0;
}

void cf_add(char *s1, char *s2, char *s3)
{
  global_condfunclist[global_numcondfunc].opcode = atoi(s1);
  strcpy(global_condfunclist[global_numcondfunc].scan2,s2);
  global_condfunclist[global_numcondfunc].scan3 = strdup(s3);
  global_numcondfunc++;
}

char *cf_search_o(int opcode)
{
  int i;

  for (i = 0; i < global_numcondfunc; i++) {
    if (global_condfunclist[i].opcode == opcode) {
      if (global_condfunclist[i].scan2[0] == 'O') {
	return global_condfunclist[i].scan3;
      }
    }
  }
  return NULL;
}


typedef struct {
  int type;
  int size;
  char *name;
  void *data;
  int intvalue;
} ty_blockobject;

typedef struct {
  char *name;
  int maxnumobjects;
  int numobjects;
  ty_blockobject **objects;
} ty_block;

typedef struct {
  int maxnumblocks;
  int numblocks;
  ty_block **blocks;
} ty_blocklist;


typedef struct {
  int bit;
  char *name;
} ty_flag;

typedef struct {
  int maxnumflags;
  int numflags;
  ty_flag flags[128];
} ty_flagsdata;

ty_blocklist global_blocklist;
ty_block *global_currentblock;
ty_blockobject *global_currentblockobject;
char global_last_edid[1024];

#define C_BLOCKOBJECTTYPE_STRING4     1
#define C_BLOCKOBJECTTYPE_INT         2
#define C_BLOCKOBJECTTYPE_UINT        3
#define C_BLOCKOBJECTTYPE_SHORT       4
#define C_BLOCKOBJECTTYPE_USHORT      5
#define C_BLOCKOBJECTTYPE_BYTE        6
#define C_BLOCKOBJECTTYPE_UBYTE       7
#define C_BLOCKOBJECTTYPE_FLAGS32     8
#define C_BLOCKOBJECTTYPE_FLAGS16     9
#define C_BLOCKOBJECTTYPE_FLAGS8      10
#define C_BLOCKOBJECTTYPE_FLOAT       11
#define C_BLOCKOBJECTTYPE_NSTRING     12
#define C_BLOCKOBJECTTYPE_INTARRAY    13
#define C_BLOCKOBJECTTYPE_BREAK       14
#define C_BLOCKOBJECTTYPE_IFSIZE      15
#define C_BLOCKOBJECTTYPE_GMSTDATA    16
#define C_BLOCKOBJECTTYPE_REPEAT      17
#define C_BLOCKOBJECTTYPE_SETLOC      18
#define C_BLOCKOBJECTTYPE_GETLOC      19
#define C_BLOCKOBJECTTYPE_NIFZSTRING  20
#define C_BLOCKOBJECTTYPE_SGMSTDATA   21


void f_init()
{
  global_blocklist.maxnumblocks = 4000;
  global_blocklist.numblocks = 0;
  global_blocklist.blocks = (ty_block **)malloc(global_blocklist.maxnumblocks*sizeof(ty_block *));

  global_currentblock = NULL;
  global_currentblockobject = NULL;
}

void f_block(char *s)
{
  ty_block *block;

  block = (ty_block *)malloc(sizeof(ty_block));
  block->name = strdup(s);
  block->maxnumobjects = 256;
  block->numobjects = 0;
  block->objects = (ty_blockobject **)malloc(block->maxnumobjects*sizeof(ty_blockobject *));

  global_blocklist.blocks[global_blocklist.numblocks] = block;
  global_blocklist.numblocks++;

  global_currentblock = block;
}

void f_string4(char *s)
{
  ty_blockobject *object;

  object = (ty_blockobject *)malloc(sizeof(ty_blockobject));
  object->type = C_BLOCKOBJECTTYPE_STRING4;
  object->size = 4;
  object->name = strdup(s);
  object->data = NULL;

  global_currentblock->objects[global_currentblock->numobjects] = object;
  global_currentblock->numobjects++;

  global_currentblockobject = object;
}

void f_int(char *s)
{
  ty_blockobject *object;

  object = (ty_blockobject *)malloc(sizeof(ty_blockobject));
  object->type = C_BLOCKOBJECTTYPE_INT;
  object->size = 4;
  object->name = strdup(s);
  object->data = NULL;

  global_currentblock->objects[global_currentblock->numobjects] = object;
  global_currentblock->numobjects++;

  global_currentblockobject = object;
}

void f_uint(char *s)
{
  ty_blockobject *object;

  object = (ty_blockobject *)malloc(sizeof(ty_blockobject));
  object->type = C_BLOCKOBJECTTYPE_UINT;
  object->size = 4;
  object->name = strdup(s);
  object->data = NULL;

  global_currentblock->objects[global_currentblock->numobjects] = object;
  global_currentblock->numobjects++;

  global_currentblockobject = object;
}

void f_short(char *s)
{
  ty_blockobject *object;

  object = (ty_blockobject *)malloc(sizeof(ty_blockobject));
  object->type = C_BLOCKOBJECTTYPE_SHORT;
  object->size = 2;
  object->name = strdup(s);
  object->data = NULL;

  global_currentblock->objects[global_currentblock->numobjects] = object;
  global_currentblock->numobjects++;

  global_currentblockobject = object;
}

void f_ushort(char *s)
{
  ty_blockobject *object;

  object = (ty_blockobject *)malloc(sizeof(ty_blockobject));
  object->type = C_BLOCKOBJECTTYPE_USHORT;
  object->size = 2;
  object->name = strdup(s);
  object->data = NULL;

  global_currentblock->objects[global_currentblock->numobjects] = object;
  global_currentblock->numobjects++;

  global_currentblockobject = object;
}

void f_byte(char *s)
{
  ty_blockobject *object;

  object = (ty_blockobject *)malloc(sizeof(ty_blockobject));
  object->type = C_BLOCKOBJECTTYPE_BYTE;
  object->size = 1;
  object->name = strdup(s);
  object->data = NULL;

  global_currentblock->objects[global_currentblock->numobjects] = object;
  global_currentblock->numobjects++;

  global_currentblockobject = object;
}

void f_ubyte(char *s)
{
  ty_blockobject *object;

  object = (ty_blockobject *)malloc(sizeof(ty_blockobject));
  object->type = C_BLOCKOBJECTTYPE_UBYTE;
  object->size = 1;
  object->name = strdup(s);
  object->data = NULL;

  global_currentblock->objects[global_currentblock->numobjects] = object;
  global_currentblock->numobjects++;

  global_currentblockobject = object;
}

void f_flags32(char *s)
{
  ty_blockobject *object;

  object = (ty_blockobject *)malloc(sizeof(ty_blockobject));
  object->type = C_BLOCKOBJECTTYPE_FLAGS32;
  object->size = 4;
  object->name = strdup(s);
  object->data = NULL;

  global_currentblock->objects[global_currentblock->numobjects] = object;
  global_currentblock->numobjects++;

  global_currentblockobject = object;
}

void f_flags16(char *s)
{
  ty_blockobject *object;

  object = (ty_blockobject *)malloc(sizeof(ty_blockobject));
  object->type = C_BLOCKOBJECTTYPE_FLAGS16;
  object->size = 2;
  object->name = strdup(s);
  object->data = NULL;

  global_currentblock->objects[global_currentblock->numobjects] = object;
  global_currentblock->numobjects++;

  global_currentblockobject = object;
}

void f_flags8(char *s)
{
  ty_blockobject *object;

  object = (ty_blockobject *)malloc(sizeof(ty_blockobject));
  object->type = C_BLOCKOBJECTTYPE_FLAGS8;
  object->size = 1;
  object->name = strdup(s);
  object->data = NULL;

  global_currentblock->objects[global_currentblock->numobjects] = object;
  global_currentblock->numobjects++;

  global_currentblockobject = object;
}

void f_flags_bit(int n, char *s)
{
  ty_flagsdata *flagsdata;

  if (global_currentblockobject != NULL) {
    if ((global_currentblockobject->type == C_BLOCKOBJECTTYPE_FLAGS32) ||
	(global_currentblockobject->type == C_BLOCKOBJECTTYPE_FLAGS16) ||
	(global_currentblockobject->type == C_BLOCKOBJECTTYPE_FLAGS8)) {
      if (global_currentblockobject->data == NULL) {
	flagsdata = (ty_flagsdata *)malloc(sizeof(ty_flagsdata));
	flagsdata->maxnumflags = 128; // See typedef for size.
	flagsdata->numflags = 0;
	global_currentblockobject->data = flagsdata;
      } else {
	flagsdata = global_currentblockobject->data;
      }
      flagsdata->flags[flagsdata->numflags].bit = n;
      flagsdata->flags[flagsdata->numflags].name = strdup(s);
      flagsdata->numflags++;
    } else {
      fprintf(stderr,"global_currentblockobject is not a flag type\n");
    }
  } else {
    fprintf(stderr,"global_currentblockobject = NULL\n");
  }
}

void f_float(char *s)
{
  ty_blockobject *object;

  object = (ty_blockobject *)malloc(sizeof(ty_blockobject));
  object->type = C_BLOCKOBJECTTYPE_FLOAT;
  object->size = 4;
  object->name = strdup(s);
  object->data = NULL;

  global_currentblock->objects[global_currentblock->numobjects] = object;
  global_currentblock->numobjects++;

  global_currentblockobject = object;
}

void f_nstring(char *s)
{
  ty_blockobject *object;

  object = (ty_blockobject *)malloc(sizeof(ty_blockobject));
  object->type = C_BLOCKOBJECTTYPE_NSTRING;
  object->size = -1;
  object->name = strdup(s);
  object->data = NULL;

  global_currentblock->objects[global_currentblock->numobjects] = object;
  global_currentblock->numobjects++;

  global_currentblockobject = object;
}

void f_intarray(char *s)
{
  ty_blockobject *object;

  object = (ty_blockobject *)malloc(sizeof(ty_blockobject));
  object->type = C_BLOCKOBJECTTYPE_INTARRAY;
  object->size = -1;
  object->name = strdup(s);
  object->data = NULL;

  global_currentblock->objects[global_currentblock->numobjects] = object;
  global_currentblock->numobjects++;

  global_currentblockobject = object;
}

void f_break(int n)
{
  ty_blockobject *object;

  object = (ty_blockobject *)malloc(sizeof(ty_blockobject));
  object->type = C_BLOCKOBJECTTYPE_BREAK;
  object->size = 0;
  object->name = NULL;
  object->intvalue = n;
  object->data = NULL;

  global_currentblock->objects[global_currentblock->numobjects] = object;
  global_currentblock->numobjects++;

  global_currentblockobject = object;
}

void f_ifsize(int n)
{
  ty_blockobject *object;

  object = (ty_blockobject *)malloc(sizeof(ty_blockobject));
  object->type = C_BLOCKOBJECTTYPE_IFSIZE;
  object->size = 0;
  object->name = NULL;
  object->intvalue = n;
  object->data = NULL;

  global_currentblock->objects[global_currentblock->numobjects] = object;
  global_currentblock->numobjects++;

  global_currentblockobject = object;
}

void f_gmstdata(char *s)
{
  ty_blockobject *object;

  object = (ty_blockobject *)malloc(sizeof(ty_blockobject));
  object->type = C_BLOCKOBJECTTYPE_GMSTDATA;
  object->size = -1;
  object->name = strdup(s);
  object->data = NULL;

  global_currentblock->objects[global_currentblock->numobjects] = object;
  global_currentblock->numobjects++;

  global_currentblockobject = object;
}

void f_sgmstdata(char *s)
{
  ty_blockobject *object;

  object = (ty_blockobject *)malloc(sizeof(ty_blockobject));
  object->type = C_BLOCKOBJECTTYPE_SGMSTDATA;
  object->size = -1;
  object->name = strdup(s);
  object->data = NULL;

  global_currentblock->objects[global_currentblock->numobjects] = object;
  global_currentblock->numobjects++;

  global_currentblockobject = object;
}

void f_repeat(char *s)
{
  ty_blockobject *object;

  object = (ty_blockobject *)malloc(sizeof(ty_blockobject));
  object->type = C_BLOCKOBJECTTYPE_REPEAT;
  object->size = 0;
  object->name = NULL;
  object->intvalue = atoi(s);
  object->data = NULL;

  global_currentblock->objects[global_currentblock->numobjects] = object;
  global_currentblock->numobjects++;

  global_currentblockobject = object;
}

// Example: intrepeat name 3
// Read int N and repeat next 3 lines N times.
void f_intrepeat(char *s)
{
  ty_blockobject *object;

  object = (ty_blockobject *)malloc(sizeof(ty_blockobject));
  object->type = C_BLOCKOBJECTTYPE_REPEAT;
  object->size = 0;
  object->name = NULL;
  object->intvalue = atoi(s); // Number of objects to repeat
  object->data = NULL;

  global_currentblock->objects[global_currentblock->numobjects] = object;
  global_currentblock->numobjects++;

  global_currentblockobject = object;
}

void f_setloc(char *s)
{
  ty_blockobject *object;

  object = (ty_blockobject *)malloc(sizeof(ty_blockobject));
  object->type = C_BLOCKOBJECTTYPE_SETLOC;
  object->size = 0;
  object->name = NULL;
  object->intvalue = 0;
  object->data = NULL;

  global_currentblock->objects[global_currentblock->numobjects] = object;
  global_currentblock->numobjects++;

  global_currentblockobject = object;
}

void f_getloc(char *s)
{
  ty_blockobject *object;

  object = (ty_blockobject *)malloc(sizeof(ty_blockobject));
  object->type = C_BLOCKOBJECTTYPE_GETLOC;
  object->size = 0;
  object->name = NULL;
  object->intvalue = 0;
  object->data = NULL;

  global_currentblock->objects[global_currentblock->numobjects] = object;
  global_currentblock->numobjects++;

  global_currentblockobject = object;
}

void f_nifzstring(char *s)
{
  ty_blockobject *object;

  object = (ty_blockobject *)malloc(sizeof(ty_blockobject));
  object->type = C_BLOCKOBJECTTYPE_NIFZSTRING;
  object->size = -1;
  object->name = strdup(s);
  object->data = NULL;

  global_currentblock->objects[global_currentblock->numobjects] = object;
  global_currentblock->numobjects++;

  global_currentblockobject = object;
}


void f_import(ty_blockobject *importobject)
{
  ty_blockobject *object;

  object = (ty_blockobject *)malloc(sizeof(ty_blockobject));
  object->type = importobject->type;
  object->size = importobject->size;
  object->name = importobject->name; // XXXX Do not delete original.
  object->data = importobject->data; // XXXX Do not delete original.

  global_currentblock->objects[global_currentblock->numobjects] = object;
  global_currentblock->numobjects++;

  global_currentblockobject = object;
}


int global_subrecordsize;
int global_loc;

// XXXX Skipping nstring and intarray is now problem.
// XXXX Solution 1: Read the whole block.
// XXXX Solution 2: Because they are for browsing purposes,
// XXXX only use them for blocks which causes no problem.
// XXXX Solution 3: Return as soon as the variable has been found. Done.

char *buffer_block_get_value_string4(void *b, char *blockname, char *blockobjectname)
{
  int i,k;
  ty_block *block;
  ty_blockobject *object;
  int n;
  char *s;

  k = -1;
  for (i = 0; i < global_blocklist.numblocks; i++) {
    if (strcmp(global_blocklist.blocks[i]->name,blockname) == 0) {
      k = i;
    }
  }
  if (k == -1) {
    fprintf(stderr,"block %s has not been defined\n",blockname);
    return NULL;
  }

  block = global_blocklist.blocks[k];
  for (i = 0; i < block->numobjects; i++) {
    object = block->objects[i];
    if (strcmp(object->name,blockobjectname) == 0) {
      if (object->type == C_BLOCKOBJECTTYPE_STRING4) {
	s = buffer_read_string4(b);
	return s;
      } else {
	fprintf(stderr,"blockobject type is not string4\n");
	return NULL;
      }
    } else {
      // XXXX fix nstring and intarray
      buffer_skip_bytes(b,object->size);
    }

  }

  return NULL;
}

char *buffer_block_get_value_string4_returntest(void *b, char *blockname, char *blockobjectname)
{
  int i,k;
  ty_block *block;
  ty_blockobject *object;
  int n;
  char *s;

  k = -1;
  for (i = 0; i < global_blocklist.numblocks; i++) {
    if (strcmp(global_blocklist.blocks[i]->name,blockname) == 0) {
      k = i;
    }
  }
  if (k == -1) {
    fprintf(stderr,"block %s has not been defined\n",blockname);
    return NULL;
  }
  fprintf(stderr,"s1\n"); sleep(6);

  block = global_blocklist.blocks[k];
  fprintf(stderr,"s2\n"); sleep(6);
  for (i = 0; i < block->numobjects; i++) {
  fprintf(stderr,"s3\n"); sleep(6);
    object = block->objects[i];
  fprintf(stderr,"s4\n"); sleep(6);
    if (strcmp(object->name,blockobjectname) == 0) {
  fprintf(stderr,"s5\n"); sleep(6);
      if (object->type == C_BLOCKOBJECTTYPE_STRING4) {
  fprintf(stderr,"s6\n"); sleep(6);
  fprintf(stderr,"using b %x %x\n",b,buffer_getbuf(b)); sleep(6);
	s = buffer_read_string4(b);
  fprintf(stderr,"s7\n"); sleep(6);
	return s;
      } else {
	fprintf(stderr,"blockobject type is not string4\n");
	return NULL;
      }
    } else {
  fprintf(stderr,"s8\n"); sleep(6);
      // XXXX fix nstring and intarray
      buffer_skip_bytes(b,object->size);
    }

  }

  return NULL;
}

int buffer_block_get_value_int(void *b, char *blockname, char *blockobjectname)
{
  int i,k;
  ty_block *block;
  ty_blockobject *object;
  int n;
  char *s;

  k = -1;
  for (i = 0; i < global_blocklist.numblocks; i++) {
    if (strcmp(global_blocklist.blocks[i]->name,blockname) == 0) {
      k = i;
    }
  }
  if (k == -1) {
    fprintf(stderr,"block %s has not been defined\n",blockname);
    return -1;
  }

  block = global_blocklist.blocks[k];
  for (i = 0; i < block->numobjects; i++) {
    object = block->objects[i];
    if (strcmp(object->name,blockobjectname) == 0) {
      if (object->type == C_BLOCKOBJECTTYPE_INT) {
	n = buffer_read_int(b);
	return n;
      } else {
	fprintf(stderr,"blockobject type is not int\n");
	return -1;
      }
    } else {
      // XXXX fix nstring and intarray
      buffer_skip_bytes(b,object->size);
    }

  }

  return -1;
}

unsigned int buffer_block_get_value_uint(void *b, char *blockname, char *blockobjectname)
{
  int i,k;
  ty_block *block;
  ty_blockobject *object;
  unsigned int n;
  char *s;

  k = -1;
  for (i = 0; i < global_blocklist.numblocks; i++) {
    if (strcmp(global_blocklist.blocks[i]->name,blockname) == 0) {
      k = i;
    }
  }
  if (k == -1) {
    fprintf(stderr,"block %s has not been defined\n",blockname);
    return -1;
  }

  block = global_blocklist.blocks[k];
  for (i = 0; i < block->numobjects; i++) {
    object = block->objects[i];
    if (strcmp(object->name,blockobjectname) == 0) {
      if (object->type == C_BLOCKOBJECTTYPE_UINT) {
	n = buffer_read_uint(b);
	return n;
      } else {
	fprintf(stderr,"blockobject type is not int\n");
	return -1;
      }
    } else {
      // XXXX fix nstring and intarray
      buffer_skip_bytes(b,object->size);
    }

  }

  return -1;
}

int buffer_block_get_value_ushort(void *b, char *blockname, char *blockobjectname)
{
  int i,k;
  ty_block *block;
  ty_blockobject *object;
  int n;
  char *s;

  k = -1;
  for (i = 0; i < global_blocklist.numblocks; i++) {
    if (strcmp(global_blocklist.blocks[i]->name,blockname) == 0) {
      k = i;
    }
  }
  if (k == -1) {
    fprintf(stderr,"block %s has not been defined\n",blockname);
    return -1;
  }

  block = global_blocklist.blocks[k];
  for (i = 0; i < block->numobjects; i++) {
    object = block->objects[i];
    if (strcmp(object->name,blockobjectname) == 0) {
      if (object->type == C_BLOCKOBJECTTYPE_USHORT) {
	n = buffer_read_ushort(b);
	return n;
      } else {
	fprintf(stderr,"blockobject type is not ushort\n");
	return -1;
      }
    } else {
      // XXXX fix nstring and intarray
      buffer_skip_bytes(b,object->size);
    }

  }

  return -1;
}

int buffer_block_get_value_flags(void *b, char *blockname, char *blockobjectname)
{
  int i,k;
  ty_block *block;
  ty_blockobject *object;
  int n;
  char *s;

  k = -1;
  for (i = 0; i < global_blocklist.numblocks; i++) {
    if (strcmp(global_blocklist.blocks[i]->name,blockname) == 0) {
      k = i;
    }
  }
  if (k == -1) {
    fprintf(stderr,"block %s has not been defined\n",blockname);
    return -1;
  }

  block = global_blocklist.blocks[k];
  for (i = 0; i < block->numobjects; i++) {
    object = block->objects[i];
    if (strcmp(object->name,blockobjectname) == 0) {
      if (object->type == C_BLOCKOBJECTTYPE_FLAGS32) {
	n = buffer_read_int(b);
	return n;
      } else if (object->type == C_BLOCKOBJECTTYPE_FLAGS16) {
	n = buffer_read_short(b);
	return n;
      } else if (object->type == C_BLOCKOBJECTTYPE_FLAGS8) {
	n = buffer_read_byte(b);
	return n;
      } else {
	fprintf(stderr,"blockobject type is not a flag\n");
	return -1;
      }
    } else {
      // XXXX fix nstring and intarray
      buffer_skip_bytes(b,object->size);
    }

  }

  return -1;
}


// XXXX Now subrecord is in its own buffer. Check overruns.
void buffer_block_print_pb_loc(void *b, char *blockname, void *pb, int loc)
{
  int i,j,k;
  ty_block *block;
  ty_blockobject *object;
  int n;
  char *s;
  float f;
  int m;
  int done;
  int repeatpos;
  int isformid;
  int foundformid;
  char *type;
  int saveloc;


  // XXXX total_subrecordsize is used in the break command.
  // XXXX This same routine is used for group and record headers,
  // XXXX but the break system is not used there.
  int total_subrecordsize;
  int object_size;


  k = -1;
  for (i = 0; i < global_blocklist.numblocks; i++) {
    if (strcmp(global_blocklist.blocks[i]->name,blockname) == 0) {
      k = i;
    }
  }
  if (k == -1) {
    fprintf(stderr,"block %s has not been defined\n",blockname);
    return;
  }

  block = global_blocklist.blocks[k];
  total_subrecordsize = -6; // Exclude header.
  repeatpos = -1;
  for (i = 0; i < block->numobjects; i++) {
    object = block->objects[i];
    object_size = object->size;
    if (object_size > buffer_gettaillen(b))
      return;
    if (object->type == C_BLOCKOBJECTTYPE_STRING4) {
      s = buffer_read_string4(b);
      sprintf(tmp_s,"%s = %s",object->name,s);
      printblock_add_loc(pb,tmp_s,loc);
      free(s);
    } else if (object->type == C_BLOCKOBJECTTYPE_INT) {
      n = buffer_read_int(b);

      // Special handling for Function_IDs.
      if (strcmp(object->name,"Function_ID") == 0) {
	s = cf_search_o(n);
	if (s != NULL) {
	  sprintf(tmp_s,"%s = %i (%s)",object->name,n,s);
	  printblock_add_loc(pb,tmp_s,loc);
	} else {
	  sprintf(tmp_s,"%s = %i (unknown function)",object->name,n);
	  printblock_add_loc(pb,tmp_s,loc);
	}
      } else {
	sprintf(tmp_s,"%s = %i",object->name,n);
	printblock_add_loc(pb,tmp_s,loc);
      }
    } else if (object->type == C_BLOCKOBJECTTYPE_UINT) {
      n = buffer_read_uint(b);

      // Special handling for FormID refs.
      isformid = 0;
      if (strlen(object->name) >= 6) {
	if (strcmp(&(object->name[strlen(object->name) - 6]),"FormID") == 0) {
	  isformid = 1;
	  printblock_add_error(pb,object->name);
	}
      }
      if (isformid == 1) {
	// Search for the record with the found FormID.
	foundformid = -1;
	for (j = 0; j < global_numrecords; j++) {
	  if (global_records[j].formid == (unsigned int)n) {
	    foundformid = j;
	  }
	}
	if (foundformid == -1) {
	  sprintf(tmp_s,"%s = %i",object->name,n);
	  printblock_add_loc(pb,tmp_s,loc);
	} else {
	  // Check type of the referenced record.
	  buffer_setloc(rootb,global_records[foundformid].loc);
	  type = buffer_block_get_value_string4(rootb,"recgroup","type");

	  sprintf(tmp_s,"%s = %i (ref at loc = %i type = %s)",object->name,n,global_records[foundformid].loc,type);
	  free(type);
	  printblock_add_loc_formidindex(pb,tmp_s,loc,foundformid);
	}
      } else {
	sprintf(tmp_s,"%s = %i",object->name,n);
	printblock_add_loc(pb,tmp_s,loc);
      }
    } else if (object->type == C_BLOCKOBJECTTYPE_SHORT) {
      n = buffer_read_short(b);
      sprintf(tmp_s,"%s = %i",object->name,n);
      printblock_add_loc(pb,tmp_s,loc);
    } else if (object->type == C_BLOCKOBJECTTYPE_USHORT) {
      n = buffer_read_ushort(b);
      sprintf(tmp_s,"%s = %i",object->name,n);
      printblock_add_loc(pb,tmp_s,loc);
    } else if (object->type == C_BLOCKOBJECTTYPE_BYTE) {
      n = buffer_read_byte(b);
      sprintf(tmp_s,"%s = %i",object->name,n);
      printblock_add_loc(pb,tmp_s,loc);
    } else if (object->type == C_BLOCKOBJECTTYPE_UBYTE) {
      n = buffer_read_ubyte(b);
      sprintf(tmp_s,"%s = %i",object->name,n);
      printblock_add_loc(pb,tmp_s,loc);
    } else if (object->type == C_BLOCKOBJECTTYPE_FLAGS32) {
      n = buffer_read_uint(b);
      sprintf(tmp_s,"%s = %x",object->name,n);
      printblock_add_loc(pb,tmp_s,loc);
    } else if (object->type == C_BLOCKOBJECTTYPE_FLAGS16) {
      n = buffer_read_ushort(b);
      sprintf(tmp_s,"%s = %x",object->name,n);
      printblock_add_loc(pb,tmp_s,loc);
    } else if (object->type == C_BLOCKOBJECTTYPE_FLAGS8) {
      n = buffer_read_ubyte(b);
      sprintf(tmp_s,"%s = %x",object->name,n);
      printblock_add_loc(pb,tmp_s,loc);
    } else if (object->type == C_BLOCKOBJECTTYPE_FLOAT) {
      f = buffer_read_float(b);
      sprintf(tmp_s,"%s = %f",object->name,f);
      printblock_add_loc(pb,tmp_s,loc);
    } else if (object->type == C_BLOCKOBJECTTYPE_NSTRING) {
      s = buffer_read_nstring(b,global_subrecordsize);
      sprintf(tmp_s,"%s = %s",object->name,s);
      printblock_add_loc(pb,tmp_s,loc);
      if (strcmp(&(block->name[5]),"EDID") == 0) {
	sprintf(global_last_edid,"%s",s);
      }
      free(s);
      // XXXX fails if nstring is only a part of the subrecord
      // object_size = ?
      object_size = global_subrecordsize;
    } else if (object->type == C_BLOCKOBJECTTYPE_INTARRAY) {
      m = global_subrecordsize/4;
      for (j = 0; j < m; j++) {
	n = buffer_read_int(b);
	sprintf(tmp_s,"%s = %i",object->name,n);
	printblock_add_loc(pb,tmp_s,loc);
      }
      // XXXX fails if nstring is only a part of the subrecord
      // object_size = ?
      object_size = global_subrecordsize;
    } else if (object->type == C_BLOCKOBJECTTYPE_BREAK) {
      // Stop processing if break value == total_subrecordsizes.
#if 0
      sprintf(tmp_s,"xxxx global_subrecordsize = %i",global_subrecordsize);
      printblock_add_loc(pb,tmp_s,loc);
      sprintf(tmp_s,"xxxx total_subrecordsize = %i",total_subrecordsize);
      printblock_add_loc(pb,tmp_s,loc);
      sprintf(tmp_s,"xxxx object intvalue = %i",object->intvalue);
      printblock_add_loc(pb,tmp_s,loc);
#endif
      if (total_subrecordsize == global_subrecordsize) {
	i = block->numobjects;
      }
    } else if (object->type == C_BLOCKOBJECTTYPE_IFSIZE) {
      if (global_subrecordsize == object->intvalue) {
	// Do nothing because this is the correction section.
      } else {
	// Skip this section. Until next ifsize or the end.
	done = 0;
	do {
	  i++;
	  if (i < block->numobjects) {
	    object = block->objects[i];
	    if (object->type == C_BLOCKOBJECTTYPE_IFSIZE) {
	      if (global_subrecordsize == object->intvalue) {
		// Found correct section.
		done = 2;
	      } else {
		// Continue skipping.
	      }
	    } else {
	      // Continue skipping.
	    }
	  } else {
	    done = 1; // i = block->numobjects
	  }
	} while (done == 0);
	if (done == 2) {
	  // Continue from the next.
	  // i++; // Not needed.
	}
      }
    } else if (object->type == C_BLOCKOBJECTTYPE_GMSTDATA) {
      // Instead of branching based on first char of last EDID,
      // we have special type for GMST/DATA.
      // We need special types for MODT and the like in any case.
      // } else if (object->type == C_BLOCKOBJECTTYPE_IFEDID) {
      if (global_last_edid[0] == 'f') {
	f = buffer_read_float(b);
	sprintf(tmp_s,"%s = %f",object->name,f);
	printblock_add_loc(pb,tmp_s,loc);
	object_size = 4;
      } else if (global_last_edid[0] == 'i') {
	n = buffer_read_int(b);
	sprintf(tmp_s,"%s = %i",object->name,n);
	printblock_add_loc(pb,tmp_s,loc);
	object_size = 4;
      } else if (global_last_edid[0] == 's') {
	s = buffer_read_nstring(b,global_subrecordsize);
	sprintf(tmp_s,"%s = %s",object->name,s);
	printblock_add_loc(pb,tmp_s,loc);
	free(s);
	object_size = global_subrecordsize;
      }
    } else if (object->type == C_BLOCKOBJECTTYPE_SGMSTDATA) {
      // Instead of branching based on first char of last EDID,
      // we have special type for GMST/DATA.
      // We need special types for MODT and the like in any case.
      // } else if (object->type == C_BLOCKOBJECTTYPE_IFEDID) {
      if (global_last_edid[0] == 'f') {
	f = buffer_read_float(b);
	sprintf(tmp_s,"%s = %f",object->name,f);
	printblock_add_loc(pb,tmp_s,loc);
	object_size = 4;
      } else if (global_last_edid[0] == 'i') {
	n = buffer_read_int(b);
	sprintf(tmp_s,"%s = %i",object->name,n);
	printblock_add_loc(pb,tmp_s,loc);
	object_size = 4;
      } else if (global_last_edid[0] == 's') {
	n = buffer_read_int(b);
	sprintf(tmp_s,"%s = %i",object->name,n);
	printblock_add_loc(pb,tmp_s,loc);
	object_size = 4;
      }
    } else if (object->type == C_BLOCKOBJECTTYPE_REPEAT) {
      // XXXX repeat has parameter "number of bytes" which is not used
      // Repeat 0 or more times
      if (global_subrecordsize == 0) {
	i = block->numobjects;
      } else {
	repeatpos = i;
	// sprintf(tmp_s,"xxxx repeatpos = %i",repeatpos);
	// printblock_add_loc(pb,tmp_s,loc);
	// Repeated block may not contain intarray, nstring, gmstdata.
      }
    } else if (object->type == C_BLOCKOBJECTTYPE_INTREPEAT) {
      // repeat 2 numitems

    } else if (object->type == C_BLOCKOBJECTTYPE_SETLOC) {
      global_loc = buffer_getloc(b);
    } else if (object->type == C_BLOCKOBJECTTYPE_GETLOC) {
      buffer_setloc(b,global_loc);
    } else if (object->type == C_BLOCKOBJECTTYPE_NIFZSTRING) {
      s = buffer_read_nstring(b,global_subrecordsize);
      for (j = 0; j < global_subrecordsize-1; j++) { // Excluding the last 0.
        if (s[j] == '\0') s[j] = ' ';
      }
      sprintf(tmp_s,"%s = %s",object->name,s);
      printblock_add_loc(pb,tmp_s,loc);
      free(s);
      // XXXX fails if nstring is only a part of the subrecord
      // object_size = ?
      object_size = global_subrecordsize;
    }


    total_subrecordsize += object_size;
    if (i == block->numobjects - 1) {
      if (repeatpos >= 0) {
#if 0
	sprintf(tmp_s,"xxxx global_subrecordsize = %i",global_subrecordsize);
	printblock_add_loc(pb,tmp_s,loc);
	sprintf(tmp_s,"xxxx total_subrecordsize = %i",total_subrecordsize);
	printblock_add_loc(pb,tmp_s,loc);
	sprintf(tmp_s,"xxxx repeatpos = %i",repeatpos);
	printblock_add_loc(pb,tmp_s,loc);
#endif
	if (total_subrecordsize < global_subrecordsize) {
	  i = repeatpos;
	}
      }
    }

  }
}


int blocklist_isdefined(char *blockname)
{
  int i,k;

  k = -1;
  for (i = 0; i < global_blocklist.numblocks; i++) {
    if (strcmp(global_blocklist.blocks[i]->name,blockname) == 0) {
      k = i;
    }
  }

  if (k == -1) {
    return 0;
  }

  return 1;
}


void block_import(char *blockname)
{
  int i,j,k;
  ty_block *block;
  ty_blockobject *object;
  int n;
  char *s;
  float f;
  int m;
  int done;
  int repeatpos;
  int isformid;
  int foundformid;
  char *type;
  int saveloc;

  k = -1;
  for (i = 0; i < global_blocklist.numblocks; i++) {
    if (strcmp(global_blocklist.blocks[i]->name,blockname) == 0) {
      k = i;
    }
  }
  if (k == -1) {
    fprintf(stderr,"import: block %s has not been defined\n",blockname);
    return;
  }

  block = global_blocklist.blocks[k];
  for (i = 0; i < block->numobjects; i++) {
    // Copy object to the current block.
    f_import(block->objects[i]);
  }
}



// int global_cursorlocation = 0;

void print_printblock(void *pb)
{
  ty_entry *p;
  int i;
  int k;
  int y;
  int done;
  int r,rr;
  int h,v;
  char *s;
  int o; // Line owner is the buffer location to start of the record.
  int *yo; // Owners of whole display.
  int co; // Owner at cursor.
  int cy;
  int bo1,bo2;
  char fc;

  getmaxyx(stdscr,yscreensize,xscreensize);

  // Owners of the whole display.
  yo = (int *)malloc(yscreensize*sizeof(int));

  // erase();
  clear();

  // Test cursor position.
  r = move(pi.pickindex-pi.printoffset,0);
  if (r == ERR) {
    if (pi.pickindex-pi.printoffset < 0) {
      // printoffset = pickindex;
      // printoffset = printoffset - (pickindex-printoffset)/2;
      pi.printoffset = pi.printoffset - yscreensize/2;
      if (pi.printoffset < 0) pi.printoffset = 0;
    } else {
      // printoffset = printoffset + (pickindex-printoffset)/2;
      pi.printoffset = pi.printoffset + yscreensize/2;
    }
  }

  // Cursor row. Line owner. Range of lines owned by the same owner.
  cy = pi.pickindex-pi.printoffset;
  co = -1;
  y = 0;
  // XXXX k < min(printblock_get_numlines(pb), yscreensize)
  for (k = pi.printoffset; k < printblock_get_numlines(pb); k++) {
    r = move(y,0);
    if (r != ERR) {
      o = printblock_get_location(pb,k);
      yo[y] = o;
      if (y == cy) {
	co = o;
	pi.cursorlocation = co;
      }
      y++;
    }
  }

  if (co == -1) {
    fprintf(stderr,"co == -1\n");
  }

#if 0
  bo1 = has_colors();
  bo2 = can_change_color();
  endwin();
  for (y = 0; y < yscreensize; y++) {
    printf("yo[%i] = %x\n",y,yo[y]);
  }
  printf("co = %x\n",co);
  printf("has_colors = %i\n",bo1);
  printf("can_change_color = %i\n",bo2);
  exit(-1);
#endif

  y = 0;
  for (k = pi.printoffset; k < printblock_get_numlines(pb); k++) {
    r = move(y,0);
    if (r != ERR) {
      s = printblock_get_line(pb,k);
      // o = printblock_get_location(pb,k);
#if 0
      // What is simplest way to change the active text color?!
      // Had to give up; too difficult, too messy system, man pages poor?
      if (yo[y] == co) {
	attron(A_COLOR);
	attrset (A_COLOR|A_CHARTEXT|A_BOLD);
	attrset (A_COLOR);
	color_set(3,NULL);
      } else {
	// COLOR_WHITE;
	attron(A_COLOR);
	attrset (A_COLOR|A_CHARTEXT|A_BOLD);
	attrset (A_COLOR);
	color_set(4,NULL);
      }
#endif
      if (yo[y] == co) {
	fc = '|';
      } else {
	fc = ' ';
      }
      // printf("%s\n",s);
      tmpchs[0] = fc;
      for (i = 0; i < strlen(s); i++) {
	tmpchs[i+1] = s[i];
      }
      tmpchs[strlen(s)+1] = 0;
      rr = addchstr(tmpchs);
      y++;
    }
  }

  // Errors.
  y = 0;
  for (k = 0; k < printblock_get_numerrors(pb); k++) {
    r = move(y,80);
    if (r != ERR) {
      s = printblock_get_error(pb,k);
      if (s != NULL) {
	for (i = 0; i < strlen(s); i++) {
	  tmpchs[i] = s[i];
	}
	tmpchs[strlen(s)] = 0;
	rr = addchstr(tmpchs);
	y++;
      }
    }
  }

  r = move(pi.pickindex-pi.printoffset,cursorx);
  if (r == ERR) {
    // printoffset++;
    // XXXX we should call printlist() here!!
    // XXXX Perhaps we should maintain the window size in variables.
  }

  refresh();
}


char scan_s1[2048];
char scan_s2[2048];
char scan_s3[2048];


void createformatdef()
{
  FILE *fp;

  f_init();

#if 0
  f_block("recgroup");
  f_string4("type");

  f_block("record");
  f_string4("type");
  f_int("size");
  f_flags32("flags1");
  f_flags_bit(19,"iscompressed");
  f_uint("formid");
  f_flags32("flags2");

  f_block("subrecord");
  f_string4("type");
  f_ushort("size");

  f_block("group");
  f_string4("type");
  f_int("size");
  f_string4("label");
  // f_int("data");
  f_int("datatype");
  f_int("stamp");
#endif


  if (strcmp(global_progname,"obrowser") == 0) {
    fp = fopen("oformatdef","r");
    global_headersize = 20;
  } else if (strcmp(global_progname,"./obrowser") == 0) {
    fp = fopen("oformatdef","r");
    global_headersize = 20;
  } else if (strcmp(global_progname,"sbrowser") == 0) {
    fp = fopen("sformatdef","r");
    global_headersize = 24;
  } else if (strcmp(global_progname,"./sbrowser") == 0) {
    fp = fopen("sformatdef","r");
    global_headersize = 24;
  } else {
    fprintf(stderr,"unknown progname\n");
    exit(-1);
  }

  if (fp == NULL) {
    fprintf(stderr,"failed to open format definition file\n");
    exit(-1);
  }

  // Splitted fscanf so that we may have variable number of parameters.
  // while (fscanf(fp,"%s %s\n",scan_s1,scan_s2) == 2) {
  while (fscanf(fp,"%s",scan_s1) == 1) {
    if (strcmp(scan_s1,"import") == 0) {
      fscanf(fp,"%s\n",scan_s2);
#if 1
      // XXXX FIX
      // XXXX We want make the import object, not copy objects
      // XXXX from the imported block.
      block_import(scan_s2);
#else
      if (strcmp(scan_s2,"subrecord") == 0) {
	f_string4("type");
	f_ushort("size");
      } else if (strcmp(scan_s2,"obnd") == 0) {
	f_short("Min_X");
	f_short("Min_Y");
	f_short("Min_Z");
	f_short("Max_X");
	f_short("Max_Y");
	f_short("Max_Z");
      } else if (strcmp(scan_s2,"schr") == 0) {
	f_int("unknown");
	f_int("Count_SCRO_SCRV");
	f_int("Compiled_Script_Size");
	f_int("Count_Script_variables");
	f_short("Script_Type");
	f_short("unknown");
      } else if (strcmp(scan_s2,"ctda") == 0) {
	f_flags8("flags");
	f_ubyte("unused");
	f_ubyte("unused");
	f_ubyte("unused");
	f_setloc("float");
	f_float("Value");
	f_getloc("uint");
	f_uint("Global_FormID");
	f_int("Function_ID");
	f_int("Parameter1");
	f_int("Parameter2");
	f_int("unknown");
      } else if (strcmp(scan_s2,"ctdt") == 0) {
	f_flags8("flags");
	f_ubyte("unused");
	f_ubyte("unused");
	f_ubyte("unused");
	f_setloc("float");
	f_float("Value");
	f_getloc("uint");
	f_uint("Global_FormID");
	f_int("Function_ID");
	f_int("Parameter1");
	f_int("Parameter2");
	// f_int("unknown"); // only in CTDA
      } else if (strcmp(scan_s2,"sctx") == 0) {
	f_nstring("Script");
      } else if (strcmp(scan_s2,"scro") == 0) {
	f_uint("Script_Object_FormID");
      } else if (strcmp(scan_s2,"slsd") == 0) {
	f_int("Script_Variable_Index");
	f_int("unused");
	f_int("unknown");
	f_int("unknown");
	f_byte("Script_Variable_Type");
	f_byte("unused");
	f_byte("unused");
	f_byte("unused");
	f_setloc("float");
	f_float("float");
	f_getloc("uint");
	f_uint("uint");
      } else if (strcmp(scan_s2,"efit") == 0) {
	f_string4("Effect");
	f_int("Magnitude");
	f_int("Area");
	f_int("Duration");
	f_int("Range");
	f_int("ActorVal");
      } else if (strcmp(scan_s2,"scit") == 0) {
	f_ifsize(4);
	f_uint("Script_FormID");
	f_ifsize(12);
	f_uint("Script_FormID");
	f_int("School");
	f_string4("Visual_Effect");
	f_ifsize(16);
	f_uint("Script_FormID");
	f_int("School");
	f_string4("Visual_Effect");
	f_flags8("flags");
	f_ubyte("unused");
	f_ubyte("unused");
	f_ubyte("unused");
      } else {
	fprintf(stderr,"unknown import %s\n",scan_s2);
      }
#endif
    } else if (strcmp(scan_s1,"block") == 0) {
      fscanf(fp,"%s\n",scan_s2);
      f_block(scan_s2);
    } else if (strcmp(scan_s1,"string4") == 0) {
      fscanf(fp,"%s\n",scan_s2);
      f_string4(scan_s2);
    } else if (strcmp(scan_s1,"int") == 0) {
      fscanf(fp,"%s\n",scan_s2);
      f_int(scan_s2);
    } else if (strcmp(scan_s1,"uint") == 0) {
      fscanf(fp,"%s\n",scan_s2);
      f_uint(scan_s2);
    } else if (strcmp(scan_s1,"short") == 0) {
      fscanf(fp,"%s\n",scan_s2);
      f_short(scan_s2);
    } else if (strcmp(scan_s1,"ushort") == 0) {
      fscanf(fp,"%s\n",scan_s2);
      f_ushort(scan_s2);
    } else if (strcmp(scan_s1,"byte") == 0) {
      fscanf(fp,"%s\n",scan_s2);
      f_byte(scan_s2);
    } else if (strcmp(scan_s1,"ubyte") == 0) {
      fscanf(fp,"%s\n",scan_s2);
      f_ubyte(scan_s2);
    } else if (strcmp(scan_s1,"flags32") == 0) {
      fscanf(fp,"%s\n",scan_s2);
      f_flags32(scan_s2);
    } else if (strcmp(scan_s1,"flags16") == 0) {
      fscanf(fp,"%s\n",scan_s2);
      f_flags16(scan_s2);
    } else if (strcmp(scan_s1,"flags8") == 0) {
      fscanf(fp,"%s\n",scan_s2);
      f_flags8(scan_s2);
    } else if (strcmp(scan_s1,"flag") == 0) {
      fscanf(fp,"%s",scan_s2);
      fscanf(fp,"%s\n",scan_s3);
      f_flags_bit(atoi(scan_s2),scan_s3);
    } else if (strcmp(scan_s1,"float") == 0) {
      fscanf(fp,"%s\n",scan_s2);
      f_float(scan_s2);
    } else if (strcmp(scan_s1,"nstring") == 0) {
      fscanf(fp,"%s\n",scan_s2);
      f_nstring(scan_s2);
    } else if (strcmp(scan_s1,"intarray") == 0) {
      fscanf(fp,"%s\n",scan_s2);
      f_intarray(scan_s2);
    } else if (strcmp(scan_s1,"break") == 0) {
      fscanf(fp,"%s\n",scan_s2);
      f_break(atoi(scan_s2));
    } else if (strcmp(scan_s1,"ifsize") == 0) {
      fscanf(fp,"%s\n",scan_s2);
      f_ifsize(atoi(scan_s2));
    } else if (strcmp(scan_s1,"gmstdata") == 0) {
      fscanf(fp,"%s\n",scan_s2);
      f_gmstdata(scan_s2);
    } else if (strcmp(scan_s1,"sgmstdata") == 0) {
      fscanf(fp,"%s\n",scan_s2);
      f_sgmstdata(scan_s2);
    } else if (strcmp(scan_s1,"repeat") == 0) {
      fscanf(fp,"%s\n",scan_s2);
      f_repeat(scan_s2);
    } else if (strcmp(scan_s1,"setloc") == 0) {
      fscanf(fp,"%s\n",scan_s2);
      f_setloc(scan_s2);
    } else if (strcmp(scan_s1,"getloc") == 0) {
      fscanf(fp,"%s\n",scan_s2);
      f_getloc(scan_s2);
    } else if (strcmp(scan_s1,"nifzstring") == 0) {
      // CREA/NIFZ
      fscanf(fp,"%s\n",scan_s2);
      f_nifzstring(scan_s2);
    } else {
      fprintf(stderr,"unknown format definition command %s\n",scan_s1);
    }
  }

  fclose(fp);




#if 0
  // XXXX new group definition:
  f_block("group");
  f_string4("type");
  f_int("size");
  f_saveloc(1);
  f_int("data"); // Read or skip.
  f_int("datatype");
  f_saveloc(2);
  f_loadloc(1);
  // XXXX Interpret "data" correctly here.
  f_switch("datatype");
  f_case_int(0);
  // XXXX What name should be used?
  f_string4("label");
  f_endcase();
  f_case_int(1);
  // XXXX What name should be used?
  f_int("data");
  f_endcase();
  f_case_int(2);
  // XXXX What name should be used?
  f_int("data");
  f_endcase();
  f_case_int(4);
  f_short("y");
  f_short("x");
  f_endcase();
  f_endswitch();
  f_loadloc(2);
  f_int("stamp");

#endif


}

void createconditionfunctiondef()
{
  FILE *fp;

  cf_init();

  fp = fopen("conditionfunctions","r");
  if (fp == NULL) {
    fprintf(stderr,"failed to open format definition file formatdef\n");
    exit(-1);
  }

  while (fscanf(fp,"%s %s %[^\n]\n",scan_s1,scan_s2,scan_s3) == 3) {
    // Keep this print for diffing the correctness of the scan.
    // printf("%3s %s %s\n",scan_s1,scan_s2,scan_s3);
    cf_add(scan_s1,scan_s2,scan_s3);
  }

  fclose(fp);
  // exit(1);
}



void create_global_records(void *b)
{
  int loc;
  char *type;
  unsigned int formid;
  int size;

  // Advance through every record linearly and save their FormID
  // and location.
  global_numrecords = 0;
  buffer_setloc(b,0);
  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    // buffer_block_print(b,"recgroup");
    buffer_setloc(b,loc);
    type = buffer_block_get_value_string4(b,"recgroup","type");
    if (strcmp(type,"GRUP") == 0) {
      buffer_setloc(b,loc);
      // size = buffer_block_get_value_int(b,"group","size");
      // buffer_setloc(b,loc+size);
      buffer_setloc(b,loc+global_headersize); // Skip the header of the group.
      // XXXX Later: Save the hierarchical path as well.
    } else {
      buffer_setloc(b,loc);
      formid = buffer_block_get_value_uint(b,"record","FormID");

      global_records[global_numrecords].loc = loc;
      global_records[global_numrecords].formid = formid;
      global_numrecords++;

      buffer_setloc(b,loc);
      size = buffer_block_get_value_int(b,"record","size");
      buffer_setloc(b,loc+global_headersize+size);
    }
    free(type);
  }
  buffer_setloc(b,0);

#if 0
  for (i = 0; i < global_numrecords; i++) {
    printf("formid / loc = %i / %i\n",global_records[i].formid,global_records[i].loc);
  }
  exit(-1);
#endif

}

void create_print_insidetype0()
{
  int loc;
  char *type;
  int size;

  if (pb != NULL) {
    printblock_delete(pb);
    pb = NULL;
  }
  pb = printblock_new();

  buffer_setloc(b,0);
  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    buffer_setloc(b,loc);
    type = buffer_block_get_value_string4(b,"recgroup","type");
    if (strcmp(type,"GRUP") == 0) {
      buffer_setloc(b,loc);
      buffer_block_print_pb_loc(b,"group",pb,loc);
      buffer_setloc(b,loc);
      size = buffer_block_get_value_int(b,"group","size");
      buffer_setloc(b,loc+size);
    } else {
      // XXXX if printinfostack_n == 1 then print one line summaries
      if (printinfostack_n == 1000) { // XXXX not in use
	// XXXX Enter the record to obtain needed information.
	// (1) Open the record.
	// (2) Parse all subrecords that matches the list.
	// (3) Read values for the wanted entries.
	// For each subrecord entry, offer strings such as
	// "REFR/XESP Enable_Parent_Ref_FormID"
	// for comparison.
	// XXXX TODO: Unique variable names within a subrecord.

	// XXXX The above information can be checked from formatdef.
	// XXXX Multiple same entries, like CNTO? NPC_ male and female?

	buffer_setloc(b,loc);
	size = buffer_block_get_value_int(b,"record","size");
	buffer_setloc(b,loc + global_headersize + size);
      } else {
	buffer_setloc(b,loc);
	buffer_block_print_pb_loc(b,"record",pb,loc);
	buffer_setloc(b,loc);
	size = buffer_block_get_value_int(b,"record","size");
	buffer_setloc(b,loc + global_headersize + size);
      }
    }
    free(type);
  }
  buffer_setloc(b,0);

}

// XXXX Modify so that subrecords are processed in their own buffer.
void create_print_insidetype1()
{
  int loc;
  char *subtype;
  int size;
  int xxxxsubrecordsize;
  void *b2;
  int subcount;

  if (pb != NULL) {
    printblock_delete(pb);
    pb = NULL;
  }
  pb = printblock_new();

  xxxxsubrecordsize = -1;
  subcount = 0;

  buffer_setloc(b,0);
  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    buffer_setloc(b,loc);
    subtype = buffer_block_get_value_string4(b,"subrecord","type");
    sprintf(tmp_s,"%s/%s",pi.recordtype,subtype);
    if (blocklist_isdefined(tmp_s) == 1) {
      buffer_setloc(b,loc);
      size = buffer_block_get_value_ushort(b,"subrecord","size");
      if (xxxxsubrecordsize > 0) {
	global_subrecordsize = xxxxsubrecordsize;
	xxxxsubrecordsize = -1;
      } else {
	global_subrecordsize = size;
      }

      // XXXX Has Skyrim more XXXX subrecords? Oblivion has only WRLD/XXXX.
#if 1
      // Note: We have to have WRLD/XXXX defined. This just simplifies
      // the code here because one code works with all XXXX subrecords.
      if (strcmp(subtype,"XXXX") == 0) {
	buffer_setloc(b,loc);
	xxxxsubrecordsize = buffer_block_get_value_int(b,"XXXX","xxxxsize");
      }
#else
      if (strcmp(tmp_s,"WRLD/XXXX") == 0) {
	buffer_setloc(b,loc);
	xxxxsubrecordsize = buffer_block_get_value_int(b,"WRLD/XXXX","xxxxsize");
      }
#endif
      buffer_setloc(b,loc);
      // XXXX Skyrim CLAS fails here because Oblivion has longer
      // XXXX record. Verify sizes.
      // XXXX Separate parsing and printing.
      b2 = buffer_new(buffer_getbuf_atloc(b),6+global_subrecordsize);
      // buffer_block_print_pb_loc(b,tmp_s,pb,loc);
      buffer_block_print_pb_loc(b2,tmp_s,pb,loc);
      buffer_free(b2);
      buffer_setloc(b,loc+6+global_subrecordsize);
    } else {
      // Block has not been defined.
      buffer_setloc(b,loc);
      buffer_block_print_pb_loc(b,"subrecord",pb,loc);
      buffer_setloc(b,loc);
      if (xxxxsubrecordsize > 0) {
	size = xxxxsubrecordsize;
	xxxxsubrecordsize = -1;
      } else {
	size = buffer_block_get_value_ushort(b,"subrecord","size");
      }
      buffer_setloc(b,loc+6+size);
    }
    free(subtype);
    subcount++;
  }
  buffer_setloc(b,0);
}

void create_print_insidetype1_old()
{
  int loc;
  char *subtype;
  int size;
  int xxxxsubrecordsize;

  if (pb != NULL) {
    printblock_delete(pb);
    pb = NULL;
  }
  pb = printblock_new();

  xxxxsubrecordsize = -1;

  buffer_setloc(b,0);
  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    buffer_setloc(b,loc);
    subtype = buffer_block_get_value_string4(b,"subrecord","type");
    sprintf(tmp_s,"%s/%s",pi.recordtype,subtype);
    if (blocklist_isdefined(tmp_s) == 1) {
      buffer_setloc(b,loc);
      size = buffer_block_get_value_ushort(b,"subrecord","size");
      if (xxxxsubrecordsize > 0) {
	global_subrecordsize = xxxxsubrecordsize;
	xxxxsubrecordsize = -1;
      } else {
	global_subrecordsize = size;
      }

      // XXXX Has Skyrim more XXXX subrecords? Oblivion has only WRLD/XXXX.
      if (strcmp(tmp_s,"WRLD/XXXX") == 0) {
	buffer_setloc(b,loc);
	xxxxsubrecordsize = buffer_block_get_value_int(b,"WRLD/XXXX","xxxxsize");
      }
      buffer_setloc(b,loc);
      // XXXX Skyrim CLAS fails here because Oblivion has longer
      // XXXX record. Verify sizes.
      // XXXX Separate parsing and printing.
      buffer_block_print_pb_loc(b,tmp_s,pb,loc);
      // buffer_setloc(b,loc+6+size);
    } else {
      buffer_setloc(b,loc);
      buffer_block_print_pb_loc(b,"subrecord",pb,loc);
      buffer_setloc(b,loc);
      if (xxxxsubrecordsize > 0) {
	size = xxxxsubrecordsize;
	xxxxsubrecordsize = -1;
      } else {
	size = buffer_block_get_value_ushort(b,"subrecord","size");
      }
      buffer_setloc(b,loc+6+size);
    }
    free(subtype);
  }
  buffer_setloc(b,0);
}

void create_print_insidetype1_returntest()
{
  int loc;
  char *subtype;
  int size;
  int xxxxsubrecordsize;

  fprintf(stderr,"t1\n"); sleep(6);
  if (pb != NULL) {
  fprintf(stderr,"t2\n"); sleep(6);
    printblock_delete(pb);
  fprintf(stderr,"t3\n"); sleep(6);
    pb = NULL;
  }
  fprintf(stderr,"t4\n"); sleep(6);
  pb = printblock_new();
  fprintf(stderr,"t5\n"); sleep(6);

  xxxxsubrecordsize = -1;

  fprintf(stderr,"t6\n"); sleep(6);
  buffer_setloc(b,0);
  fprintf(stderr,"t7\n"); sleep(6);
  while (buffer_eof(b) != 1) {
  fprintf(stderr,"t8\n"); sleep(6);
    loc = buffer_getloc(b);
    buffer_setloc(b,loc);
  fprintf(stderr,"t9\n"); sleep(6);
  // fprintf(stderr,"using b %x / %x\n",b,buffer_getbuf(b)); sleep(6);
  // subtype = buffer_block_get_value_string4(b,"subrecord","type");
    subtype = buffer_block_get_value_string4_returntest(b,"subrecord","type");
  fprintf(stderr,"t10\n"); sleep(6);
    sprintf(tmp_s,"%s/%s",pi.recordtype,subtype);
  fprintf(stderr,"t11\n"); sleep(6);
    if (blocklist_isdefined(tmp_s) == 1) {
  fprintf(stderr,"t12\n"); sleep(6);
      buffer_setloc(b,loc);
      if (xxxxsubrecordsize > 0) {
  fprintf(stderr,"t13\n"); sleep(6);
	global_subrecordsize = xxxxsubrecordsize;
	xxxxsubrecordsize = -1;
      } else {
  fprintf(stderr,"t14\n"); sleep(6);
	global_subrecordsize = buffer_block_get_value_ushort(b,"subrecord","size");
      }
      if (strcmp(tmp_s,"WRLD/XXXX") == 0) {
  fprintf(stderr,"t15\n"); sleep(6);
	buffer_setloc(b,loc);
	xxxxsubrecordsize = buffer_block_get_value_int(b,"WRLD/XXXX","xxxxsize");
      }
  fprintf(stderr,"t16\n"); sleep(6);
      buffer_setloc(b,loc);
      buffer_block_print_pb_loc(b,tmp_s,pb,loc);
  fprintf(stderr,"t17\n"); sleep(6);
    } else {
  fprintf(stderr,"t18\n"); sleep(6);
      buffer_setloc(b,loc);
      buffer_block_print_pb_loc(b,"subrecord",pb,loc);
      buffer_setloc(b,loc);
  fprintf(stderr,"t19\n"); sleep(6);
      if (xxxxsubrecordsize > 0) {
  fprintf(stderr,"t20\n"); sleep(6);
	size = xxxxsubrecordsize;
	xxxxsubrecordsize = -1;
      } else {
  fprintf(stderr,"t21\n"); sleep(6);
	size = buffer_block_get_value_ushort(b,"subrecord","size");
      }
  fprintf(stderr,"t22\n"); sleep(6);
      buffer_setloc(b,loc+6+size);
    }
  fprintf(stderr,"t23\n"); sleep(6);
    free(subtype);
  }
  fprintf(stderr,"t24\n"); sleep(6);
  buffer_setloc(b,0);
  fprintf(stderr,"t25\n"); sleep(6);
}


// What if entering cannot be performed? We need to pop pi from
// stack in any case.
// Uses globals b, pi.
void check_printinfo_insidetype0(int cursorlocation)
{
  int loc;
  char *type;
  int size;

  // Enter to a group or a record.
  loc = cursorlocation;
  buffer_setloc(b,loc);
  type = buffer_block_get_value_string4(b,"recgroup","type");
  if (strcmp(type,"GRUP") == 0) {
    buffer_setloc(b,loc);
    size = buffer_block_get_value_int(b,"group","size") - global_headersize;
    pi.insidetype = 0; // Group.
    pi.iscompressed = 0;
  } else {
    buffer_setloc(b,loc);
    size = buffer_block_get_value_int(b,"record","size");
    buffer_setloc(b,loc);
    pi.iscompressed = 0x40000 & buffer_block_get_value_flags(b,"record","flags1");
    if (pi.iscompressed != 0) {
      pi.iscompressed = 1;
    }
    buffer_setloc(b,loc);
    pi.insidetype = 1; // Record.
  }
  buffer_setloc(b,loc);

  sprintf(pi.recordtype,"%s",type);
  free(type);

  pi.loc = 0; // Always extract the printed data to its own buffer.
  pi.cursorlocation = 0;
  pi.pickindex = 0;
  pi.printoffset = 0;
  pi.uncompbuffer = NULL;
  pi.size = size;

}


void uncompress_record()
{
  unsigned char *buffer;
  int buflen;
  int nuncomp,nin,nout,err;
  int ndata;
  unsigned char *obuffer;

  // Uncompress and replace b.
  if ((pi.iscompressed == 1) && (pi.uncompbuffer == NULL)) {
    nuncomp = buffer_read_int(b);
    buffer = buffer_getbuf(b);
    nin = pi.size-4;
    nout = nuncomp + 10;
    // printf("numcomp = %i, nout = %i\n",nuncomp,nout);
    obuffer = (unsigned char *)malloc(nout*sizeof(unsigned char));
    err = uncompress(obuffer,(uLongf *)(&nout),&(buffer[buffer_getloc(b)]),nin);
    if (err == Z_OK) {
      // printf("err = OK\n");
    } else if (err == Z_MEM_ERROR) {
      fprintf(stderr,"err = MEM\n");
    } else if (err == Z_BUF_ERROR) {
      fprintf(stderr,"err = BUF\n");
    } else if (err == Z_DATA_ERROR) {
      fprintf(stderr,"err = DATA\n");
    } else {
      fprintf(stderr,"Unknown error\n");
    }
    if (nout != nuncomp) {
      fprintf(stderr,"Uncompressed data is of wrong size\n");
      exit(-1);
    }
    pi.uncompbuffer = obuffer;
    pi.compb = b;
    b = buffer_new(obuffer,(int)nout);
    pi.b = b;
    pi.size = (int)nout;
  }
}

int main(int ac, char **av)
{
  FILE *fp;
  void *m;
  // void *b;
  void *b2;
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
  void *format_genrecord;
  void *format_group;
  int size;
  char *type;
  int insidetype;
  int enterinsidetype;
  char *subtype;
  int xxxxsubrecordsize;
  void *btmp;
  unsigned char *obuffer = NULL;
  unsigned int flags;
  int nuncomp,nin,nout,err;
  int ndata;
  int iscompressed;
  unsigned int formid;
  int formidindex;
  int formidloc;
  char *s;
  int cursorlocation;
  int k;

#if 0
  for (i = 0; i < strlen(av[1]); i++) {
    tmpchs[i] = (av[1])[i];
  }
  tmpchs[strlen(av[1])] = 0;
#endif

  if (ac < 1) {
    fprintf(stderr,"Usage: espbrowser <file>\n");
    exit(-1);
  }

  global_progname = av[0];

  gf = fopen("log","w");
  if (gf == NULL) {
    fprintf(stderr,"Cannot open log file\n");
    exit(-1);
  }

  createformatdef();

  createconditionfunctiondef();


  m = mmapfile_open_r(av[1]);
  buffer = mmapfile_getbuf(m);
  buflen = mmapfile_getsize(m);

  b = buffer_new(buffer,buflen);
  rootb = buffer_new(buffer,buflen); // We need separate ty_buffer.

  create_global_records(b);

  // We may want a hierarchical structure to hold the record
  // locations. So that, records can be advanced backwards.
  // Maybe later.

  printinfostack_n = 0;

  // Initial print for the UI.
  printinfo_init0();
  // pi.b = b;
  create_print_insidetype0();

  // printblock_print(pb);

  numlist = 0;
  cursorx = 0;



  initscr();
  start_color();
  // init_pair (1, 5, 0);
  // init_pair (2, 4, 0);
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

  print_printblock(pb);

  // File position = 0 at the start.

  // List is created at print time.

  // list[numlist] = create_unknown(buffer_getloc(b),buffer_getlen(b));
  // list[numlist] = strdup("unknown");
  // numlist++;
  // printlist();

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

    if (key == (int)'q') {
      done = 1;
    }

    if (key == (int)'t') {
      createformatdef();
    }

    // Move between items.
    // pickindex = 0 at start.
    if (key == KEY_UP) {
      if (pi.pickindex > 0) pi.pickindex--;

      print_printblock(pb);
    }

    if (key == KEY_DOWN) {
      numlist = printblock_get_numlines(pb);
      if (pi.pickindex < numlist-1) pi.pickindex++;

      print_printblock(pb);
    }

    if (key == KEY_PPAGE) {
      getmaxyx(stdscr,yscreensize,xscreensize);
      pi.pickindex -= yscreensize/2;
      if (pi.pickindex < 0) pi.pickindex = 0;

      print_printblock(pb);
    }

    if (key == KEY_NPAGE) {
      getmaxyx(stdscr,yscreensize,xscreensize);
      numlist = printblock_get_numlines(pb);
      pi.pickindex += yscreensize/2;
      // XXXX assumes that a list entry is one row
      if (pi.pickindex > numlist-1) pi.pickindex = numlist-1;

      print_printblock(pb);
    }

    if (key == 13) {

      // insidetype = 0 when we are inside a group (or at root level)
      // insidetype = 0 we find groups and records
      // insidetype = 1 when we are inside a record
      // insidetype = 1 we find subrecords
      // insidetype = 2 when we are inside a subrecord (decoder mode)

      // endwin();
      // printf("XXXX %i %i %i %i\n",pi.cursorlocation,buffer_getloc(b),buffer_getlen(b),pi.insidetype);
      // return 1;

      if (pi.insidetype == 0) {
	// Enter to groups or to records.
	printinfo_copy(&pi,&(printinfostack[printinfostack_n]));
	printinfostack_n++;

	cursorlocation = pi.cursorlocation;
	printinfo_init0();
	check_printinfo_insidetype0(cursorlocation);

	buffer_setloc(b,cursorlocation);
	buffer_skip_bytes(b,global_headersize); // Header should be defined in formatdef.
	b2 = buffer_new(buffer_getbuf_atloc(b),pi.size);
	b = b2;
	pi.b = b;

	// endwin();
	// printf("XXXX %i %i %i %i %i %i\n",cursorlocation,pi.cursorlocation,buffer_getloc(b),buffer_getlen(b),pi.insidetype,pi.size);
	// return 1;

	// fprintf(stderr,"should enter to group %i %i %i\n",pi.cursorlocation,buffer_getloc(b),buffer_getlen(b));
	// fprintf(stderr,"insidetype = %i\n",pi.insidetype);
	// sleep(5);
	if (pi.insidetype == 0) {
	  // fprintf(stderr,"entered group %i %i %i\n",pi.cursorlocation,buffer_getloc(b),buffer_getlen(b));
	  // sleep(5);
	  create_print_insidetype0();
	} else if (pi.insidetype == 1) {
	  // fprintf(stderr,"1111 %i %i %i\n",pi.cursorlocation,buffer_getloc(b),buffer_getlen(b));
	  // fprintf(gf,"1111 %i %i\n",buffer_getloc(b),buffer_getlen(b));
	  // printinfo_printlog();
	  // sleep(6);
	  uncompress_record();
	  // fprintf(gf,"1111 %i %i\n",buffer_getloc(b),buffer_getlen(b));
	  // printinfo_printlog();
	  // sleep(6);
	  create_print_insidetype1();
	  // fprintf(gf,"1111 %i %i\n",buffer_getloc(b),buffer_getlen(b));
	  // printinfo_printlog();
	  // sleep(6);
	}

	pi.pickindex = 0;
	pi.printoffset = 0;
	// pi.cursorlocation ?

      } else if (pi.insidetype == 1) {
	// Enter to script or follow the FormID.

	loc = printblock_get_location(pb,pi.pickindex);
	buffer_setloc(b,loc);
	subtype = buffer_block_get_value_string4(b,"subrecord","type");

	formidindex = printblock_get_formidindex(pb,pi.pickindex);

	sprintf(tmp_s,"subtype/formidindex %s/%i",subtype,formidindex);
	printblock_add_error(pb,tmp_s);

	if (strcmp(subtype,"SCTX") == 0) {
	  buffer_setloc(b,loc);
	  size = buffer_block_get_value_ushort(b,"subrecord","size");

	  printinfo_copy(&pi,&(printinfostack[printinfostack_n]));
	  printinfostack_n++;

	  printinfo_init1();

	  buffer_setloc(b,loc);
	  buffer_skip_bytes(b,6);
	  b2 = buffer_new(buffer_getbuf_atloc(b),size);

	  b = b2;
	  pi.b = b;
	  pi.size = size;

	  if (pb != NULL) {
	    printblock_delete(pb);
	    pb = NULL;
	  }
	  pb = printblock_new();

	  s = buffer_read_nstring(b,pi.size);

	  // Divide the script to multiple lines.
	  k = strlen(s);
	  for (i = 0; i < k; i++) {
	    if (s[i] == '\n') {
	      s[i] = '\0';
	    }
	  }

	  printblock_add_loc(pb,s,0);
	  for (i = 0; i < k; i++) {
	    if (s[i] == '\0') {
	      if (i+1 < k) {
		printblock_add_loc(pb,&(s[i+1]),0);
	      }
	    }
	  }

	  free(s);

	  pi.insidetype = 2;
	  pi.pickindex = 0;
	  pi.printoffset = 0;
	  pi.iscompressed = 0;

	} else if (formidindex != -1) {
	  // Enter the FormID ref.
	  printinfo_copy(&pi,&(printinfostack[printinfostack_n]));
	  printinfostack_n++;

	  formidloc = global_records[formidindex].loc;

	  b = rootb;

	  printinfo_init0();
	  // pi.b = b;
	  check_printinfo_insidetype0(formidloc);

	  buffer_setloc(b,formidloc);
	  buffer_skip_bytes(b,global_headersize);
	  b2 = buffer_new(buffer_getbuf_atloc(b),pi.size);
	  b = b2;
	  pi.b = b;

	  if (pi.insidetype == 0) {
	    create_print_insidetype0();
	  } else if (pi.insidetype == 1) {
	    // fprintf(gf,"before ur\n");
	  // fprintf(gf,"1111 %i %i\n",buffer_getloc(b),buffer_getlen(b));
	  // printinfo_printlog();
	  // sleep(6);
	    uncompress_record();
	    // fprintf(gf,"after ur\n");
	  // fprintf(gf,"1111 %i %i\n",buffer_getloc(b),buffer_getlen(b));
	  // printinfo_printlog();
	  // sleep(6);
	    create_print_insidetype1();
	    // fprintf(gf,"after cpi1\n");
	  // fprintf(gf,"1111 %i %i\n",buffer_getloc(b),buffer_getlen(b));
	  // printinfo_printlog();
	  // sleep(6);
	  }

	  pi.pickindex = 0;
	  pi.printoffset = 0;
	  // pi.cursorlocation ?

	}

	free(subtype);


      } else if (pi.insidetype == 2) {
	// Not used for now.
      }

      print_printblock(pb);

    }


    if (key == KEY_BACKSPACE) {

      // fprintf(stderr,"g1\n");
      // sleep(5);
      if (printinfostack_n > 0) {

	// XXXX save iscompressed to stack.
	// Delete the current buffer.
      // fprintf(stderr,"g2\n");
      // sleep(5);
	if (pi.iscompressed == 1) {
      // fprintf(stderr,"g3\n");
      // sleep(5);
      // fprintf(stderr,"freeing %x\n",pi.uncompbuffer); sleep(6);
	  free(pi.uncompbuffer);
      // fprintf(stderr,"g4\n");
      // sleep(5);
	  pi.uncompbuffer = NULL;
	}
      // fprintf(stderr,"g5\n");
      // fprintf(stderr,"freeing %x (not %x)\n",b,buffer_getbuf(b)); sleep(6);
      // sleep(5);
	buffer_free(b);
      // fprintf(stderr,"g6\n");
      // sleep(5);
	pi.b = NULL;
      // fprintf(stderr,"g7\n");
      // sleep(5);

	// Delete the current printblock.
	// printblock_free(pb);
	// printblock_delete(pb);

	// Load the current buffer information from stack.
      // fprintf(stderr,"g8\n");
      // sleep(5);
	printinfostack_n--;
	printinfo_copy(&(printinfostack[printinfostack_n]),&pi);
      // fprintf(stderr,"g9\n");
      // sleep(5);
	b = pi.b;
      // fprintf(stderr,"g10\n");
      // sleep(5);
	buffer_setloc(b,0);
      // fprintf(stderr,"g11\n");
      // sleep(5);
	// global_cursorlocation = browserstack[browserstack_n].global_cursorlocation;

	// pb = printblock_new();

      // fprintf(stderr,"pi.insidetype %i\n",pi.insidetype);
      // sleep(5);
	if (pi.insidetype == 0) {
	  // fprintf(stderr,"0000 %i %i %i\n",pi.cursorlocation,buffer_getloc(b),buffer_getlen(b));
	  create_print_insidetype0();
	} else if (pi.insidetype == 1) {
	  // fprintf(stderr,"1111 %i %i\n",buffer_getloc(b),buffer_getlen(b));
	  // printinfo_print();
	  // sleep(10);
	  uncompress_record();
	  // fprintf(stderr,"after uncompress_record\n");
	  // fprintf(stderr,"1111 %i %i\n",buffer_getloc(b),buffer_getlen(b));
	  // printinfo_print();
	  // sleep(10);
	  create_print_insidetype1();
	  // create_print_insidetype1_returntest();
	  // fprintf(stderr,"after create_print_insidetype1\n");
	  // fprintf(stderr,"1111 %i %i\n",buffer_getloc(b),buffer_getlen(b));
	  // printinfo_print();
	  // sleep(10);
	}

	// pi.pickindex = 0; // NO return to the same line.
	// pi.printoffset = 0; // NO
	// pi.cursorlocation ?

	print_printblock(pb);
      }
    }


    if (key == 's') {
      // Save original uncompressed data of record or subrecord to file.

      // insidetype = 0 when we are inside a group (or at root level)
      // insidetype = 0 we find groups and records
      // insidetype = 1 when we are inside a record
      // insidetype = 1 we find subrecords
      // insidetype = 2 when we are inside a subrecord (decoder mode)

#if 0
      if (pi.insidetype == 1) {

	buffer2file(buffer_getbuf(b),buffer_getlen(b),"saved_record");

      }
#else
      if (pi.insidetype == 0) {

	cursorlocation = pi.cursorlocation;
	buffer_setloc(b,cursorlocation);
	size = buffer_block_get_value_int(b,"record","size");
	buffer_setloc(b,cursorlocation);
	buffer2file(buffer_getbuf_atloc(b),size+global_headersize,"saved_record");
      }

#endif

    }



  }

  endwin();

  fclose(gf);

  return 1;
}

