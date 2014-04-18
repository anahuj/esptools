

// Copyright 2008 Juhana Sadeharju

// This version of the espparser does not require the understanding
// of the ESP format. That is possible because data may be skipped
// based on the size entries. Specific data may be accessed and
// extracted by its path (e.g., "GRUP/GRUP/LAND/VHGT") or when
// the data is reached in a systematic file traversal.

// The parser only needs to know the "GRUP" record. All other records
// with the record-sized headers and the headers
// (of the group, the record, and the subrecord) . Only the name,
// the size, and the compressed flag.

// By executing esp_get_next() only, the whole ESP files is
// accessed in depth-first order.
// The esp_skip() skips the current record (without entering in to it).

#if 1
#define C_RECORD_HEADERSIZE 24
#else
#define C_RECORD_HEADERSIZE 20
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <zlib.h>

#include "mylib/filesdirs.h"
#include "mylib/mmapfile.h"
#include "mylib/buffer.h"


// Oblivion mod file structures.
typedef struct {
  int size;
  unsigned char *data;
} ty_oblivion_chunk;

typedef struct {
  char *name;
  int type;
  int ival;
  float fval;
  char *sval;
} ty_format_value;

typedef struct {
  char *type; // "float"
  char *name; // "Rotation X"
} ty_format_item;


// bufferstack
// locationstack if we keep the location separately % XXXX do not keep
typedef struct {
  void *m;
  void *b[20];
  int numb; // Current buffer.
  char *path; // e.g. GRUP/GRUP/LAND/VHGT
  int loc[20];
  int issubrecordlevel;
  char *grouptypes[11];
  int incompressed;
} ty_esp;

// For recursive parsing we windowize the original buffer.
void *bufferstack[128];



void printflags(unsigned int n)
{
  unsigned int k;
  int i;

  k = 0x80000000;
  for (i = 0; i < 32; i++) {
    if ((n & k) != 0) {
      printf("1");
    } else {
      printf("0");
    }
    k = k >> 1;
    if (((i % 4) == 3) && (i != 31)) {
      printf(",");
    }
  }
  printf("\n");
}

void printmodt(void *b, int n)
{
  int i,loc,m;
  float f;

  for (i = 0; i < n/4; i++) {
    loc = buffer_getloc(b);
    m = buffer_read_int(b);
    buffer_setloc(b,loc);
    f = buffer_read_float(b);
    printf("%i -- %f\n",m,f);
  }

}

int uncomp_zlib(unsigned char *inbuf, int insize, int reqoutsize,
                unsigned char **outbuf, int *outsize)
{
  unsigned char *obuf;
  int err;

  obuf = (unsigned char *)malloc(reqoutsize*sizeof(unsigned char));
  *outsize = reqoutsize;
  err = uncompress(obuf,(uLongf *)outsize,inbuf,insize);
  if (err != Z_OK) {
    free(obuf);
    if (err == Z_MEM_ERROR) {
      fprintf(stderr,"zlib err = MEM\n");
    } else if (err == Z_BUF_ERROR) {
      fprintf(stderr,"zlib err = BUF\n");
    } else if (err == Z_DATA_ERROR) {
      fprintf(stderr,"zlib err = DATA\n");
    } else {
      fprintf(stderr,"zlib unknown error\n");
    }
    return 0;
  }
  if (*outsize != reqoutsize) {
    printf("Uncompressed data is of wrong size\n");
    exit(-1);
  }

  *outbuf = obuf;

  return 1;
}


void *esp_open(char *s)
{
  ty_esp *p;
  void *m;
  unsigned char *buffer;
  int buflen;
  void *b;

  m = mmapfile_open_r(s);
  if (m == NULL) exit(-1);
  buffer = mmapfile_getbuf(m);
  buflen = mmapfile_getsize(m);

  b = buffer_new(buffer,buflen);

  p = (ty_esp *)malloc(sizeof(ty_esp));
  p->m = m;
  p->b[0] = b;
  p->loc[0] = 0; // -1
  p->numb = 0;

  p->grouptypes[0] = strdup("Top");
  p->grouptypes[1] = strdup("World Children");
  p->grouptypes[2] = strdup("Interior Cell Block");
  p->grouptypes[3] = strdup("Interior Cell Sub-Block");
  p->grouptypes[4] = strdup("Exterior Cell Block");
  p->grouptypes[5] = strdup("Exterior Cell Sub-Block");
  p->grouptypes[6] = strdup("Cell Children");
  p->grouptypes[7] = strdup("Topic Children");
  p->grouptypes[8] = strdup("Cell Persistent Children");
  p->grouptypes[9] = strdup("Cell Temporary Children");
  p->grouptypes[10] = strdup("Cell Visible Distant Children");

  p->incompressed = 0;

  return (void *)p;
}


void esp_close(void *pp)
{
  ty_esp *p;

  p = pp;
  buffer_free(p->b[0]);
  mmapfile_close(p->m);
}


