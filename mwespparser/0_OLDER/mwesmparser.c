
// Copyright 2008 Juhana Sadeharju
// GNU GPL

// mwesmparser: now only extracts the land data

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

#define C_RECORD_HEADER_SIZE 16 // Ob = 20, MW = 16


// Oblivion mod file structures.
typedef struct {
  int size;
  unsigned char *data;
} ty_oblivion_chunk;


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


float mw_land_vhgt[65][65]; // We precompute/unpack the height values.
unsigned char mw_land_vclr_r[65][65];
unsigned char mw_land_vclr_g[65][65];
unsigned char mw_land_vclr_b[65][65];
char mw_land_vnml_x[65][65];
char mw_land_vnml_y[65][65];
char mw_land_vnml_z[65][65];
short mw_land_vtex[16][16];

int parsebuffer_land_tes3(void *b)
{
  int i,j,k,l,m,n;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int has_land_intv;
  int land_intv_xloc;
  int land_intv_yloc;
  int has_land_vhgt;
  int has_land_vnml;
  int has_land_vclr;
  int has_land_vtex;
  int data;
  float baseheight;
  int columnheight,rowheight;
  char fn[20];
  FILE *fp;

  has_land_intv = 0;
  has_land_vhgt = 0;
  has_land_vnml = 0;
  has_land_vclr = 0;
  has_land_vtex = 0;
 
  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"DATA") == 0) {
      n = buffer_read_int(b);
      printf("LAND/DATA %i\n",n);
#if 1
      n = buffer_read_int(b);
      printf("%i\n",n);
      data = n;
      // flags = buffer_read_uint(b);
      // printflags(flags);
#else
      buffer_skip_bytes(b,n);
#endif
    } else if (strcmp(s,"VNML") == 0) {
      n = buffer_read_int(b);
      printf("LAND/VNML %i\n",n);
      has_land_vnml = 1;
#if 1
      for (j = 0; j < 65; j++) {
	for (i = 0; i < 65; i++) {
	  mw_land_vnml_x[j][i] = buffer_read_byte(b);
	  mw_land_vnml_y[j][i] = buffer_read_byte(b);
	  mw_land_vnml_z[j][i] = buffer_read_byte(b);
	}
      }
#else
      buffer_skip_bytes(b,n);
#endif
    } else if (strcmp(s,"VHGT") == 0) {
      n = buffer_read_int(b);
      printf("LAND/VHGT %i\n",n);
      has_land_vhgt = 1;
#if 1
      f = buffer_read_float(b);
      printf("%f\n",f);
      baseheight = f;

      // Checked from MGE of Timeslip.
      columnheight = 0;
      for (j = 0; j < 65; j++) {
	columnheight += buffer_read_byte(b);
	mw_land_vhgt[j][0] = baseheight + (float)columnheight;
	rowheight = columnheight;
	for (i = 1; i < 65; i++) {
	  rowheight += buffer_read_byte(b);
	  mw_land_vhgt[j][i] = baseheight + (float)rowheight;
	  // printf("%i\n",n);
	}
      }
      buffer_skip_bytes(b,n-4-65*65);
#if 0
      // Oblivion related.
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
#endif

#else
      f = buffer_read_float(b);
      printf("%f\n",f);
      baseheight = f;
      buffer_skip_bytes(b,n-4);
#endif
    } else if (strcmp(s,"VCLR") == 0) {
      n = buffer_read_int(b);
      printf("LAND/VCLR %i\n",n);
      has_land_vclr = 1;
#if 1
      for (j = 0; j < 65; j++) {
	for (i = 0; i < 65; i++) {
	  mw_land_vclr_r[j][i] = buffer_read_ubyte(b);
	  mw_land_vclr_g[j][i] = buffer_read_ubyte(b);
	  mw_land_vclr_b[j][i] = buffer_read_ubyte(b);
	}
      }
      buffer_skip_bytes(b,n-65*65*3);
#else
      buffer_skip_bytes(b,n);
#endif
    } else if (strcmp(s,"BTXT") == 0) {
      n = buffer_read_int(b);
      printf("LAND/BTXT %i\n",n);
#if 0
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_short(b);
      printf("%i\n",n);
#else
      buffer_skip_bytes(b,n);
#endif
    } else if (strcmp(s,"ATXT") == 0) {
      n = buffer_read_int(b);
      printf("LAND/ATXT %i\n",n);
#if 0
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_short(b);
      printf("%i\n",n);
#else
      buffer_skip_bytes(b,n);
#endif
    } else if (strcmp(s,"VTXT") == 0) {
      n = buffer_read_int(b);
      printf("LAND/VTXT %i\n",n);
#if 0
#else
      buffer_skip_bytes(b,n);
#endif
    } else if (strcmp(s,"INTV") == 0) {
      n = buffer_read_int(b);
      printf("LAND/INTV %i\n",n);
      has_land_intv = 1;
#if 1
      n = buffer_read_int(b);
      printf("%i\n",n);
      land_intv_xloc = n;
      n = buffer_read_int(b);
      printf("%i\n",n);
      land_intv_yloc = n;
#else
      buffer_skip_bytes(b,n);
#endif
    } else if (strcmp(s,"WNAM") == 0) {
      n = buffer_read_int(b);
      printf("LAND/WNAM %i\n",n);
#if 0
#else
      buffer_skip_bytes(b,n);
#endif
    } else if (strcmp(s,"VTEX") == 0) {
      n = buffer_read_int(b);
      printf("LAND/VTEX %i\n",n);
      has_land_vtex = 1;
#if 1
      for (l = 0; l < 4; l++) {
	for (k = 0; k < 4; k++) {
	  for (j = 0; j < 4; j++) {
	    for (i = 0; i < 4; i++) {
	      mw_land_vtex[4*l + j][4*k + i] = buffer_read_short(b);
	    }
	  }
	}
      }
#else
      buffer_skip_bytes(b,n);
#endif
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of LAND\n");

#if 1
  if (has_land_intv != 1) {
    printf("LAND has no INTV\n");
    exit(-1);
  } else {
    sprintf(fn,"land_%i_%i.info",land_intv_xloc,land_intv_yloc);
    fp = fopen(fn,"w");
    fprintf(fp,"xloc = %i\n",land_intv_xloc);
    fprintf(fp,"yloc = %i\n",land_intv_yloc);
    fprintf(fp,"data = %i\n",data);
    if (has_land_vhgt == 0) {
      fprintf(fp,"has_land_vhgt = %i\n",has_land_vhgt);
      fprintf(fp,"baseheight = 0.0\n");
    } else {
      fprintf(fp,"has_land_vhgt = %i\n",has_land_vhgt);
      fprintf(fp,"baseheight = %f\n",baseheight);
    }
    fprintf(fp,"has_land_vclr = %i\n",has_land_vclr);
    fprintf(fp,"has_land_vnml = %i\n",has_land_vnml);
    fprintf(fp,"has_land_vtex = %i\n",has_land_vtex);
    fclose(fp);

  }

  if ((has_land_intv != 1) || (has_land_vhgt != 1)) {
    printf("LAND has no INTV or has no VHGT\n");
  } else {
    sprintf(fn,"land_%i_%i.vhgt",land_intv_xloc,land_intv_yloc);
    fp = fopen(fn,"w");
    if (fwrite(mw_land_vhgt,4,65*65,fp) != 65*65) {
      fprintf(stderr,"error in writing VHGT\n");
    }
    fclose(fp);
  }

  if ((has_land_intv != 1) || (has_land_vnml != 1)) {
    printf("LAND has no INTV or has no VNML\n");
  } else {
    sprintf(fn,"land_%i_%i.vnml",land_intv_xloc,land_intv_yloc);
    fp = fopen(fn,"w");
    if (fwrite(mw_land_vnml_x,1,65*65,fp) != 65*65) {
      fprintf(stderr,"error in writing VNML\n");
    }
    if (fwrite(mw_land_vnml_y,1,65*65,fp) != 65*65) {
      fprintf(stderr,"error in writing VNML\n");
    }
    if (fwrite(mw_land_vnml_z,1,65*65,fp) != 65*65) {
      fprintf(stderr,"error in writing VNML\n");
    }
    fclose(fp);
  }

  if ((has_land_intv != 1) || (has_land_vclr != 1)) {
    printf("LAND has no INTV or has no VCLR\n");
  } else {
    sprintf(fn,"land_%i_%i.vclr",land_intv_xloc,land_intv_yloc);
    fp = fopen(fn,"w");
    if (fwrite(mw_land_vclr_r,1,65*65,fp) != 65*65) {
      fprintf(stderr,"error in writing VCLR\n");
    }
    if (fwrite(mw_land_vclr_g,1,65*65,fp) != 65*65) {
      fprintf(stderr,"error in writing VCLR\n");
    }
    if (fwrite(mw_land_vclr_b,1,65*65,fp) != 65*65) {
      fprintf(stderr,"error in writing VCLR\n");
    }
    fclose(fp);
  }

  if ((has_land_intv != 1) || (has_land_vtex != 1)) {
    printf("LAND has no INTV or has no VTEX\n");
  } else {
    sprintf(fn,"land_%i_%i.vtex",land_intv_xloc,land_intv_yloc);
    fp = fopen(fn,"w");
    if (fwrite(mw_land_vtex,2,16*16,fp) != 16*16) {
      fprintf(stderr,"error in writing VTEX\n");
    }
    fclose(fp);
  }

#endif

  return -1;
}


