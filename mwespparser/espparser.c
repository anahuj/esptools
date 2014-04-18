
// Copyright 2006-2009 Juhana Sadeharju
// GNU GPL

// espparser: extracts the data from Morrowind ESP file

// Usage: espparser <esp file> <target directory>


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

#if 0
// Oblivion mod file structures.
typedef struct {
  int size;
  unsigned char *data;
} ty_oblivion_chunk;
#endif

// For recursive parsing we windowize the original buffer.
void *bufferstack[128];

int global_formid;

// Version needed for ModRegion.
int global_version = -1; // 0 Morrowind 1 Tribunal + Bloodmoon

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

void printflags16(unsigned int n)
{
  unsigned int k;
  int i;

  k = 0x00008000;
  for (i = 0; i < 16; i++) {
    if ((n & k) != 0) {
      printf("1");
    } else {
      printf("0");
    }
    k = k >> 1;
    if (((i % 4) == 3) && (i != 15)) {
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

char global_printhexdump[50];

void printhexdump(void *b, int offset, int length)
{
  int loc;
  int i,n;
  int k;
  int m;

  loc = buffer_getloc(b);
  buffer_setloc(b,loc + offset);

  for (m = 0; m < 50; m++) {
    global_printhexdump[m] = '\0';
  }

  k = 0;
  for (i = 0; i < length; i++) {
    n = buffer_read_ubyte(b);
    printf("%2x",n);
    if ((n >= 32) && (n <= 126)) {
      global_printhexdump[k] = (char)n;
    } else {
      global_printhexdump[k] = '.';
    }
    k++;
    if (i < length - 1) {
      if (k == 12) {
	printf("  %s\n",global_printhexdump);
	for (m = 0; m < 50; m++) {
	  global_printhexdump[m] = '\0';
	}
	k = 0;
      } else {
	printf(" ");
      }
    }
  }
  printf("  %s\n",global_printhexdump);

  buffer_setloc(b,loc);
}

void parse_compiledscript_mw(void *b)
{
  int n,n2,n3;
  int opcode;
  int opcodelen;
  int explen;
  int funclen;
  int varop;
  int varindex;
  int refvarop;
  int refvarindex;
  char *s2;
  char *s3;
  float f,f2,f3,f4;
  int i,k,m;

  printf(" === Attempting to decompile the compiled script\n");
  while (buffer_eof(b) != 1) {
    opcode = buffer_read_ushort(b);
    switch (opcode) {
    case 0x106:
      printf("if\n");
      n = buffer_read_ubyte(b);
      printf("JmpOps %i\n",n);
      n = buffer_read_ubyte(b);
      printf("ExpLen %i\n",n);
      explen = n;
      buffer_skip_bytes(b,explen); // Decompiling top level codes only.
      break;
    case 0x107:
      printf("else\n");
      n = buffer_read_ubyte(b);
      printf("JmpOps %i\n",n);
      break;
    case 0x108:
      printf("elseif\n");
      n = buffer_read_ubyte(b);
      printf("JmpOps %i\n",n);
      n = buffer_read_ubyte(b);
      printf("ExpLen %i\n",n);
      explen = n;
      buffer_skip_bytes(b,explen); // Decompiling top level codes only.
      break;
    case 0x10a:
      printf("while\n");
      n = buffer_read_ubyte(b);
      printf("JmpOps %i\n",n);
      n = buffer_read_ubyte(b);
      printf("ExpLen %i\n",n);
      explen = n;
      buffer_skip_bytes(b,explen); // Decompiling top level codes only.
      break;
    case 0x10cc:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      n = buffer_read_short(b);
      n2 = buffer_read_short(b);
      printf("Journal \"%s\" %i %i\n",s2,n,n2);
      free(s2);
      break;
    case 0x010c:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf("\"%s\"->\n",s2);
      free(s2);
      break;
    case 0x1019:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf("StartCombat \"%s\"\n",s2);
      free(s2);
      break;
    case 0x0105:
      printf("Set\n");
      n = buffer_read_ubyte(b);
      printf("0x%x\n",n);
      varop = n;
      if (varop == 0x73) {
	// local var
	n = buffer_read_short(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	s2 = buffer_read_nstring(b,n); // Not string: almaScript
	printf("\"%s\"\n",s2);
	free(s2);
      } else if (varop == 0x56) {
	// non-local var
	n = buffer_read_short(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	s2 = buffer_read_nstring(b,n);
	printf("\"%s\"\n",s2);
	free(s2);
      } else if (varop == 0x66) {
	n = buffer_read_short(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	s2 = buffer_read_nstring(b,n); // Not string: AzuraEnd
	printf("\"%s\"\n",s2);
	free(s2);
      } else if (varop == 0x72) {
	n = buffer_read_ubyte(b);
	s2 = buffer_read_nstring(b,n);
	printf("\"%s\"\n",s2);
	free(s2);
	n = buffer_read_ubyte(b);
	printf("varop 73, did read: %x\n",n);
	n = buffer_read_short(b);
	printf("varindex %i\n",n);
	n = buffer_read_ubyte(b);
	s2 = buffer_read_nstring(b,n);
	printf("\"%s\"\n",s2);
	free(s2);
      } else if (varop == 0x6d) {
	n = buffer_read_ubyte(b);
	s2 = buffer_read_nstring(b,n);
	printf("\"%s\"\n",s2);
	free(s2);
	n = buffer_read_ubyte(b);
	printf("varop 66, did read: %x\n",n);
	n = buffer_read_short(b);
	printf("varindex %i\n",n);
	n = buffer_read_ubyte(b);
	s2 = buffer_read_nstring(b,n);
	printf("\"%s\"\n",s2);
	free(s2);
      } else if (varop == 0x47) {
	n = buffer_read_ubyte(b);
	s2 = buffer_read_nstring(b,n);
	printf("\"%s\"\n",s2);
	free(s2);
	n = buffer_read_ubyte(b);
	s2 = buffer_read_nstring(b,n);
	printf("\"%s\"\n",s2);
	free(s2);
      } else {
	printf("Unknown varop 0x%x. Exit.\n",varop);
	printhexdump(b,-20,60);
	printf(" === End of attempt to decompile the compiled script\n");
	return;
      }
      break;
    case 0x1021:
      n = buffer_read_short(b);
      printf("Random %i\n",n);
      break;
    case 0x1014:
      n = buffer_read_byte(b);
      n2 = buffer_read_byte(b);
      n3 = buffer_read_byte(b);
      printf("PlayGroup %i %i %i\n",n,n2,n3);
      break;
    case 0x1015:
      n = buffer_read_byte(b);
      n2 = buffer_read_byte(b);
      n3 = buffer_read_short(b);
      printf("LoopGroup %i %i %i\n",n,n2,n3);
      break;
    case 0x111b:
      printf("Say\n");
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf("\"%s\"\n",s2);
      free(s2);
      n = buffer_read_ushort(b);
      s2 = buffer_read_nstring(b,n);
      printf("\"%s\"\n",s2);
      free(s2);
      break;
    case 0x10f8:
      f = buffer_read_float(b);
      f2 = buffer_read_float(b);
      f3 = buffer_read_float(b);
      n = buffer_read_byte(b);
      printf("AiTravel %f %f %f %i\n",f,f2,f3,n);
      break;
    case 0x10f6:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf("AiFollow \"%s\"\n",s2);

      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);

      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);

      f = buffer_read_float(b);
      printf("%f\n",f);
      n = buffer_read_byte(b);
      printf("%i\n",n);
      free(s2);
      break;
    case 0x10f9:
      f = buffer_read_float(b);
      f2 = buffer_read_float(b);
      f3 = buffer_read_float(b);
      k = buffer_read_short(b);
      printf("AiWander %f %f %f %i\n",f,f2,f3,k);
      for (i = 0; i < k; i++) {
	n = buffer_read_short(b);
	printf("%i\n",n);
      }
      n = buffer_read_byte(b);
      printf("%i\n",n);
      break;
    case 0x11a5:
      f = buffer_read_float(b);
      printf("HurtCollidingActor %f\n",f);
      break;
    case 0x108e:
      f = buffer_read_float(b);
      printf("ModHealth %f\n",f);
      break;
    case 0x1100:
      f = buffer_read_float(b);
      printf("SetFight %f\n",f);
      break;
    case 0x1103:
      f = buffer_read_float(b);
      printf("SetFlee %f\n",f);
      break;
    case 0x1106:
      f = buffer_read_float(b);
      printf("SetAlarm %f\n",f);
      break;
    case 0x1109:
      f = buffer_read_float(b);
      printf("SetHello %f\n",f);
      break;
    case 0x1134:
      f = buffer_read_float(b);
      printf("ModCurrentFatigue %f\n",f);
      break;
    case 0x1135:
      f = buffer_read_float(b);
      printf("HurtStandingActor %f\n",f);
      break;
    case 0x109a:
      f = buffer_read_float(b);
      printf("ModDisposition %f\n",f);
      break;
    case 0x108d:
      f = buffer_read_float(b);
      printf("SetHealth %f\n",f);
      break;
    case 0x104b:
      f = buffer_read_float(b);
      printf("SetLongblade %f\n",f);
      break;
    case 0x103c:
      f = buffer_read_float(b);
      printf("SetBlock %f\n",f);
      break;
    case 0x1081:
      f = buffer_read_float(b);
      printf("SetMarksman %f\n",f);
      break;
    case 0x1030:
      f = buffer_read_float(b);
      printf("SetSpeed %f\n",f);
      break;
    case 0x1054:
      f = buffer_read_float(b);
      printf("SetAthletics %f\n",f);
      break;
    case 0x106c:
      f = buffer_read_float(b);
      printf("SetAlchemy %f\n",f);
      break;
    case 0x1057:
      f = buffer_read_float(b);
      printf("SetEnchant %f\n",f);
      break;
    case 0x105a:
      f = buffer_read_float(b);
      printf("SetDestruction %f\n",f);
      break;
    case 0x105d:
      f = buffer_read_float(b);
      printf("SetAlteration %f\n",f);
      break;
    case 0x1060:
      f = buffer_read_float(b);
      printf("SetIllusion %f\n",f);
      break;
    case 0x1063:
      f = buffer_read_float(b);
      printf("SetConjuration %f\n",f);
      break;
    case 0x1066:
      f = buffer_read_float(b);
      printf("SetMysticism %f\n",f);
      break;
    case 0x1069:
      f = buffer_read_float(b);
      printf("SetRestoration %f\n",f);
      break;
    case 0x1024:
      f = buffer_read_float(b);
      printf("SetStrength %f\n",f);
      break;
    case 0x1090:
      f = buffer_read_float(b);
      printf("SetMagicka %f\n",f);
      break;
    case 0x1093:
      f = buffer_read_float(b);
      printf("SetFatigue %f\n",f);
      break;
    case 0x1099:
      f = buffer_read_float(b);
      printf("SetDisposition %f\n",f);
      break;
    case 0x1097:
      f = buffer_read_float(b);
      printf("ModReputation %f\n",f);
      break;
    case 0x1094:
      f = buffer_read_float(b);
      printf("ModFatigue %f\n",f);
      break;
    case 0x1025:
      f = buffer_read_float(b);
      printf("ModStrength %f\n",f);
      break;
    case 0x1031:
      f = buffer_read_float(b);
      printf("ModSpeed %f\n",f);
      break;
    case 0x103d:
      f = buffer_read_float(b);
      printf("ModBlock %f\n",f);
      break;
    case 0x1043:
      f = buffer_read_float(b);
      printf("ModMediumArmor %f\n",f);
      break;
    case 0x107f:
      f = buffer_read_float(b);
      printf("ModShortBlade %f\n",f);
      break;
    case 0x1028:
      f = buffer_read_float(b);
      printf("ModIntelligence %f\n",f);
      break;
    case 0x102b:
      f = buffer_read_float(b);
      printf("ModWillpower %f\n",f);
      break;
    case 0x106a:
      f = buffer_read_float(b);
      printf("ModRestoration %f\n",f);
      break;
    case 0x1085:
      f = buffer_read_float(b);
      printf("ModMercantile %f\n",f);
      break;
    case 0x1101:
      f = buffer_read_float(b);
      printf("ModFight %f\n",f);
      break;
    case 0x1132:
      m = buffer_getloc(b);
      n = buffer_read_ubyte(b);
      printf("1132: vartest 0x%x\n",n);
      if (n == 0x66) {
	n2 = buffer_read_ushort(b);
	printf("1132: varindex %i\n",n2);
	n2 = buffer_read_ubyte(b);
	printf("1132: %i\n",n2);
      } else {
	buffer_setloc(b,m);
	f = buffer_read_float(b);
	printf("ModCurrentHealth %f\n",f);
      }
      break;
    case 0x1130:
      f = buffer_read_float(b);
      printf("FadeOut %f\n",f);
      break;
    case 0x102e:
      f = buffer_read_float(b);
      printf("ModAgility %f\n",f);
      break;
    case 0x1091:
      f = buffer_read_float(b);
      printf("ModMagicka %f\n",f);
      break;
    case 0x1131:
      f = buffer_read_float(b);
      printf("FadeIn %f\n",f);
      break;
    case 0x1034:
      f = buffer_read_float(b);
      printf("ModEndurance %f\n",f);
      break;
    case 0x1037:
      f = buffer_read_float(b);
      printf("ModPersonality %f\n",f);
      break;
    case 0x1055:
      f = buffer_read_float(b);
      printf("ModAthletics %f\n",f);
      break;
    case 0x103a:
      f = buffer_read_float(b);
      printf("ModLuck %f\n",f);
      break;
    case 0x104c:
      f = buffer_read_float(b);
      printf("ModLongblade %f\n",f);
      break;
    case 0x1046:
      f = buffer_read_float(b);
      printf("ModHeavyarmor %f\n",f);
      break;
    case 0x1052:
      f = buffer_read_float(b);
      printf("ModSpear %f\n",f);
      break;
    case 0x104f:
      f = buffer_read_float(b);
      printf("ModAxe %f\n",f);
      break;
    case 0x1049:
      f = buffer_read_float(b);
      printf("ModBluntweapon %f\n",f);
      break;
    case 0x1040:
      f = buffer_read_float(b);
      printf("ModArmorer %f\n",f);
      break;
    case 0x1082:
      f = buffer_read_float(b);
      printf("ModMarksman %f\n",f);
      break;
    case 0x102a:
      f = buffer_read_float(b);
      printf("SetWillpower %f\n",f);
      break;
    case 0x102d:
      f = buffer_read_float(b);
      printf("SetAgility %f\n",f);
      break;
    case 0x1033:
      f = buffer_read_float(b);
      printf("SetEndurance %f\n",f);
      break;
    case 0x1045:
      f = buffer_read_float(b);
      printf("SetHeavyarmor %f\n",f);
      break;
    case 0x1042:
      f = buffer_read_float(b);
      printf("SetMediumarmor %f\n",f);
      break;
    case 0x1051:
      f = buffer_read_float(b);
      printf("SetSpear %f\n",f);
      break;
    case 0x104e:
      f = buffer_read_float(b);
      printf("SetAxe %f\n",f);
      break;
    case 0x1048:
      f = buffer_read_float(b);
      printf("SetBluntweapon %f\n",f);
      break;
    case 0x103f:
      f = buffer_read_float(b);
      printf("SetArmorer %f\n",f);
      break;
    case 0x118e:
      f = buffer_read_float(b);
      printf("SetScale %f\n",f);
      break;
    case 0x10c2:
      f = buffer_read_float(b);
      printf("ModResistParalysis %f\n",f);
      break;
    case 0x10bf:
      f = buffer_read_float(b);
      printf("ModResistPoison %f\n",f);
      break;
    case 0x10aa:
      f = buffer_read_float(b);
      printf("ModResistMagicka %f\n",f);
      break;
    case 0x10ad:
      f = buffer_read_float(b);
      printf("ModResistFire %f\n",f);
      break;
    case 0x10b0:
      f = buffer_read_float(b);
      printf("ModResistFrost %f\n",f);
      break;
#if 0
    case 0x:
      f = buffer_read_float(b);
      printf(" %f\n",f);
      break;
#endif
    case 0x1155:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      n = buffer_read_byte(b);
      printf("PlayBink \"%s\" %i\n",s2,n);
      free(s2);
      break;
    case 0x101b:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf("StartScript \"%s\"\n",s2);
      free(s2);
      break;
    case 0x101c:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf("StopScript \"%s\"\n",s2);
      free(s2);
      break;
    case 0x1022:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf("AddTopic \"%s\"\n",s2);
      free(s2);
      break;
    case 0x10d0:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf("PCRaiseRank \"%s\"\n",s2);
      free(s2);
      break;
    case 0x10d3:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf("PCClearExpelled \"%s\"\n",s2);
      free(s2);
      break;
    case 0x10ec:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf("RemoveSoulGem \"%s\"\n",s2);
      free(s2);
      break;
    case 0x10d9:
      f = buffer_read_float(b);
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf("ModPCFacRep %f \"%s\"\n",f,s2);
      free(s2);
      break;
    case 0x10f4:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      n2 = buffer_read_ushort(b);
      f = buffer_read_float(b);
      f2 = buffer_read_float(b);
      f3 = buffer_read_float(b);
      n3 = buffer_read_ubyte(b);
      printf("AIEscort \"%s\" %i %f %f %f %i\n",s2,n2,f,f2,f3,n3);
      free(s2);
      break;
    case 0x110d:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      n = buffer_read_ushort(b);
      printf("Drop \"%s\" %i\n",s2,n);
      free(s2);
      break;
    case 0x11ba:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      n = buffer_read_ushort(b);
      f = buffer_read_float(b);
      n2 = buffer_read_ushort(b);
      printf("PlaceAtMe \"%s\" %i %f %i\n",s2,n,f,n2);
      free(s2);
      break;
    case 0x112b:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      f = buffer_read_float(b);
      f2 = buffer_read_float(b);
      printf("PlaySoundVP \"%s\" %f %f\n",s2,f,f2);
      free(s2);
      break;
    case 0x112d:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      f = buffer_read_float(b);
      f2 = buffer_read_float(b);
      printf("Playsound3DVP \"%s\" %f %f\n",s2,f,f2);
      free(s2);
      break;
    case 0x113b:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf("PCJoinFaction \"%s\"\n",s2);
      free(s2);
      break;
    case 0x1152:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf("ShowMap \"%s\"\n",s2);
      free(s2);
      break;
    case 0x1111:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      n = buffer_read_ubyte(b);
      s3 = buffer_read_nstring(b,n);
      n = buffer_read_short(b);
      printf("ModFactionReaction \"%s\" \"%s\" %i\n",s2,s3,n);
      free(s3);
      free(s2);
      break;
#if 0
    case 0x:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf(" \"%s\"\n",s2);
      free(s2);
      break;
    case 0x:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf(" \"%s\"\n",s2);
      free(s2);
      break;
#endif
    case 0x111d:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf("AddSpell \"%s\"\n",s2);
      free(s2);
      break;
    case 0x111e:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf("RemoveSpell \"%s\"\n",s2);
      free(s2);
      break;
    case 0x11ad:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf("ExplodeSpell \"%s\"\n",s2);
      free(s2);
      break;
    case 0x1191:
      n2 = buffer_read_ubyte(b);
      printf("should be 0x66 / 0x%x\n",n2);
      n2 = buffer_read_ushort(b);
      n3 = buffer_read_ubyte(b);
      printf("SetWaterLevel varop %i %i\n",n2,n3);
      break;
    case 0x1192:
      n2 = buffer_read_ubyte(b);
      printf("should be 0x66 / 0x%x\n",n2);
      n2 = buffer_read_ushort(b);
      n3 = buffer_read_ubyte(b);
      printf("ModWaterLevel varop %i %i\n",n2,n3);
      break;
    case 0x109c:
      n2 = buffer_read_ubyte(b);
      printf("should be 0x73 / 0x%x\n",n2);
      n2 = buffer_read_ushort(b);
      n3 = buffer_read_ubyte(b);
      printf("SetPCCrimeLevel varop %i %i\n",n2,n3);
      break;
    case 0x100b:
      n = buffer_read_ubyte(b);
      n2 = buffer_read_ubyte(b);
      printf("should be 0x73 / 0x%x\n",n2);
      n2 = buffer_read_ushort(b);
      n3 = buffer_read_ubyte(b);
      printf("SetPos %c varop %i %i\n",n,n2,n3);
      break;
    case 0x100d:
      n = buffer_read_ubyte(b);
      n2 = buffer_read_ubyte(b);
      printf("should be 0x73 / 0x%x\n",n2);
      n2 = buffer_read_ushort(b);
      n3 = buffer_read_ubyte(b);
      printf("SetAngle %c varop %i %i\n",n,n2,n3);
      break;
    case 0x1004:
      f = buffer_read_float(b);
      f2 = buffer_read_float(b);
      f3 = buffer_read_float(b);
      n = buffer_read_int(b);
      printf("Position %f %f %f %i\n",f,f2,f3,n);
      break;
    case 0x1005:
      f = buffer_read_float(b);
      f2 = buffer_read_float(b);
      f3 = buffer_read_float(b);
      f4 = buffer_read_float(b);
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf("PositionCell %f %f %f %f \"%s\"\n",f,f2,f3,f4,s2);
      free(s2);
      break;
    case 0x1195:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      f = buffer_read_float(b);
      f2 = buffer_read_float(b);
      f3 = buffer_read_float(b);
      n = buffer_read_int(b);
      printf("PlaceItem \"%s\" %f %f %f %i\n",s2,f,f2,f3,n);
      free(s2);
      break;
    case 0x1196:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      n = buffer_read_ubyte(b);
      s3 = buffer_read_nstring(b,n);
      f = buffer_read_float(b);
      f2 = buffer_read_float(b);
      f3 = buffer_read_float(b);
      f4 = buffer_read_float(b);
      printf("PlaceItemCell \"%s\" \"%s\" %f %f %f %f\n",s2,s3,f,f2,f3,f4);
      free(s3);
      free(s2);
      break;
    case 0x1006:
      n = buffer_read_ubyte(b);
      f = buffer_read_float(b);
      printf("Move %c %f\n",n,f);
      break;
    case 0x1007:
      n = buffer_read_ubyte(b);
      f = buffer_read_float(b);
      printf("Rotate %c %f\n",n,f);
      break;
    case 0x1008:
      n = buffer_read_ubyte(b);
      f = buffer_read_float(b);
      printf("MoveWorld %c %f\n",n,f);
      break;
    case 0x1009:
      n = buffer_read_ubyte(b);
      f = buffer_read_float(b);
      printf("RotateWorld %c %f\n",n,f);
      break;
    case 0x1162:
      n = buffer_read_int(b);
      n2 = buffer_read_int(b);
      printf("Face %i %i\n",n,n2);
      break;
    case 0x1123:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      n = buffer_read_ubyte(b);
      s3 = buffer_read_nstring(b,n);
      printf("Cast \"%s\" \"%s\"\n",s2,s3);
      free(s3);
      free(s2);
      break;
    case 0x10d4:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      n = buffer_read_ushort(b);
      printf("AddItem \"%s\" %i\n",s2,n);
      free(s2);
      break;
    case 0x10d5:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      n = buffer_read_ushort(b);
      printf("RemoveItem \"%s\" %i\n",s2,n);
      free(s2);
      break;
    case 0x1002:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf("PlaySound \"%s\"\n",s2);
      free(s2);
      break;
    case 0x112c:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf("PlaySound3D \"%s\"\n",s2);
      free(s2);
      break;
    case 0x112e:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf("PlayLoopSound3D \"%s\"\n",s2);
      free(s2);
      break;
    case 0x112f:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      f = buffer_read_float(b);
      f2 = buffer_read_float(b);
      printf("PlayLoopSound3DVP \"%s\" %f %f\n",s2,f,f2);
      free(s2);
      break;
    case 0x1151:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf("StopSound \"%s\"\n",s2);
      free(s2);
      break;
    case 0x1003:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      printf("StreamMusic \"%s\"\n",s2);
      free(s2);
      break;
    case 0x10e6:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      n2 = buffer_read_ushort(b);
      f = buffer_read_float(b);
      n3 = buffer_read_ushort(b);
      printf("PlaceAtPC \"%s\" %i %f %i\n",s2,n2,f,n3);
      free(s2);
      break;
    case 0x11ab:
      n = buffer_read_short(b);
      printf("SetDelete %i\n",n);
      break;
    case 0x1136:
      n = buffer_read_short(b);
      printf("Lock %i\n",n);
      break;
    case 0x1124:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      n2 = buffer_read_short(b);
      printf("ChangeWeather \"%s\" %i\n",s2,n2);
      free(s2);
      break;
    case 0x1125:
      n = buffer_read_ubyte(b);
      s2 = buffer_read_nstring(b,n);
      n2 = buffer_read_ubyte(b);
      n3 = buffer_read_ubyte(b);
      printf("ModRegion \"%s\" %i %i\n",s2,n2,n3);
      free(s2);
      // Morrowind.esm : 6 bytes
      // Tribunal.esm : 8 bytes
      // Bloodmoon.esm : 8 bytes
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      if (global_version == 1) {
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
      }
      break;
    case 0x1000:
      n = buffer_read_ushort(b);
      s2 = buffer_read_nstring(b,n);
      printf("MessageBox \"%s\"\n",s2);
      free(s2);
      k = buffer_read_ubyte(b);
      printf("messagebox variables %i\n",k);
      for (i = 0; i < k; i++) {
	n = buffer_read_ubyte(b);
	printf("varop 0x66 / 0x%x\n",n);
	n = buffer_read_ushort(b);
	printf("varindex %i\n",n);
      }
      k = buffer_read_ubyte(b);
      printf("messagebox answers %i\n",k);
      for (i = 0; i < k; i++) {
	n = buffer_read_ubyte(b);
	s2 = buffer_read_nstring(b,n);
	printf("\"%s\"\n",s2);
	free(s2);
      }
      break;
    case 0x0124:
      printf("Return\n");
      break;
    case 0x0109:
      printf("endif\n");
      break;
    case 0x010b:
      printf("endwhile\n");
      break;
    case 0x0101:
      printf("end\n");
      break;
    case 0x10da:
      printf("Enable\n");
      break;
    case 0x10db:
      printf("Disable\n");
      break;
    case 0x10dc:
      printf("GetDisabled\n");
      break;
    case 0x1017:
      printf("Activate\n");
      break;
    case 0x1018:
      printf("OnActivate\n");
      break;
    case 0x1012:
      printf("GetSecondsPassed\n");
      break;
    case 0x1020:
      printf("MenuMode\n");
      break;
    case 0x10ce:
      printf("RaiseRank\n");
      break;
    case 0x10fe:
      printf("GetDeadCount\n");
      break;
    case 0x10e8:
      printf("ForceGreeting\n");
      break;
    case 0x10dd:
      printf("EnablePlayerControls\n");
      break;
    case 0x10de:
      printf("DisablePlayerControls\n");
      break;
    case 0x1163:
      printf("ForceSneak\n");
      break;
    case 0x1164:
      printf("ClearForceSneak\n");
      break;
    case 0x10e7:
      printf("Resurrect\n");
      break;
    case 0x10e1:
      printf("WakeUpPC\n");
      break;
    case 0x10ee:
      printf("EnableTeleporting\n");
      break;
    case 0x10ef:
      printf("DisableTeleporting\n");
      break;
    case 0x1193:
      printf("EnableLevitation\n");
      break;
    case 0x1194:
      printf("DisableLevitation\n");
      break;
    case 0x1137:
      printf("Unlock\n");
      break;
    case 0x10e9:
      printf("GoToJail\n");
      break;
    case 0x101a:
      printf("StopCombat\n");
      break;
    case 0x115f:
      printf("DontSaveObject\n");
      break;
    case 0x013f:
      printf("EnableRest\n");
      break;
    case 0x1010:
      printf("SetAtStart\n");
      break;
    case 0x10e3:
      printf("DisablePlayerViewSwitch\n");
      break;
    case 0x10e5:
      printf("ShowRestMenu\n");
      break;
    case 0x1117:
      printf("EnableStatsMenu\n");
      break;
    case 0x1118:
      printf("EnableInventoryMenu\n");
      break;
    case 0x1119:
      printf("EnableMapMenu\n");
      break;
    case 0x111a:
      printf("EnableMagicMenu\n");
      break;
    case 0x1126:
      printf("EnableNameMenu\n");
      break;
    case 0x1127:
      printf("EnableRaceMenu\n");
      break;
    case 0x1128:
      printf("EnableClassMenu\n");
      break;
    case 0x1129:
      printf("EnableBirthMenu\n");
      break;
    case 0x113f:
      printf("EnablePlayerJumping\n");
      break;
    case 0x1140:
      printf("DisablePlayerJumping\n");
      break;
    case 0x114c:
      printf("DisableVanityMode\n");
      break;
    case 0x114f:
      printf("PayFine\n");
      break;
    case 0x1159:
      printf("EnablePlayerFighting\n");
      break;
    case 0x115a:
      printf("DisablePlayerFighting\n");
      break;
    case 0x115c:
      printf("EnablePlayerMagic\n");
      break;
    case 0x115d:
      printf("DisablePlayerMagic\n");
      break;
    case 0x1160:
      printf("EnableStatReviewMenu\n");
      break;
    case 0x10e2:
      printf("EnablePlayerViewSwitch\n");
      break;
    case 0x114b:
      printf("EnableVanityMode\n");
      break;
    case 0x1166:
      printf("Fall\n");
      break;
    case 0x119a:
      printf("ForceRun\n");
      break;
    case 0x11b3:
      printf("BecomeWerewolf\n");
      break;
    case 0x11b4:
      printf("UndoWerewolf\n");
      break;
    case 0x11b7:
      printf("TurnMoonRed\n");
      break;
    case 0x11b8:
      printf("TurnMoonWhite\n");
      break;
    case 0x11b9:
      printf("SetWereWolfAcrobatics\n");
      break;
    default:
      printf("Unknown opcode %x. Exit.\n",opcode);
      printhexdump(b,-20,60);
      printf(" === End of attempt to decompile the compiled script\n");
      return;
      break;
#if 0
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
#endif
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


#include "parsebuffer_acti.c"

#include "parsebuffer_alch.c"

#include "parsebuffer_appa.c"

#include "parsebuffer_armo.c"

#include "parsebuffer_body.c"

#include "parsebuffer_book.c"

#include "parsebuffer_bsgn.c"

#include "parsebuffer_cell.c"

#include "parsebuffer_clas.c"

#include "parsebuffer_clot.c"

#include "parsebuffer_cntc.c"

#include "parsebuffer_cont.c"

#include "parsebuffer_crea.c"

#include "parsebuffer_crec.c"

#include "parsebuffer_dial.c"

#include "parsebuffer_door.c"

#include "parsebuffer_ench.c"

#include "parsebuffer_fact.c"

#include "parsebuffer_fmap.c"

#include "parsebuffer_game.c"

#include "parsebuffer_glob.c"

#include "parsebuffer_gmst.c"

#include "parsebuffer_info.c"

#include "parsebuffer_ingr.c"

#include "parsebuffer_jour.c"

#include "parsebuffer_klst.c"

#include "parsebuffer_land.c"

#include "parsebuffer_levc.c"

#include "parsebuffer_levi.c"

#include "parsebuffer_ligh.c"

#include "parsebuffer_lock.c"

#include "parsebuffer_ltex.c"

#include "parsebuffer_mgef.c"

#include "parsebuffer_misc.c"

#include "parsebuffer_npc.c"

#include "parsebuffer_npcc.c"

#include "parsebuffer_pcdt.c"

#include "parsebuffer_pgrd.c"

#include "parsebuffer_prob.c"

#include "parsebuffer_ques.c"

#include "parsebuffer_race.c"

#include "parsebuffer_refr.c"

#include "parsebuffer_regn.c"

#include "parsebuffer_repa.c"

#include "parsebuffer_scpt.c"

#include "parsebuffer_skil.c"

#include "parsebuffer_sndg.c"

#include "parsebuffer_soun.c"

#include "parsebuffer_spel.c"

#include "parsebuffer_splm.c"

#include "parsebuffer_sscr.c"

#include "parsebuffer_stat.c"

#include "parsebuffer_stln.c"

#include "parsebuffer_tes3.c"

#include "parsebuffer_weap.c"


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
#if 0
  printf("                                                ^TES4:Master\n");
  printf("                                         ^REGN:Border Region\n");
  printf("                                     ^On Local Map?? + REFR/LIGH?:Casts Shadows\n");
  printf("                                    ^Quest Item + REFR:Persistent Reference\n");
  printf("                                   ^REFR:Initially Disabled\n");
  printf("                              ^Visible When Distant\n");
  printf("                           ^ACTI:Dangerous + CELL:Off limits\n");
  printf("                         ^Can't Wait\n");
#endif
#if 0
  m = buffer_read_int(b);
  printf("formid = %i / formid = 0x%.8x\n",m,m);
  global_formid = m;
#endif
  flags2 = buffer_read_uint(b);
  printf("flags 2 = ");
  printflags(flags2);
  //      flags 2 = 0000,0000,0000,0000,0000,0000,0000,0000
  printf("                                    ^References Persist + Corpses Persist\n");
  printf("                                ^Blocked\n");

  buffer_setloc(b,mloc);
  buffer_skip_bytes(b,16); // MW

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
    b = buffer_new(&(buffer[buffer_getloc(btmp)]),ndata); // MW -4
  }

#endif

      if (strcmp(s,"ACTI") == 0) {
	r = parsebuffer_acti(b);
      } else if (strcmp(s,"ALCH") == 0) {
	r = parsebuffer_alch(b);
      } else if (strcmp(s,"APPA") == 0) {
	r = parsebuffer_appa(b);
      } else if (strcmp(s,"ARMO") == 0) {
	r = parsebuffer_armo(b);
      } else if (strcmp(s,"BODY") == 0) {
	r = parsebuffer_body(b);
      } else if (strcmp(s,"BOOK") == 0) {
	r = parsebuffer_book(b);
      } else if (strcmp(s,"BSGN") == 0) {
	r = parsebuffer_bsgn(b);
      } else if (strcmp(s,"CELL") == 0) {
	r = parsebuffer_cell(b);
      } else if (strcmp(s,"CLAS") == 0) {
	r = parsebuffer_clas(b);
      } else if (strcmp(s,"CLOT") == 0) {
	r = parsebuffer_clot(b);
      } else if (strcmp(s,"CNTC") == 0) {
	r = parsebuffer_cntc(b);
      } else if (strcmp(s,"CONT") == 0) {
	r = parsebuffer_cont(b);
      } else if (strcmp(s,"CREA") == 0) {
	r = parsebuffer_crea(b);
      } else if (strcmp(s,"CREC") == 0) {
	r = parsebuffer_crec(b);
      } else if (strcmp(s,"DIAL") == 0) {
	r = parsebuffer_dial(b);
      } else if (strcmp(s,"DOOR") == 0) {
	r = parsebuffer_door(b);
      } else if (strcmp(s,"ENCH") == 0) {
	r = parsebuffer_ench(b);
      } else if (strcmp(s,"FACT") == 0) {
	r = parsebuffer_fact(b);
      } else if (strcmp(s,"FMAP") == 0) {
	r = parsebuffer_fmap(b);
      } else if (strcmp(s,"GAME") == 0) {
	r = parsebuffer_game(b);
      } else if (strcmp(s,"GLOB") == 0) {
	r = parsebuffer_glob(b);
      } else if (strcmp(s,"GMST") == 0) {
	r = parsebuffer_gmst(b);
      } else if (strcmp(s,"INFO") == 0) {
	r = parsebuffer_info(b);
      } else if (strcmp(s,"INGR") == 0) {
	r = parsebuffer_ingr(b);
      } else if (strcmp(s,"JOUR") == 0) {
	r = parsebuffer_jour(b);
      } else if (strcmp(s,"KLST") == 0) {
	r = parsebuffer_klst(b);
      } else if (strcmp(s,"LAND") == 0) {
	r = parsebuffer_land(b);
      } else if (strcmp(s,"LEVC") == 0) {
	r = parsebuffer_levc(b);
      } else if (strcmp(s,"LEVI") == 0) {
	r = parsebuffer_levi(b);
      } else if (strcmp(s,"LIGH") == 0) {
	r = parsebuffer_ligh(b);
      } else if (strcmp(s,"LOCK") == 0) {
	r = parsebuffer_lock(b);
      } else if (strcmp(s,"LTEX") == 0) {
	r = parsebuffer_ltex(b);
      } else if (strcmp(s,"MGEF") == 0) {
	r = parsebuffer_mgef(b);
      } else if (strcmp(s,"MISC") == 0) {
	r = parsebuffer_misc(b);
      } else if (strcmp(s,"NPC_") == 0) {
	r = parsebuffer_npc(b);
      } else if (strcmp(s,"NPCC") == 0) {
	r = parsebuffer_npcc(b);
      } else if (strcmp(s,"PCDT") == 0) {
	r = parsebuffer_pcdt(b);
      } else if (strcmp(s,"PGRD") == 0) {
	r = parsebuffer_pgrd(b);
      } else if (strcmp(s,"PROB") == 0) {
	r = parsebuffer_prob(b);
      } else if (strcmp(s,"QUES") == 0) {
	r = parsebuffer_ques(b);
      } else if (strcmp(s,"RACE") == 0) {
	r = parsebuffer_race(b);
      } else if (strcmp(s,"REFR") == 0) {
	r = parsebuffer_refr(b);
      } else if (strcmp(s,"REGN") == 0) {
	r = parsebuffer_regn(b);
      } else if (strcmp(s,"REPA") == 0) {
	r = parsebuffer_repa(b);
      } else if (strcmp(s,"SCPT") == 0) {
	r = parsebuffer_scpt(b);
      } else if (strcmp(s,"SKIL") == 0) {
	r = parsebuffer_skil(b);
      } else if (strcmp(s,"SNDG") == 0) {
	r = parsebuffer_sndg(b);
      } else if (strcmp(s,"SOUN") == 0) {
	r = parsebuffer_soun(b);
      } else if (strcmp(s,"SPEL") == 0) {
	r = parsebuffer_spel(b);
      } else if (strcmp(s,"SPLM") == 0) {
	r = parsebuffer_splm(b);
      } else if (strcmp(s,"SSCR") == 0) {
	r = parsebuffer_sscr(b);
      } else if (strcmp(s,"STAT") == 0) {
	r = parsebuffer_stat(b);
      } else if (strcmp(s,"STLN") == 0) {
	r = parsebuffer_stln(b);
      } else if (strcmp(s,"TES3") == 0) {
	r = parsebuffer_tes3(b);
      } else if (strcmp(s,"WEAP") == 0) {
	r = parsebuffer_weap(b);
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
  buffer_skip_bytes(b,16);
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

  if (ac < 1) {
    fprintf(stderr,"Usage: espparser <file>\n");
    exit(-1);
  }

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