// The algorithm:
// 1. Check the header. GRUP or not? The size is in <int>.
// Records: Compressed or not?
// Return to the user who decides if to continue or to skip.
// 2. Skip: buffer_skip_bytes(b, datasize - N);
// 3. Continue: If compressed, decompress, malloc, and make new
// buffer. If uncompressed, make new buffer.
// Keep the group and record header data accessible.
// If it was group, continue at 1.
// If it was record, continue at 11.

// 11. Check the header. The size is in <short>.
// If XXXX, then parse the <int> as datasize, and move to the next
// subrecord without parsing its datasize.
// Return to the user who decides if to continue or to skip.
// 12. Skip: buffer_skip_bytes(b, datasize);
// 13. Continue: Make new buffer.
// Keep the subrecord header data accessible.
// Return to user with the new buffer containing the subrecord
// data.

// With subrecords, we return the data.
// Should it be an option that we return the uncompressed data
// of records and of groups?

// XXXX Do we need to return the size? Should we return the header
// data as a new buffer?
// Return to the user:
// Subrecord: type, size.
// Record: type, size (must return the uncompressed size),
// Group: type, size


// Makes a subbuffer and moves to it.
// Uncompress if necessary.
// Pushes to the stack.
void esp_enter(void *pp, int a, int b)
{
}

// Deletes the subbuffer.
// Pops from the stack.
void esp_leave(void *pp)
{
}

#if 0
// Problem:
// How to detect if we have record or subrecord?
// The record and subrecord sizes does not include
// the size of the header, and that makes skipping
// non-trivial, data-dependent.
//
// Solved:
// At the main level, we may skip only groups and records.
// All subrecords are inside the records.

// 2. The subrecord "XXXX" makes this non-trivial.


// XXXX First we implement all in this routine. Then we split the code.

// Create new buffers for parsing the records and the groups.
// We need a stack for holding the buffers because the groups
// may be nested.
#if 0
// Old.
int esp_get_next(void *pp)
{
  ty_esp *p;
  int loc,n;
  char *s;
  void *b;

  p = pp;
  b = p->b;

  if (p->loc == -1) {
    p->loc = 0;
    p->issubrecordlevel = 0;
  } else {
    if (p->issubrecordlevel == 0) {
      if (buffer_eof(b) != 1) {
	loc = buffer_getloc(b);
	s = buffer_read_string4(b);
	if (strcmp(s,"GRUP") == 0) {
	  n = buffer_read_int(b);
	  buffer_setloc(b,loc+n);
	} else {
	  n = buffer_read_int(b);
	  buffer_setloc(b,loc+20+n);
	}
	free(s);
	if (buffer_eof(b) != 1) {
	  p->loc = buffer_getloc(b);
	} else {
	  p->loc = -2;
	}
      } else {
	p->loc = -2;
      }
    } else {
      // XXXX Later.
    }
  }

  return p->loc;
}
#endif

typedef struct {
  void *b;
  int currentloc;
  int nextloc;
} ty_stackentry;


char *esp_check(void *pp)
{
  ty_esp *p;
  int loc,n;
  char *s;
  void *b;

  p = pp;
  b = p->stack[p->numb - 1].b;
  // XXXX Stack stores only buffers pointing to uncompressed data.

  // What if EOF?

  while (buffer_eof(b) == 1) {
    buffer_free(b);

    // Free the buffer memory if the data was originally compressed.
    // stack[].m is NULL if we use subbuffer of a higher level buffer.
    if (p->stack[p->numb - 1].m != NULL) {
      free(p->stack[p->numb - 1].m);
    }

    p->numb--;
    b = p->stack[p->numb - 1].b;
    // XXXX We moved to end of record before pushing to stack.
    // XXXX We pushed NULL to stack[0].
  }

  if (b == NULL) return NULL;

  // XXXX Here we should handle the "XXXX" subrecord.
  // XXXX Or should?
  // Maybe not because we enclose each subrecord to its own buffer.
  // On otherhand, our traverser fails completely because the
  // datasize of the next subrecord is 0.
  // We should check "XXXX" prior creating the subrecord buffer.
  s = buffer_read_string4(b);
#if 1
  if (strcmp(s,"XXXX") == 0) {
    n = buffer_read_ushort(b); // Should be 4 for int.
    loc = buffer_getloc(b);
    p->xxxx = buffer_read_int(b); // Length of the next subrecord.
    p->isxxxx = 1;
    buffer_setloc(b,loc + n); // Move to next subrecord which must now exists.
    // XXXX We already were at this loc after XXXX subrecord but we
    // XXXX now move between records only by using the datasize fields.
    free(s);
    s = buffer_read_string4(b);
  }
#endif

  return s;
}

// CONTINUE.
// esp_next() Should enter groups and records.
// It should stop at the begin of the next record.
// User should know if this is record or subrecord.
// Subrecords can be detected by if we entered to
// record which was not GRUP.

// We need to maintain the header info.
// Perhaps we store the headers in the stack/path as pointers
// to buffers.
// Record header info is written in the header phase, and is
// read if we advance to compressed block.

// Alternatively we may just store the compressed/uncompressed flag.