char mw_ltex_name[200];
char mw_ltex_data[200];

int parsebuffer_ltex_tes3(void *b)
{
  int i,j,k,l,m,n;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int has_ltex_name;
  int has_ltex_intv;
  int ltex_intv_texid;
  int has_ltex_data;
  int data;
  float baseheight;
  int columnheight,rowheight;
  char fn[20];
  FILE *fp;

  has_ltex_name = 0;
  has_ltex_intv = 0;
  has_ltex_data = 0;
 
  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"NAME") == 0) {
      n = buffer_read_int(b);
      printf("LTEX/NAME %i\n",n);
      has_ltex_name = 1;
#if 1
      s2 = buffer_read_nstring(b,n);
      s2[n-1] = '\0'; // In the case the '\0' is not there. May break the name.
      strcpy(mw_ltex_name,s2);
      printf("%s\n",s2);
      free(s2);
#else
      buffer_skip_bytes(b,n);
#endif
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_int(b);
      printf("LTEX/DATA %i\n",n);
      has_ltex_data = 1;
#if 1
      s2 = buffer_read_nstring(b,n);
      s2[n-1] = '\0'; // In the case the '\0' is not there. May break the name.
      strcpy(mw_ltex_data,s2);
      printf("%s\n",s2);
      free(s2);
#else
      buffer_skip_bytes(b,n);
#endif
    } else if (strcmp(s,"INTV") == 0) {
      n = buffer_read_int(b);
      printf("LTEX/INTV %i\n",n);
      has_ltex_intv = 1;
#if 1
      n = buffer_read_int(b);
      printf("%i\n",n);
      ltex_intv_texid = n;
#else
      buffer_skip_bytes(b,n);
#endif
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of LTEX\n");

#if 1
  if ((has_ltex_intv == 0) || (has_ltex_name == 0) || (has_ltex_data == 0)) {
    printf("LTEX has no INTV or no NAME or no DATA\n");
    exit(-1);
  } else {
    sprintf(fn,"ltex_%i",ltex_intv_texid);
    fp = fopen(fn,"w");
    fprintf(fp,"ltex_intv_texid = %i\n",ltex_intv_texid);
    fprintf(fp,"ltex_name = \"%s\"\n",mw_ltex_name);
    fprintf(fp,"ltex_data = \"%s\"\n",mw_ltex_data);
    fclose(fp);
  }

#endif

  return -1;
}



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
      // buffer_skip_bytes(b,C_RECORD_HEADER_SIZE);
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
	printf("%i %i\n",
	       (int)(((unsigned short *)s2)[0]),
	       (int)(((unsigned short *)s2)[1]));
	printf("Grouptype = 4 Exterior Cell Block\n");
	break;
      case 5:
	// grid y,x -- reverse order
	printf("%i %i\n",
	       (int)(((unsigned short *)s2)[0]),
	       (int)(((unsigned short *)s2)[1]));
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
      b2 = buffer_new(&(buffer[buffer_getloc(b)]),n-C_RECORD_HEADER_SIZE);
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
#if 0
  // MW has no formids.
  m = buffer_read_int(b);
  printf("formid = %i\n",m);
#endif
  flags2 = buffer_read_uint(b);
  printf("flags 2 = ");
  printflags(flags2);

  buffer_setloc(b,mloc);
  buffer_skip_bytes(b,C_RECORD_HEADER_SIZE);

  // MW may not have this flag.
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

  
      if (strcmp(s,"LAND") == 0) {
	r = parsebuffer_land_tes3(b);
      } else if (strcmp(s,"LTEX") == 0) {
	r = parsebuffer_ltex_tes3(b);
      } else {
	printf("Record %s unimplemented\n",s);
	r = 1;
      }
      if (r == 0) {
	printf("parsebuffer_ error\n");
	exit(-1);
      }

#if 0
      // Oblivion.
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
#endif

#if 1
      // Moved from parsebuffer_ routines

  buffer_free(b);
  b = btmp;
  buffer_setloc(b,mloc);
  buffer_skip_bytes(b,C_RECORD_HEADER_SIZE);
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
