
// Copyright 2007 Juhana Sadeharju
// GNU GPL

// espparser: extracts the data from Oblivion ESP file
// espcompiler: compiles the data to Oblivion ESP file

// Usage: espparser <esp file> <target directory>
// Usage: espcompiler <source directory> <esp file>

// The ESP file is converted to directory and file system.
// This is only the first step in parsing and using the
// data in the ESP file.

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


// For recursive parsing we windowize the original buffer.
void *bufferstack[128];

int global_formid;

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

void printflags8(unsigned int n)
{
  unsigned int k;
  int i;

  k = 0x00000080;
  for (i = 0; i < 8; i++) {
    if ((n & k) != 0) {
      printf("1");
    } else {
      printf("0");
    }
    k = k >> 1;
    if (((i % 4) == 3) && (i != 7)) {
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

// Converts the hashes to print format which matches hexdump output.
// byte0 byte1 ... byte7
char *hash2hex(char *hash)
{
  char *name;
  int len;
  int i;
  unsigned int h = 0xffffff00;
  char t[9];
  char *s;

  s = (char *)malloc(25*sizeof(char));
  for (i = 0; i < 25; i++) s[i] = ' ';
  for (i = 0; i < 8; i++) {
    sprintf(t,"%x",h | (unsigned int)hash[i]);
    // printf("t = \"%s\"\n",t);
    s[3*i+0] = t[6];
    s[3*i+1] = t[7];
  }
  s[23] = '\0';
  s[24] = '\0';

  return s;
}

char *hash2name(char *hash)
{
  char *name;
  int len;
  int i;

  len = (int)hash[2];
  name = (char *)malloc((len+1)*sizeof(char));
  for (i = 0; i < len; i++) name[i] = '.';
  name[len] = '\0';
  name[0] = hash[3] & 0x7f; // 0x1f but two low bits of 0xfc are 0
  if (len > 1) {
    name[len-1] = hash[0] & 0x7f;
  }
  if (len > 2) {
    name[len-2] = hash[1] & 0x7f;
  }

  return name;
}

void parse_modt(void *b, int n)
{
  int numchunks;
  char *hash;
  char *hashhex;
  char *s;
  int i;

  numchunks = n/24;
  for (i = 0; i < numchunks; i++) {
    hash = buffer_read_bytes(b,8);
    hashhex = hash2hex(hash);
    s = hash2name(hash);
    printf("%s  \"%s\"\n",hashhex,s);
    free(s);
    free(hashhex);
    free(hash);
    hash = buffer_read_bytes(b,8);
    hashhex = hash2hex(hash);
    s = hash2name(hash);
    printf("%s  \"%s\"\n",hashhex,s);
    free(s);
    free(hashhex);
    free(hash);
    hash = buffer_read_bytes(b,8);
    hashhex = hash2hex(hash);
    s = hash2name(hash);
    printf("%s  \"%s\"\n",hashhex,s);
    free(s);
    free(hashhex);
    free(hash);
  }
}

void parse_nift(void *b, int n)
{
  int numchunks;
  char *hash;
  char *hashhex;
  char *s;
  int i,j;
  int numnifs;
  int numtextures;

  n = buffer_read_int(b);
  printf("%i\n",n);
  numnifs = n;

  for (i = 0; i < numnifs; i++) {
    n = buffer_read_byte(b);
    printf("%i\n",n);
    numtextures = n;

    // numchunks = n/24;
    // for (i = 0; i < numchunks; i++) {
    // base, normal, specular maps == 3 maps?
    for (j = 0; j < numtextures; j++) {

      hash = buffer_read_bytes(b,8);
      hashhex = hash2hex(hash);
      s = hash2name(hash);
      printf("%s  \"%s\"\n",hashhex,s);
      free(s);
      free(hashhex);
      free(hash);
      hash = buffer_read_bytes(b,8);
      hashhex = hash2hex(hash);
      s = hash2name(hash);
      printf("%s  \"%s\"\n",hashhex,s);
      free(s);
      free(hashhex);
      free(hash);
      hash = buffer_read_bytes(b,8);
      hashhex = hash2hex(hash);
      s = hash2name(hash);
      printf("%s  \"%s\"\n",hashhex,s);
      free(s);
      free(hashhex);
      free(hash);
    }
  }
}


void parse_ctda(void *b)
{
  int n;
  float f;
  int m;

  n = buffer_read_ubyte(b);
  printflags8(n);
  //      0000,0000
  printf("        ^0 AND 1 OR\n");
  printf("       ^Run on Target\n");
  printf("      ^Use Global\n");
  printf("^^^000 == 001 != 010 > 011 >= 100 < 101 <=\n");
  n = buffer_read_ubyte(b);
  printf("%i (unused)\n",n);
  n = buffer_read_ubyte(b);
  printf("%i (unused)\n",n);
  n = buffer_read_ubyte(b);
  printf("%i (unused)\n",n);
  m = buffer_getloc(b);
  f = buffer_read_float(b);
  buffer_setloc(b,m);
  n = buffer_read_int(b);
  printf("Value %f / Global FormID %i\n",f,n);
  n = buffer_read_int(b);
  printf("Function ID %i\n",n);
  n = buffer_read_int(b);
  printf("Parameter 1: %i\n",n);
  n = buffer_read_int(b);
  printf("Parameter 2: %i\n",n);
  // XXXX 4*ubyte?
  n = buffer_read_int(b);
  printf("%i\n",n); // XXXX Oblivion.esm has values 0 and 1  TODO
}

void parse_ctdt(void *b)
{
  int n;
  float f;

  n = buffer_read_ubyte(b);
  printflags8(n);
  //      0000,0000
  printf("        ^0 AND 1 OR\n");
  printf("       ^Run on Target\n");
  printf("^^^000 == 001 != 010 > 011 >= 100 < 101 <=\n");
  n = buffer_read_ubyte(b);
  printf("%i\n",n);
  n = buffer_read_ubyte(b);
  printf("%i\n",n);
  n = buffer_read_ubyte(b);
  printf("%i\n",n);
  f = buffer_read_float(b);
  printf("Value %f\n",f);
  n = buffer_read_int(b);
  printf("Function ID %i\n",n);
  n = buffer_read_int(b);
  printf("Parameter 1: %i\n",n);
  n = buffer_read_int(b);
  printf("Parameter 2: %i\n",n);
}

void parse_efit(void *b)
{
  int n;
  float f;
  char *s2;

  s2 = buffer_read_nstring(b,4);
  printf("%s\n",s2);
  free(s2);
  n = buffer_read_int(b);
  printf("Magnitude %i\n",n);
  n = buffer_read_int(b);
  printf("Area %i\n",n);
  n = buffer_read_int(b);
  printf("Duration %i\n",n);
  n = buffer_read_int(b);
  printf("Range %i %% 0 Self 1 Touch 2 Target\n",n);
  n = buffer_read_int(b);
  printf("ActorVal %i %% 0 Strength 1 Intelligence 2 Willpower 3 Agility 4 Speed 5 Endurance 6 Personality 7 Luck\n",n);
}

void parse_scit(void *b, int size)
{
  int n;
  unsigned int flags;
  char *s2;

  if (size == 4) {
    n = buffer_read_int(b);
    printf("Script FormID %i (Masked FormID %i)\n",n,n & 0xffffff);
  } else if (size == 12) {
    n = buffer_read_int(b);
    printf("Script FormID %i\n",n);
    n = buffer_read_int(b);
    printf("School %i %% 0 Alteration 1 Conjuration 2 Destruction 3 Illusion 4 Mysticism 5 Restoration\n",n);
    s2 = buffer_read_nstring(b,4);
    printf("Visual Effect \"%s\"\n",s2);
    free(s2);
  } else if (size == 16) {
    n = buffer_read_int(b);
    printf("Script FormID %i\n",n);
    n = buffer_read_int(b);
    printf("School %i %% 0 Alteration 1 Conjuration 2 Destruction 3 Illusion 4 Mysticism 5 Restoration\n",n);
    s2 = buffer_read_nstring(b,4);
    printf("Visual Effect \"%s\"\n",s2);
    free(s2);
    n = buffer_read_ubyte(b);
    printflags8(n);
    //      0000,0000
    printf("        ^Effect is Hostile\n");
    n = buffer_read_ubyte(b);
    printf("%i (unused)\n",n);
    n = buffer_read_ubyte(b);
    printf("%i (unused)\n",n);
    n = buffer_read_ubyte(b);
    printf("%i (unused)\n",n);
  } else {
    fprintf(stderr,"error in SCIT\n");
    exit(-1);
  }
}

void parse_schr(void *b)
{
  int n;

  n = buffer_read_int(b);
  printf("%i schrunknown1\n",n);
  n = buffer_read_int(b);
  printf("Number of the script objects (SCRO) and refs (SCRV) %i\n",n);
  n = buffer_read_int(b);
  printf("Size of the compiled script (SCDA) %i\n",n);
  n = buffer_read_int(b);
  printf("Number of the script variables %i\n",n);
  n = buffer_read_short(b);
  printf("Script Type %i %% 0 Object 1 Quest 256 Effect\n",n);
  n = buffer_read_short(b);
  printf("%i schrunknown2\n",n);
}

// See UESP Wiki doc on SCDA.
void parse_compiledscript(void *b)
{
  int n;
  int opcode;
  int opcodelen;
  int explen;
  int funclen;
  int varop;
  int varindex;
  int refvarop;
  int refvarindex;

  printf(" === Attempting to decompile the compiled script\n");
  while (buffer_eof(b) != 1) {
    opcode = buffer_read_ushort(b);
    switch (opcode) {
    case 0x1d:
      printf("ScriptName\n");
      opcodelen = buffer_read_ushort(b);
      break;
    case 0x10:
      printf("BeginMode\n");
      opcodelen = buffer_read_ushort(b);
      buffer_skip_bytes(b,opcodelen); // Decompiling top level codes only.
      break;
    case 0x11:
      printf("End\n");
      opcodelen = buffer_read_ushort(b);
      buffer_skip_bytes(b,opcodelen); // Decompiling top level codes only.
      break;
    case 0x15:
      printf("Set\n");
      opcodelen = buffer_read_ushort(b);
      // buffer_skip_bytes(b,opcodelen); // Decompiling top level codes only.
      n = buffer_read_ubyte(b);
      // printf("variable 1st byte %x\n",n);
      // buffer_skip_bytes(b,opcodelen-1); // Skipping rest of var and expression.
      varop = n;
      switch (varop) {
      case 0x47:
	printf("varop %x\n",varop);
	varindex = buffer_read_ushort(b);
	printf("varindex %i\n",varindex);
	buffer_skip_bytes(b,opcodelen-3); // Skipping expression.
	break;
      case 0x66:
	printf("varop %x\n",varop);
	varindex = buffer_read_ushort(b);
	printf("varindex %i\n",varindex);
	buffer_skip_bytes(b,opcodelen-3); // Skipping expression.
	break;
      case 0x72:
	printf("varop %x\n",varop);
	varindex = buffer_read_ushort(b);
	printf("varindex %i\n",varindex);
#if 0
	n = buffer_read_ubyte(b);
	printf("ref script var data 1 %i %x\n",n,n);
	n = buffer_read_ubyte(b);
	printf("ref script var data 2 %i %x\n",n,n);
	n = buffer_read_ubyte(b);
	printf("ref script var data 3 %i %x\n",n,n);
	buffer_skip_bytes(b,opcodelen-3-3); // Skipping expression.
#else
	n = buffer_read_ubyte(b);
	refvarop = n;
	switch (refvarop) {
	case 0x47:
	  printf("refvarop %x\n",refvarop);
	  refvarindex = buffer_read_ushort(b);
	  printf("refvarindex %i\n",refvarindex);
	  buffer_skip_bytes(b,opcodelen-3-3); // Skipping expression.
	  break;
	case 0x66:
	  printf("refvarop %x\n",refvarop);
	  refvarindex = buffer_read_ushort(b);
	  printf("refvarindex %i\n",refvarindex);
	  buffer_skip_bytes(b,opcodelen-3-3); // Skipping expression.
	  break;
	case 0x73:
	  printf("refvarop %x\n",refvarop);
	  refvarindex = buffer_read_ushort(b);
	  printf("refvarindex %i\n",refvarindex);
	  buffer_skip_bytes(b,opcodelen-3-3); // Skipping expression.
	  break;
	default:
	  printf("unknown ref varop %x of set command\n",refvarop);
	  buffer_skip_bytes(b,opcodelen-3-1); // Skipping rest of var and expression.
	  break;
	}
#endif
	break;
      case 0x73:
	printf("varop %x\n",varop);
	varindex = buffer_read_ushort(b);
	printf("varindex %i\n",varindex);
	buffer_skip_bytes(b,opcodelen-3); // Skipping expression.
	break;
      default:
	printf("unknown set varop %x\n",varop);
	buffer_skip_bytes(b,opcodelen-1); // Skipping rest of var and expression.
	break;
      }
      break;
    case 0x16:
      printf("If\n");
      opcodelen = buffer_read_ushort(b);
      n = buffer_read_ushort(b);
      printf("JmpOps %i\n",n);
      n = buffer_read_ushort(b);
      printf("ExpLen %i\n",n);
      explen = n;
      buffer_skip_bytes(b,explen); // Decompiling top level codes only.
      break;
    case 0x17:
      printf("Else\n");
      opcodelen = buffer_read_ushort(b);
      n = buffer_read_ushort(b);
      printf("JmpOps %i\n",n);
      break;
    case 0x18:
      printf("ElseIf\n");
      opcodelen = buffer_read_ushort(b);
      n = buffer_read_ushort(b);
      printf("JmpOps %i\n",n);
      n = buffer_read_ushort(b);
      printf("ExpLen %i\n",n);
      explen = n;
      buffer_skip_bytes(b,explen); // Decompiling top level codes only.
      break;
    case 0x19:
      printf("EndIf\n");
      opcodelen = buffer_read_ushort(b);
      buffer_skip_bytes(b,opcodelen); // Decompiling top level codes only.
      break;
    case 0x1c:
      printf("RefSCRO");
      n = buffer_read_ushort(b);
      printf("%i\n",n);
      n = buffer_read_ushort(b);
      printf("Function%.4x\n",n);
      funclen = buffer_read_ushort(b);
      buffer_skip_bytes(b,funclen); // Not decompiling function.
      break;
    case 0x1e:
      printf("Return\n");
      opcodelen = buffer_read_ushort(b);
      break;
    default:
      // Check if we have a function.
      switch (opcode) {
#if 0
      case 0x1021:
	printf("Function%.4x\n",opcode);
	funclen = buffer_read_ushort(b);
	buffer_skip_bytes(b,funclen); // Not decompiling function.
	break;
#endif
#if 0
      case 0x100d:
	printf("Function%.4x\n",opcode);
	funclen = buffer_read_ushort(b);
	buffer_skip_bytes(b,funclen); // Not decompiling function.
	break;
#endif
      default:
	if (opcode >= 0x1000) {
	  printf("Function%.4x\n",opcode);
	  funclen = buffer_read_ushort(b);
	  buffer_skip_bytes(b,funclen); // Not decompiling function.
	} else {
	  printf("Unknown opcode %x. Exit.\n",opcode);
	  printf(" === End of attempt to decompile the compiled script\n");
	  return;
	}
	break;
      }
      break;
    }
  }
  printf(" === End of successful decompile of the compiled script\n");
}

void parse_scda(void *b, int size)
{
  unsigned char *cs;
  int loc;
  void *bcs;

  loc = buffer_getloc(b);
  cs = buffer_read_bytes(b,size);
  buffer_setloc(b,loc);
  printf("Skipping compiled script\n");
  buffer_skip_bytes(b,size);
  printf("skipping bytes\n");

  bcs = buffer_new(cs,size);

  parse_compiledscript(bcs);

  buffer_free(bcs);
  free(cs);
}

void parse_slsd(void *b)
{
  int n;
  float f;
  int *fint;
  unsigned char *fuc;
  int m;

  n = buffer_read_int(b);
  printf("Index of the script variable %i\n",n); // ok
  n = buffer_read_int(b);
  printf("%i\n",n); // uninitialized
  n = buffer_read_int(b); // == 0 in Fallout3.esm
  printf("%i\n",n);
  n = buffer_read_int(b); // == 0 in Fallout3.esm
  printf("%i\n",n);
  n = buffer_read_byte(b); // ok
  printf("Type of the script variable %i\n",n);
  n = buffer_read_byte(b); // uninitialized
  printf("%i\n",n);
  n = buffer_read_byte(b); // uninitialized
  printf("%i\n",n);
  n = buffer_read_byte(b); // uninitialized
  printf("%i\n",n);
#if 0
  n = buffer_read_int(b);
  printf("%i\n",n); // uninitialized
#else
#if 1
  // How to get these bits as float?
  // ((float *)(&n))[0] does not work.
  // Copying data byte by byte fails for the same reason
  // as above.
  // Do I really have to check each bit and built the float value
  // myself? I have no idea what is the format of float.
  m = buffer_getloc(b);
  n = buffer_read_int(b);
  printf("%i -- ",n);
  buffer_setloc(b,m);
  f = buffer_read_float(b);
  printf("%f\n",f);
#else
  // Why ((int *)(&f))[0] does not work?
  // Strange: fint = &f technique first did not work, but
  // adding fuc technique, fint techniues started working.
  // What is the proper way to examine bits of a float variable?
  f = buffer_read_float(b);
  // printf("%i -- %f\n",((int *)(&f))[0],f);
  fuc = &f;
  fint = &f;
  printf("%i -- %f -- %i %i %i %i\n",*fint,f,fuc[0],fuc[1],fuc[2],fuc[3]);
#endif
#endif
}

void parse_scro(void *b)
{
  int n;

  n = buffer_read_int(b);
  printf("Script Object FormID %i\n",n);
}

int global_sctx_file_number = 1;
char global_sctx_file_name[100];

void parse_sctx(void *b, int size)
{
  char *s2;
  FILE *fp;

  s2 = buffer_read_nstring(b,size);
  printf("===Script Begin\n%s\n===Script End\n",s2);

#if PRINT_SCTX_TO_FILE
  global_sctx_file_name[0] = '\0';
  sprintf(global_sctx_file_name,"sctx%.4i",global_sctx_file_number);
  fp = fopen(global_sctx_file_name,"w");
  fprintf(fp,"%s\n",s2);
  fclose(fp);
  global_sctx_file_number++;
#endif

  free(s2);
}


#include "parsebuffer_achr.c"

#include "parsebuffer_acre.c"

#include "parsebuffer_acti.c"

#include "parsebuffer_alch.c"

#include "parsebuffer_ammo.c"

#include "parsebuffer_anio.c"

#include "parsebuffer_appa.c"

#include "parsebuffer_armo.c"

#include "parsebuffer_book.c"

#include "parsebuffer_bsgn.c"

#include "parsebuffer_cell.c"

#include "parsebuffer_clas.c"

#include "parsebuffer_clmt.c"

#include "parsebuffer_clot.c"

#include "parsebuffer_cont.c"

#include "parsebuffer_crea.c"

#include "parsebuffer_csty.c"

#include "parsebuffer_dial.c"

#include "parsebuffer_door.c"

#include "parsebuffer_efsh.c"

#include "parsebuffer_ench.c"

#include "parsebuffer_eyes.c"

#include "parsebuffer_fact.c"

#include "parsebuffer_flor.c"

#include "parsebuffer_furn.c"

#include "parsebuffer_glob.c"

#include "parsebuffer_gmst.c"

#include "parsebuffer_gras.c"

#include "parsebuffer_hair.c"

#include "parsebuffer_idle.c"

#include "parsebuffer_info.c"

#include "parsebuffer_ingr.c"

#include "parsebuffer_keym.c"

#include "parsebuffer_land.c"

#include "parsebuffer_ligh.c"

#include "parsebuffer_lscr.c"

#include "parsebuffer_ltex.c"

#include "parsebuffer_lvlc.c"

#include "parsebuffer_lvli.c"

#include "parsebuffer_lvsp.c"

#include "parsebuffer_mgef.c"

#include "parsebuffer_misc.c"

#include "parsebuffer_npc.c"

#include "parsebuffer_pack.c"

#include "parsebuffer_pgrd.c"

#include "parsebuffer_qust.c"

#include "parsebuffer_race.c"

#include "parsebuffer_refr.c"

#include "parsebuffer_regn.c"

#include "parsebuffer_road.c"

#include "parsebuffer_sbsp.c"

#include "parsebuffer_scpt.c"

#include "parsebuffer_sgst.c"

#include "parsebuffer_skil.c"

#include "parsebuffer_slgm.c"

#include "parsebuffer_soun.c"

#include "parsebuffer_spel.c"

#include "parsebuffer_stat.c"

#include "parsebuffer_tes4.c"

#include "parsebuffer_tree.c"

#include "parsebuffer_watr.c"

#include "parsebuffer_weap.c"

#include "parsebuffer_wrld.c"

#include "parsebuffer_wthr.c"

int global_grouplevel = -1;
int global_locn = 0;
int global_loc[20];

void parsebuffer(void *b)
{
  int loc,loc2,n,m;
  char *s,*s2;
  void *b2;
  unsigned char *buffer;
  float f;
  unsigned int flags1;
  unsigned int flags2;
  int r;
  int mloc;
  int i,nn;
  void *btmp;
  unsigned char *obuffer = NULL;
  unsigned int flags;
  int nuncomp,nin,nout,err;
  int ndata;

  global_grouplevel++;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name 0: %s %i %i",s,global_grouplevel,
	   global_loc[global_locn] + loc);
    if (strcmp(s,"GRUP") == 0) {
      n = buffer_read_int(b); // uint groupsize;
      printf(" %i\n",global_loc[global_locn] + loc + n);
      printf("Groupsize = %i\n",n);
      // buffer_setloc(b,loc);
      // buffer_skip_bytes(b,20);
      // loc2 = buffer_getloc(b);
      s2 = buffer_read_string4(b); // label
      m = buffer_read_int(b); // int grouptype;
      switch (m) {
      case 0:
	printf("%s\n",s2);
	printf("Grouptype = 0 Top\n");
	break;
      case 1:
	printf("%i\n",((int *)s2)[0]);
	printf("Grouptype = 1 World Children\n");
	break;
      case 2:
	// printf("loc2 = %i\n",global_loc[global_locn] + loc2);
	printf("%i\n",((int *)s2)[0]);
	printf("Grouptype = 2 Interior Cell Block\n");
	break;
      case 3:
	printf("%i\n",((int *)s2)[0]);
	printf("Grouptype = 3 Interior Cell Sub-Block\n");
	break;
      case 4:
	// grid y,x -- reverse order
	printf("Cell loc %i %i (y x)\n",
	       (int)(((short *)s2)[0]),
	       (int)(((short *)s2)[1]));
	printf("Grouptype = 4 Exterior Cell Block\n");
	break;
      case 5:
	// grid y,x -- reverse order
	printf("Cell loc %i %i (y x)\n",
	       (int)(((short *)s2)[0]),
	       (int)(((short *)s2)[1]));
	printf("Grouptype = 5 Exterior Cell Sub-Block\n");
	break;
      case 6:
	printf("%i\n",((int *)s2)[0]);
	printf("Grouptype = 6 Cell Children\n");
	break;
      case 7:
	printf("%i\n",((int *)s2)[0]);
	printf("Grouptype = 7 Topic Children\n");
	break;
      case 8:
	printf("%i\n",((int *)s2)[0]);
	printf("Grouptype = 8 Cell Persistent Children\n");
	break;
      case 9:
	printf("%i\n",((int *)s2)[0]);
	printf("Grouptype = 9 Cell Temporary Children\n");
	break;
      case 10:
	printf("%i\n",((int *)s2)[0]);
	printf("Grouptype = 10 Cell Visible Distant Children\n");
	break;
      default:
	printf("Unknown group type\n");
	break;
      }
      free(s2);
      m = buffer_read_int(b); // int stamp;
      printf("Stamp = %i\n",m);
      // buffer_skip_bytes(b,n);
      buffer = buffer_getbuf(b);
      b2 = buffer_new(&(buffer[buffer_getloc(b)]),n-20);
      global_locn++;
      global_loc[global_locn] = global_loc[global_locn - 1] + buffer_getloc(b);
      parsebuffer(b2);
      buffer_free(b2);
      global_locn--;
      buffer_setloc(b,loc);
      buffer_skip_bytes(b,n);

      printf("Chunk extra: GRUP END\n");
    } else {
      printf("\n");
      buffer_setloc(b,loc);

#if 1
      // Moved from parsebuffer_ routines

  mloc = buffer_getloc(b);
  buffer_skip_bytes(b,4);
  ndata = buffer_read_int(b);
  flags1 = buffer_read_uint(b);
  printf("flags 1 = ");
  printflags(flags1);
  //      flags 1 = 0000,0000,0000,0000,0000,0000,0000,0000
  printf("                                                ^TES4:Master\n");
  printf("                                         ^REGN:Border Region\n");
  printf("                                     ^On Local Map?? + REFR/LIGH?:Casts Shadows\n");
  printf("                                    ^Quest Item + REFR:Persistent Reference\n");
  printf("                                   ^REFR:Initially Disabled\n");
  printf("                              ^Visible When Distant\n");
  printf("                           ^ACTI:Dangerous + CELL:Off limits\n");
  printf("                         ^Can't Wait\n");
  m = buffer_read_int(b);
  printf("formid = %i / formid = 0x%.8x\n",m,m);
  global_formid = m;
  flags2 = buffer_read_uint(b);
  printf("flags 2 = ");
  printflags(flags2);

  buffer_setloc(b,mloc);
  buffer_skip_bytes(b,20);

  if (flags1 & 0x00040000) {
    printf("Data is compressed\n");
    nuncomp = buffer_read_int(b);
    buffer = buffer_getbuf(b);
    nin = ndata-4;
    nout = 10*nin; // parsebuffer_land() had 100
    nout = nuncomp + 10;
    printf("numcomp = %i, nout = %i\n",nuncomp,nout);
    obuffer = (unsigned char *)malloc(nout*sizeof(unsigned char));
    err = uncompress(obuffer,(uLongf *)(&nout),&(buffer[buffer_getloc(b)]),nin);
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
    if (nout != nuncomp) {
      printf("Uncompressed data is of wrong size\n");
      exit(-1);
    }
    btmp = b;
    b = buffer_new(obuffer,(int)nout);
  } else {
    buffer = buffer_getbuf(b);
    btmp = b;
    b = buffer_new(&(buffer[buffer_getloc(btmp)]),ndata);
  }

#endif

      if (strcmp(s,"ACHR") == 0) {
	r = parsebuffer_achr(b);
      } else if (strcmp(s,"ACRE") == 0) {
	r = parsebuffer_acre(b);
      } else if (strcmp(s,"ACTI") == 0) {
	r = parsebuffer_acti(b);
      } else if (strcmp(s,"ALCH") == 0) {
	r = parsebuffer_alch(b);
      } else if (strcmp(s,"AMMO") == 0) {
	r = parsebuffer_ammo(b);
      } else if (strcmp(s,"ANIO") == 0) {
	r = parsebuffer_anio(b);
      } else if (strcmp(s,"APPA") == 0) {
	r = parsebuffer_appa(b);
      } else if (strcmp(s,"ARMO") == 0) {
	r = parsebuffer_armo(b);
      } else if (strcmp(s,"BOOK") == 0) {
	r = parsebuffer_book(b);
      } else if (strcmp(s,"BSGN") == 0) {
	r = parsebuffer_bsgn(b);
      } else if (strcmp(s,"CELL") == 0) {
	r = parsebuffer_cell(b);
      } else if (strcmp(s,"CLAS") == 0) {
	r = parsebuffer_clas(b);
      } else if (strcmp(s,"CLMT") == 0) {
	r = parsebuffer_clmt(b);
      } else if (strcmp(s,"CLOT") == 0) {
	r = parsebuffer_clot(b);
      } else if (strcmp(s,"CONT") == 0) {
	r = parsebuffer_cont(b);
      } else if (strcmp(s,"CREA") == 0) {
	r = parsebuffer_crea(b);
      } else if (strcmp(s,"CSTY") == 0) {
	r = parsebuffer_csty(b);
      } else if (strcmp(s,"DIAL") == 0) {
	r = parsebuffer_dial(b);
      } else if (strcmp(s,"DOOR") == 0) {
	r = parsebuffer_door(b);
      } else if (strcmp(s,"EFSH") == 0) {
	r = parsebuffer_efsh(b);
      } else if (strcmp(s,"ENCH") == 0) {
	r = parsebuffer_ench(b);
      } else if (strcmp(s,"EYES") == 0) {
	r = parsebuffer_eyes(b);
      } else if (strcmp(s,"FACT") == 0) {
	r = parsebuffer_fact(b);
      } else if (strcmp(s,"FLOR") == 0) {
	r = parsebuffer_flor(b);
      } else if (strcmp(s,"FURN") == 0) {
	r = parsebuffer_furn(b);
      } else if (strcmp(s,"GLOB") == 0) {
	r = parsebuffer_glob(b);
      } else if (strcmp(s,"GMST") == 0) {
	r = parsebuffer_gmst(b);
      } else if (strcmp(s,"GRAS") == 0) {
	r = parsebuffer_gras(b);
      } else if (strcmp(s,"HAIR") == 0) {
	r = parsebuffer_hair(b);
      } else if (strcmp(s,"IDLE") == 0) {
	r = parsebuffer_idle(b);
      } else if (strcmp(s,"INFO") == 0) {
	r = parsebuffer_info(b);
      } else if (strcmp(s,"INGR") == 0) {
	r = parsebuffer_ingr(b);
      } else if (strcmp(s,"KEYM") == 0) {
	r = parsebuffer_keym(b);
      } else if (strcmp(s,"LAND") == 0) {
	r = parsebuffer_land(b);
      } else if (strcmp(s,"LIGH") == 0) {
	r = parsebuffer_ligh(b);
      } else if (strcmp(s,"LSCR") == 0) {
	r = parsebuffer_lscr(b);
      } else if (strcmp(s,"LTEX") == 0) {
	r = parsebuffer_ltex(b);
      } else if (strcmp(s,"LVLC") == 0) {
	r = parsebuffer_lvlc(b);
      } else if (strcmp(s,"LVLI") == 0) {
	r = parsebuffer_lvli(b);
      } else if (strcmp(s,"LVSP") == 0) {
	r = parsebuffer_lvsp(b);
      } else if (strcmp(s,"MGEF") == 0) {
	r = parsebuffer_mgef(b);
      } else if (strcmp(s,"MISC") == 0) {
	r = parsebuffer_misc(b);
      } else if (strcmp(s,"NPC_") == 0) {
	r = parsebuffer_npc(b);
      } else if (strcmp(s,"PACK") == 0) {
	r = parsebuffer_pack(b);
      } else if (strcmp(s,"PGRD") == 0) {
	r = parsebuffer_pgrd(b);
      } else if (strcmp(s,"QUST") == 0) {
	r = parsebuffer_qust(b);
      } else if (strcmp(s,"RACE") == 0) {
	r = parsebuffer_race(b);
      } else if (strcmp(s,"REFR") == 0) {
	r = parsebuffer_refr(b);
      } else if (strcmp(s,"REGN") == 0) {
	r = parsebuffer_regn(b);
      } else if (strcmp(s,"ROAD") == 0) {
	r = parsebuffer_road(b);
      } else if (strcmp(s,"SBSP") == 0) {
	r = parsebuffer_sbsp(b);
      } else if (strcmp(s,"SCPT") == 0) {
	r = parsebuffer_scpt(b);
      } else if (strcmp(s,"SGST") == 0) {
	r = parsebuffer_sgst(b);
      } else if (strcmp(s,"SKIL") == 0) {
	r = parsebuffer_skil(b);
      } else if (strcmp(s,"SLGM") == 0) {
	r = parsebuffer_slgm(b);
      } else if (strcmp(s,"SOUN") == 0) {
	r = parsebuffer_soun(b);
      } else if (strcmp(s,"SPEL") == 0) {
	r = parsebuffer_spel(b);
      } else if (strcmp(s,"STAT") == 0) {
	r = parsebuffer_stat(b);
      } else if (strcmp(s,"TES4") == 0) {
	r = parsebuffer_tes4(b);
      } else if (strcmp(s,"TREE") == 0) {
	r = parsebuffer_tree(b);
      } else if (strcmp(s,"WATR") == 0) {
	r = parsebuffer_watr(b);
      } else if (strcmp(s,"WEAP") == 0) {
	r = parsebuffer_weap(b);
      } else if (strcmp(s,"WRLD") == 0) {
	r = parsebuffer_wrld(b);
      } else if (strcmp(s,"WTHR") == 0) {
	r = parsebuffer_wthr(b);
      } else {
	printf("Record %s unimplemented\n",s);
	exit(-1);
	// tessnipsource/Records.cs lists additional records which are
	// not listed at UESP Wiki / Tes4Mod:Mod_File_Format.
	// NONE
	// SNDG
	// TLOD
	// TOFT
      }
      if (r == 0) {
	printf("parsebuffer_ error\n");
	exit(-1);
      }
#if 1
      // Moved from parsebuffer_ routines

  buffer_free(b);
  b = btmp;
  buffer_setloc(b,mloc);
  buffer_skip_bytes(b,20);
  buffer_skip_bytes(b,ndata);
  if (flags1 & 0x00040000) {
    free(obuffer);
  }

#endif

    }
    free(s);
  }
  global_grouplevel--;
}


int main(int ac, char **av)
{
  void *m;
  unsigned char *buffer;
  int buflen,n,i;
  void *b;
  char *s;
  float f;
  int hierarchy;
  int loc;

#if 0
  if (ac < 2) {
    fprintf(stderr,"Usage: espparser <file> <targetdir>\n");
    exit(-1);
  }
#else
  if (ac < 1) {
    fprintf(stderr,"Usage: espparser <file>\n");
    exit(-1);
  }
#endif

  m = mmapfile_open_r(av[1]);
  buffer = mmapfile_getbuf(m);
  buflen = mmapfile_getsize(m);

  b = buffer_new(buffer,buflen);

  global_locn = 0;
  global_loc[0] = 0;

  parsebuffer(b);

  buffer_free(b);

  return 1;
}