// Maintain loc_if_advanced_to_child and loc_if_advanced_to_next.
// esp_child() and esp_next().

// We should write this more like a state machine.
// esp_next() would advance the state.

// in_top, in_group, in_record levels.
// in_top and in_group can be merged.

// The current version.
int esp_next(void *pp)
{
  ty_esp *p;
  int loc,n;
  char *s;
  void *b;

  p = pp;
  b = p->stack[p->numb - 1].b;
  // XXXX Stack stores only buffers pointing to uncompressed data.

  // What if EOF?

  while (buffer_eof(b) == 1) {
    buffer_free(b);

    // We should handle the subrecord-to-record transition here.

    // Free the buffer memory if the data was originally compressed.
    // stack[].m is NULL if we use subbuffer of a higher level buffer.
    if (p->stack[p->numb - 1].m != NULL) {
      free(p->stack[p->numb - 1].m);
    }

    p->numb--;
    b = p->stack[p->numb - 1].b;
    // XXXX We moved to end of record before pushing to stack.
    // XXXX We pushed NULL to stack[0].
  }

  if (b == NULL) return NULL;

  // Now we should enter to record.
  // XXXX Thinker this more.
  // esp_next() should move like this: header, data, header, data, etc.
  // p->phase = 0 for having header.next.
  // p->phase = 1 for having data next.
  // The buffer location may be in both cases at the begin of record.

  // Where we are at this point? At begin of header? Of data?

  if (p->level == 0) {
    // Group or record expected.
    // Make new buffer for the header only.
    // Return the new buffer to user.

    if (p->phase == 0) {
      // Header.

      // Move to the next header at the same tree level.
      buffer_setloc(b,q->nextloc); // == 0 for a new buffer.
      if (buffer_eof(b) == 1) {
	// Delete the buffer. No need to delete memory.
	// Pop the stack.
      } else {
	// Parse the header for name, size.
	// If record, parse also the compression flag.
	if (p->isgroup == 1) {
	  // Group.
	} else {
	  // Record.
	}
      }

    } else {
      // Data.
      if (p->isgroup == 1) {
	// Group.
	buffer = buffer_getbuf(b);
	btmp = b; // XXXX push to stack
	b = buffer_new(&(buffer[buffer_getloc(btmp)]),p->datasize); // XXXX place to stack
      } else {
	// Record.
	if (p->iscompressed == 1) {
	  numinputdata = p->datasize - 4; // skip the numuncompdata
	  numuncompdata = buffer_read_int(b);
	  numoutdata = numuncompdata;
	  obuffer = (unsigned char *)malloc(numoutdata*sizeof(unsigned char));
	  err = uncompress(obuffer,(uLongf *)(&numoutdata),&(buffer[buffer_getloc(b)]),numinputdata); // XXXX use buffer_getbuf_atloc()
	  if (err == Z_OK) {
	    // printf("err = OK\n");
	  } else if (err == Z_MEM_ERROR) {
	    printf("err = MEM\n");
	  } else if (err == Z_BUF_ERROR) {
	    printf("err = BUF\n");
	  } else if (err == Z_DATA_ERROR) {
	    printf("err = DATA\n");
	  } else {
	    printf("Unknown error\n");
	  }
	  if (numoutdata != numuncompdata) {
	    printf("Uncompressed data is of wrong size\n");
	    exit(-1);
	  }
	  btmp = b; // XXXX push to stack
	  b = buffer_new(obuffer,(int)numoutdata); // XXXX place to stack
	} else {
	  buffer = buffer_getbuf(b);
	  btmp = b; // XXXX push to stack
	  b = buffer_new(&(buffer[buffer_getloc(btmp)]),p->datasize); // XXXX place to stack
	}
      }

    }

    // Old code.
    recloc = buffer_getloc(b);
    s = buffer_read_string4(b);
    if (strcmp(s,"GRUP") == 0) {
      n = buffer_read_int(b);
      buffer_setloc(b,loc+n);
    } else {
      n = buffer_read_int(b);
      buffer_setloc(b,loc+20+n);
    }
    free(s);
    if (buffer_eof(b) != 1) {
      p->loc = buffer_getloc(b);
    } else {
      p->loc = -2;
    }
    // End of old code.


  } else {
    // Subrecord.
    // XXXX Later.

    // Processing of XXXX belongs to the header phase.
    // We expect to be in the correct record when we are
    // in the data phase.

    if (p->phase == 0) {
      // Header.

      recloc = buffer_getloc(b);
      // XXXX Here we should handle the "XXXX" subrecord.
      // XXXX Or should?

      // Maybe not because we enclose each subrecord to its own buffer.
      // On otherhand, our traverser fails completely because the
      // datasize of the next subrecord is 0.
      // We should check "XXXX" prior creating the subrecord buffer.

      s = buffer_read_string4(b);
#if 1
      if (strcmp(s,"XXXX") == 0) {
	n = buffer_read_ushort(b); // Should be 4 for int.
	if (n != 4) {
	  fprintf(stderr,"datasize of XXXX subrecord != 4 (= %i)\n",n);
	  exit(-1);
	}
	dataloc = buffer_getloc(b);
	p->xxxx = buffer_read_int(b); // Length of the next subrecord.
	p->isxxxx = 1;
	buffer_setloc(b,dataloc + n); // Move to next subrecord which must now exists.
	// XXXX We already were at this loc after XXXX subrecord but we
	// XXXX now move between records only by using the datasize fields.
	free(s);
	recloc = buffer_getloc(b);
	s = buffer_read_string4(b);
      }
#endif

    } else {
      // Data.
    }

  }


  return p->loc;
}


int esp_next_1(void *pp)
{
  ty_esp *p;
  int loc,n;
  char *s;
  void *b;

  p = pp;
  b = p->stack[p->numb - 1].b;

  if (p->level == 0) {
    // Group or record.
    if (buffer_eof(b) != 1) {
      // Make new buffer for the header only.
      // Return the new buffer to user.

      loc = buffer_getloc(b);
      s = buffer_read_string4(b);
      if (strcmp(s,"GRUP") == 0) {
	n = buffer_read_int(b);
	buffer_setloc(b,loc+n);
      } else {
	n = buffer_read_int(b);
	buffer_setloc(b,loc+20+n);
      }
      free(s);
      if (buffer_eof(b) != 1) {
	p->loc = buffer_getloc(b);
      } else {
	p->loc = -2;
      }
    } else {
      // End of buffer.
      p->loc = -2;
    }
  } else {
    // Subrecord.
    // XXXX Later.
  }


  return p->loc;
}


// Old version. 
// XXXX If user skips the record, we need not uncompress it.
int esp_get_next(void *pp)
{
  ty_esp *p;
  int loc,n;
  char *s;
  void *b;

  p = pp;
  b = p->stack[p->numb - 1].b;
  loc = p->stack[p->numb - 1].nextloc;
  buffer_setloc(b,loc);

  if (p->level == 0) {
    // Group or record.
    if (buffer_eof(b) != 1) {
      // Make new buffer for the header only.
      // Return the new buffer to user.

      loc = buffer_getloc(b);
      s = buffer_read_string4(b);
      if (strcmp(s,"GRUP") == 0) {
	n = buffer_read_int(b);
	buffer_setloc(b,loc+n);
      } else {
	n = buffer_read_int(b);
	buffer_setloc(b,loc+20+n);
      }
      free(s);
      if (buffer_eof(b) != 1) {
	p->loc = buffer_getloc(b);
      } else {
	p->loc = -2;
      }
    } else {
      // End of buffer.
      p->loc = -2;
    }
  } else {
    // Subrecord.
    // XXXX Later.
  }


  return p->loc;
}
#endif

// How to detected if we have record, subrecord, or group header?
void esp_print_type(void *pp)
{
  ty_esp *p;
  int loc;
  char *s;
  void *b;

  p = pp;
  b = p->b;
  loc = buffer_getloc(b);
  s = buffer_read_string4(b);
  printf("%s\n",s);
  free(s);
  buffer_setloc(b,loc);
}

void esp_print_size(void *pp)
{
  ty_esp *p;
  int loc;
  char *s;
  void *b;
  int n;

  p = pp;
  b = p->b;
  loc = buffer_getloc(b);
  buffer_skip_bytes(b,4);
  n = buffer_read_int(b);
  printf("%i\n",n);
  buffer_setloc(b,loc);
}

#if 0
// esp_get_next() version.

int main(int ac, char **av)
{
  void *esp;
  int rec;

  if (ac < 1) {
    fprintf(stderr,"Usage: libespparser file.esp\n");
    exit(-1);
  }

  esp = esp_open(av[1]);

  // esp_get_next_record()
  // esp_get_next_subrecord()
  // esp_get_next_group()  needed?
  // esp_get_next() gives next record, subrecord, group in depth-first order
  while ((rec = esp_get_next(esp)) >= 0) {
    esp_print_type(esp);
    esp_print_size(esp);
  } 

  esp_close(esp);

  return 1;
}

#endif


char *esp_read_name(ty_esp *esp) // void *p
{
  void *b;

  b = esp->b[esp->numb];
  if (buffer_gettaillen(b) < 4) return NULL;
  return buffer_read_string4(b);
}

void esp_read_name_in(ty_esp *esp, char *s) // void *p
{
  void *b;

  b = esp->b[esp->numb];
  // if (buffer_gettaillen(b) < 4) return NULL;
  buffer_read_string4_in(b,s);
}

void esp_skip_group(ty_esp *esp) // void *p
{
  void *b;
  int n;

  b = esp->b[esp->numb];
  n = buffer_read_int(b);
  buffer_skip_bytes(b,n-8); // 8 = "GRUP" + groupsize
}

void esp_skip_record(ty_esp *esp) // void *p
{
  void *b;
  int n;
  int loc;

  b = esp->b[esp->numb];
  // loc = buffer_getloc(b);
  // printf("loc = %i\n",loc);
  n = buffer_read_int(b);
  // printf("record size %i\n",n);
  buffer_skip_bytes(b,n + C_RECORD_HEADERSIZE - 8); // 8 = RecordID + recordsize
  // loc = buffer_getloc(b);
  // printf("loc = %i\n",loc);
}

void esp_skip_subrecord(ty_esp *esp) // void *p
{
  void *b;
  int n;

  b = esp->b[esp->numb];
  n = buffer_read_ushort(b);
  buffer_skip_bytes(b,n);
}

void esp_skip_subrecord_xxxx(ty_esp *esp, int skip) // void *p
{
  void *b;
  int n;

  b = esp->b[esp->numb];
  n = buffer_read_ushort(b);
  buffer_skip_bytes(b,skip);
}

int esp_getloc(ty_esp *esp) // void *p
{
  void *b;
  int n;

  b = esp->b[esp->numb];
  return buffer_getloc(b);
}

// We assume the buffer index is after the record type,
// at loc 4 in the header.
void esp_print_grouptype(ty_esp *esp) // void *p
{
  void *b;
  int n;
  int loc;
  char *s2;
  int grouptype;
  char *label_s;
  int label_int;
  int label_x;
  int label_y;

  b = esp->b[esp->numb];
  loc = buffer_getloc(b);
  n = buffer_read_int(b);
  s2 = buffer_read_string4(b); // label
  grouptype = buffer_read_int(b);
  label_s = s2;
  label_int = ((int *)s2)[0];
  // grid y,x -- reverse order
  label_x = (int)(((short *)s2)[1]);
  label_y = (int)(((short *)s2)[0]);
  switch (grouptype) {
  case 0:
    printf("  %s %s\n",label_s,esp->grouptypes[grouptype]);
    break;
  case 1:
    printf("  %i %s\n",label_int,esp->grouptypes[grouptype]);
    break;
  case 2:
    printf("  %i %s\n",label_int,esp->grouptypes[grouptype]);
    break;
  case 3:
    printf("  %i %s\n",label_int,esp->grouptypes[grouptype]);
    break;
  case 4:
    printf("  %i %i %s\n",label_x,label_y,esp->grouptypes[grouptype]);
    break;
  case 5:
    printf("  %i %i %s\n",label_x,label_y,esp->grouptypes[grouptype]);
    break;
  case 6:
    printf("  %i %s\n",label_int,esp->grouptypes[grouptype]);
    break;
  case 7:
    printf("  %i %s\n",label_int,esp->grouptypes[grouptype]);
    break;
  case 8:
    printf("  %i %s\n",label_int,esp->grouptypes[grouptype]);
    break;
  case 9:
    printf("  %i %s\n",label_int,esp->grouptypes[grouptype]);
    break;
  case 10:
    printf("  %i %s\n",label_int,esp->grouptypes[grouptype]);
    break;
  default:
    printf("  unknown group type\n");
    break;
  }
  free(s2);

  buffer_setloc(b,loc);
}

void esp_enter_group(ty_esp *esp) // void *p
{
  void *b;
  int n;
  int loc;
  void *b2;
  int groupsize;

  b = esp->b[esp->numb];
  loc = buffer_getloc(b);

  groupsize = buffer_read_int(b);
  buffer_skip_bytes(b,C_RECORD_HEADERSIZE - 8);

  b2 = buffer_new(buffer_getbuf_atloc(b),groupsize - C_RECORD_HEADERSIZE); // Includes header size.
  buffer_set_offset(b2,buffer_getloc(b));
  esp->b[esp->numb + 1] = b2;
  esp->numb++;

  buffer_setloc(b,loc);
}

void esp_leave_group(ty_esp *esp) // void *p
{
  void *b;
  int n;
  int loc;
  void *b2;

  b2 = esp->b[esp->numb];
  buffer_free(b2);

  esp->numb--;
}

void esp_enter_record(ty_esp *esp) // void *p
{
  void *b;
  int n;
  int loc;
  void *b2;
  int recordsize;
  unsigned int flags;
  int compsize;
  int uncompsize;
  int outsize;
  unsigned char *outbuf;
  int err;

  b = esp->b[esp->numb];
  loc = buffer_getloc(b);

  recordsize = buffer_read_int(b);
  flags = buffer_read_uint(b);
  buffer_skip_bytes(b,C_RECORD_HEADERSIZE - 4 - 8); // 4 = RecID.

  if (flags & 0x00040000) {
    // Data is uncompressed.
    uncompsize = buffer_read_int(b);
    compsize = recordsize - 4; // Only 4 because recordsize excludes header size.
    err = uncomp_zlib(buffer_getbuf_atloc(b),compsize,uncompsize,&outbuf,&outsize);
    if (err == 0) {
      fprintf(stderr,"uncomp_zlib() failed\n");
      exit(-1);
    }
    
    esp->incompressed = 1;
    b2 = buffer_new(outbuf,outsize);
    // Offset in compressed data is meaningless.
    // We may write the uncompressed data to file and use here offset 0.
    // buffer_set_offset(b2,buffer_getloc(b));

  } else {
    // Data is uncompressed.
    esp->incompressed = 0;
    b2 = buffer_new(buffer_getbuf_atloc(b),recordsize); // Excludes header size.
    buffer_set_offset(b2,buffer_getloc(b));
  }
  esp->b[esp->numb + 1] = b2;
  esp->numb++;

  buffer_setloc(b,loc);
}

void esp_leave_record(ty_esp *esp) // void *p
{
  void *b;
  int n;
  int loc;
  void *b2;

  b2 = esp->b[esp->numb];
  if (esp->incompressed == 1) {
    free(buffer_getbuf(b2));
  }
  buffer_free(b2);
  esp->numb--;
  esp->incompressed = 0;
}

int esp_get_groupsize(ty_esp *esp) // void *p
{
  void *b;
  int n;
  int loc;
  void *b2;
  int size;

  b = esp->b[esp->numb];
  loc = buffer_getloc(b);

  size = buffer_read_int(b);

  buffer_setloc(b,loc);

  return size;
}

int esp_get_recordsize(ty_esp *esp) // void *p
{
  void *b;
  int n;
  int loc;
  void *b2;
  int size;

  b = esp->b[esp->numb];
  loc = buffer_getloc(b);

  size = buffer_read_int(b);

  buffer_setloc(b,loc);

  return size;
}

int esp_get_subrecordsize(ty_esp *esp) // void *p
{
  void *b;
  int n;
  int loc;
  void *b2;
  int size;

  b = esp->b[esp->numb];
  loc = buffer_getloc(b);

  size = buffer_read_ushort(b);

  buffer_setloc(b,loc);

  return size;
}

void *esp_get_buffer(ty_esp *esp)
{
  return esp->b[esp->numb];
}

#if 0
// Pre 20100326.

// More explicit version with esp_enter()/esp_leave() etc.

int main(int ac, char **av)
{
  void *esp;
  int level[20];
  int done;
  int numlevel;
  char *name;
  char *inrecord;
  int loc;
  int size;
  // for REFR/DATA
  int n;
  float f;
  float xpos,ypos,zpos;
  void *b;
  int hasxxxx;
  int xxxxsize;
  int mloc;

  if (ac < 1) {
    fprintf(stderr,"Usage: libespparser file.esp\n");
    exit(-1);
  }

  esp = esp_open(av[1]);

  // OK fixed with level[] and numlevel
  // The level system should be fixed.

  done = 0;
  numlevel = 0;
  level[0] = 0; // 0 = top, 1 = group, 2 = record
  inrecord = NULL;
  hasxxxx = 0;
  xxxxsize = 0;

  while (done == 0) {
    if (level[numlevel] == 0) {
      // In top.
      loc = esp_getloc(esp);
      name = esp_read_name(esp);
      if (name != NULL) {
        // printf("%s\n",name);
	if (strcmp(name,"GRUP") == 0) {
#if 0
	  size = esp_get_groupsize(esp);
	  printf("%s %i %i\n",name,loc,size);
	  esp_print_grouptype(esp);
	  esp_skip_group(esp);
#else
	  size = esp_get_groupsize(esp);
	  printf("%s %i %i\n",name,loc,size);
	  esp_print_grouptype(esp);
	  esp_enter_group(esp);
	  numlevel++;
	  level[numlevel] = 1;
#endif 
	} else {
#if 0
	  size = esp_get_recordsize(esp);
	  printf("%s %i %i\n",name,loc,size);
	  esp_skip_record(esp);
#else
	  size = esp_get_recordsize(esp);
	  printf("%s %i %i\n",name,loc,size);
	  esp_enter_record(esp);
	  numlevel++;
	  level[numlevel] = 2;
	  inrecord = strdup(name);
#endif 
	}
	free(name);
      } else {
	// name == NULL
	// End of file.
	done = 1;
      }
    } else if (level[numlevel] == 1) {
      // Inside group.
      loc = esp_getloc(esp);
      name = esp_read_name(esp);
      if (name != NULL) {
        // printf("%s\n",name);
	if (strcmp(name,"GRUP") == 0) {
#if 0
	  size = esp_get_groupsize(esp);
	  printf("%s %i %i\n",name,loc,size);
	  esp_print_grouptype(esp);
	  esp_skip_group(esp);
#else
	  size = esp_get_groupsize(esp);
	  printf("%s %i %i\n",name,loc,size);
	  esp_print_grouptype(esp);
	  esp_enter_group(esp);
	  numlevel++;
	  level[numlevel] = 1;
#endif 
	} else {
#if 0
	  size = esp_get_recordsize(esp);
	  printf("%s %i %i\n",name,loc,size);
	  esp_skip_record(esp);
#else
	  size = esp_get_recordsize(esp);
	  printf("%s %i %i\n",name,loc,size);
	  esp_enter_record(esp);
	  numlevel++;
	  level[numlevel] = 2;
	  inrecord = strdup(name);
#endif 
	}
	free(name);
      } else {
	// name == NULL
	// End of buffer.
	esp_leave_group(esp);
	esp_skip_group(esp); // Needed because group was processed in other buffer.
	numlevel--;
      }
    } else if (level[numlevel] == 2) {
      // Inside a record.
      loc = esp_getloc(esp);
      name = esp_read_name(esp);
      if (name != NULL) {
	// XXXX We need to handle the special XXXX subrecord here.
	size = esp_get_subrecordsize(esp);
	mloc = esp_getloc(esp);
	if (strcmp(name,"XXXX") == 0) {
	  hasxxxx = 1;
	  b = esp_get_buffer(esp);
	  n = buffer_read_short(b);
	  xxxxsize = buffer_read_int(b);
	  printf("%s %i %i %i\n",name,loc,size,xxxxsize);
	  // buffer_setloc(b,mloc); // Return to begin of XXXX subrecord.
	  // esp_skip_subrecord(esp);
	} else {
	  if (hasxxxx == 1) {
	    size = xxxxsize;
	    hasxxxx = 2;
	    xxxxsize = 0;
	    printf("%s %i %i (defined by XXXX subrecord)\n",name,loc,size);
	  } else {
	    printf("%s %i %i\n",name,loc,size);
	  }

	  // Print all refr coordinates.
	  if ((strcmp(inrecord,"REFR") == 0) && (strcmp(name,"DATA") == 0)) {
	    b = esp_get_buffer(esp);
	    n = buffer_read_short(b);
	    // printf("REFR/DATA %i\n",n);
	    f = buffer_read_float(b);
	    xpos = f;
	    // printf("Position X %f\n",f);
	    f = buffer_read_float(b);
	    ypos = f;
	    // printf("Position Y %f\n",f);
	    f = buffer_read_float(b);
	    zpos = f;
	    // printf("Position Z %f\n",f);
	    f = buffer_read_float(b);
	    // printf("Rotation X %f\n",f);
	    f = buffer_read_float(b);
	    // printf("Rotation Y %f\n",f);
	    f = buffer_read_float(b);
	    // printf("Rotation Z %f\n",f);
	    printf("refr pos %f %f %f\n",xpos,ypos,zpos);
	  } else {
	    if (hasxxxx == 2) {
	      esp_skip_subrecord_xxxx(esp,size);
	      hasxxxx = 0;
	    } else {
	      esp_skip_subrecord(esp);
	    }
	  }
	}
	free(name);
      } else {
	// name == NULL
	// End of buffer.
	// XXXX commented out until we figure out what to do at leave
	// esp_leave_record(esp);
	esp_leave_record(esp);
	esp_skip_record(esp); // Needed because record was processed in other buffer.
	numlevel--;
	free(inrecord);
	inrecord = NULL;
      }
    }

    // esp_print_type(esp);
    // esp_print_size(esp);
  }

  esp_close(esp);

  return 1;
}

#endif



#if 1
// Post 20100326.

// More explicit version with esp_enter()/esp_leave() etc.

// Total size of memory needed to hold Fallout3.esm
// ? 40*89748 + 28*718951 + 12*2634065
// %2 = 55329328
// ? 40*89748 + 28*718951
// %3 = 23720548

// size = 40 bytes, or 24 bytes if groupdata is not expanded
typedef struct {
  int loc;
  int size;
  int groupdata; // Depends on the type.
  int type;

  // Skip these four if too much memory is used.
  int label; // Copy of groupdata.
  int x; // Copy of groupdata.
  int y; // Copy of groupdata.
  int formid; // Copy of groupdata.

  int unknown1; // Stamp.
  int unknown2; // F3.
} ty_group;

// size = 28 bytes
typedef struct {
  int loc;
  int type;
  int size;
  int flags;
  int formid;
  int unknown1; // Flags2.
  int unknown2; // F3.
} ty_record;

// XXXX But CS displays the subrecord data in the scrolled list widget.
// Subrecord data are read when needed. They are not kept in the memory.
// size = 12 bytes
typedef struct {
  int loc;  // XXXX How to handle compressed records?
  int type;
  int size;
} ty_subrecord;

#if 0
// XXXX How to handle compressed records?
#define G_ESFILE_MAXSIZE 10000000

typedef struct {
  void *data[G_ESFILE_MAXSIZE];
} ty_esfile;
#endif

int main(int ac, char **av)
{
  void *esp;
  int level[20];
  int done;
  int numlevel;
  char *name;
  char *inrecord;
  int loc;
  int size;
  // for REFR/DATA
  int n;
  float f;
  float xpos,ypos,zpos;
  void *b;
  int hasxxxx;
  int xxxxsize;
  int mloc;

  if (ac < 1) {
    fprintf(stderr,"Usage: libespparser file.esp\n");
    exit(-1);
  }

  esp = esp_open(av[1]);

  // OK fixed with level[] and numlevel
  // The level system should be fixed.

  done = 0;
  numlevel = 0;
  level[0] = 0; // 0 = top, 1 = group, 2 = record
  inrecord = NULL;
  hasxxxx = 0;
  xxxxsize = 0;

  while (done == 0) {
    if (level[numlevel] == 0) {
      // In top.
      loc = esp_getloc(esp);
      name = esp_read_name(esp);
      if (name != NULL) {
        // printf("%s\n",name);
	if (strcmp(name,"GRUP") == 0) {
#if 0
	  size = esp_get_groupsize(esp);
	  printf("%s %i %i\n",name,loc,size);
	  esp_print_grouptype(esp);
	  esp_skip_group(esp);
#else
	  size = esp_get_groupsize(esp);
	  printf("group %s %i %i\n",name,loc,size);
	  esp_print_grouptype(esp);
	  esp_enter_group(esp);
	  numlevel++;
	  level[numlevel] = 1;
#endif 
	} else {
#if 0
	  size = esp_get_recordsize(esp);
	  printf("%s %i %i\n",name,loc,size);
	  esp_skip_record(esp);
#else
	  size = esp_get_recordsize(esp);
	  printf("record %s %i %i\n",name,loc,size);
	  esp_enter_record(esp);
	  numlevel++;
	  level[numlevel] = 2;
	  inrecord = strdup(name);
#endif 
	}
	free(name);
      } else {
	// name == NULL
	// End of file.
	done = 1;
      }
    } else if (level[numlevel] == 1) {
      // Inside group.
      loc = esp_getloc(esp);
      name = esp_read_name(esp);
      if (name != NULL) {
        // printf("%s\n",name);
	if (strcmp(name,"GRUP") == 0) {
#if 0
	  size = esp_get_groupsize(esp);
	  printf("%s %i %i\n",name,loc,size);
	  esp_print_grouptype(esp);
	  esp_skip_group(esp);
#else
	  size = esp_get_groupsize(esp);
	  printf("group %s %i %i\n",name,loc,size);
	  esp_print_grouptype(esp);
	  esp_enter_group(esp);
	  numlevel++;
	  level[numlevel] = 1;
#endif 
	} else {
#if 0
	  size = esp_get_recordsize(esp);
	  printf("%s %i %i\n",name,loc,size);
	  esp_skip_record(esp);
#else
	  size = esp_get_recordsize(esp);
	  printf("record %s %i %i\n",name,loc,size);
	  esp_enter_record(esp);
	  numlevel++;
	  level[numlevel] = 2;
	  inrecord = strdup(name);
#endif 
	}
	free(name);
      } else {
	// name == NULL
	// End of buffer.
	esp_leave_group(esp);
	esp_skip_group(esp); // Needed because group was processed in other buffer.
	numlevel--;
      }
    } else if (level[numlevel] == 2) {
      // Inside a record.
      loc = esp_getloc(esp);
      name = esp_read_name(esp);
      if (name != NULL) {
	// XXXX We need to handle the special XXXX subrecord here.
	size = esp_get_subrecordsize(esp);
	mloc = esp_getloc(esp);
	if (strcmp(name,"XXXX") == 0) {
	  hasxxxx = 1;
	  b = esp_get_buffer(esp);
	  n = buffer_read_short(b);
	  xxxxsize = buffer_read_int(b);
	  printf("subrecord %s %i %i %i\n",name,loc,size,xxxxsize);
	  // buffer_setloc(b,mloc); // Return to begin of XXXX subrecord.
	  // esp_skip_subrecord(esp);
	} else {
	  if (hasxxxx == 1) {
	    size = xxxxsize;
	    hasxxxx = 2;
	    xxxxsize = 0;
	    printf("subrecord %s %i %i (defined by XXXX subrecord)\n",name,loc,size);
	  } else {
	    printf("subrecord %s %i %i\n",name,loc,size);
	  }

	  // Print all refr coordinates.
	  if ((strcmp(inrecord,"REFR") == 0) && (strcmp(name,"DATA") == 0)) {
	    b = esp_get_buffer(esp);
	    n = buffer_read_short(b);
	    // printf("REFR/DATA %i\n",n);
	    f = buffer_read_float(b);
	    xpos = f;
	    // printf("Position X %f\n",f);
	    f = buffer_read_float(b);
	    ypos = f;
	    // printf("Position Y %f\n",f);
	    f = buffer_read_float(b);
	    zpos = f;
	    // printf("Position Z %f\n",f);
	    f = buffer_read_float(b);
	    // printf("Rotation X %f\n",f);
	    f = buffer_read_float(b);
	    // printf("Rotation Y %f\n",f);
	    f = buffer_read_float(b);
	    // printf("Rotation Z %f\n",f);
	    printf("refr pos %f %f %f\n",xpos,ypos,zpos);
	  } else {
	    if (hasxxxx == 2) {
	      esp_skip_subrecord_xxxx(esp,size);
	      hasxxxx = 0;
	    } else {
	      esp_skip_subrecord(esp);
	    }
	  }
	}
	free(name);
      } else {
	// name == NULL
	// End of buffer.
	// XXXX commented out until we figure out what to do at leave
	// esp_leave_record(esp);
	esp_leave_record(esp);
	esp_skip_record(esp); // Needed because record was processed in other buffer.
	numlevel--;
	free(inrecord);
	inrecord = NULL;
      }
    }

    // esp_print_type(esp);
    // esp_print_size(esp);
  }

  esp_close(esp);

  return 1;
}

#endif
