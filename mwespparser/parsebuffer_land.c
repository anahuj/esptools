

// At LAND record exit, these structures have been filled.

#if 1

// We combine four quadrants to one texture layer.
// B-texture is available at the same resolution as are
// A-textures even B-texture fills the whole quadrant. 

// B-textures are disjoint. Likewise ATXT+VTXT* groups are disjoint.
// int bformids[4];  one per quadrant
// int aformids[4][9]; 9 per quadrant
// char textures[9][33][33]; // pointers to formids
// float opacity[9][33][33];

// We use texture formid indexes because otherwise it will
// take too long to check all textures needed.


typedef struct {
  int textureformidindex;
  float opacity;
} ty_land_texturelayer_data;

#if 0
typedef struct {
  int formids[4];
  int textureformidindex[33][33];
  float opacity[33][33];
} ty_land_texturelayer;
#else
typedef struct {
  int formids[4];
  ty_land_texturelayer_data texdata[33][33];
} ty_land_texturelayer;
#endif

typedef struct {
  int hasvhgt;
  int hasvnml;
  int hasvclr;
  float vhgtbase;
  char vhgt[33*33]; // 1089, three filler bytes at end excluded.
  char vnml[3*33*33]; // 3267
  char vclr[3*33*33]; // 3267
  ty_land_texturelayer basetexture;
  ty_land_texturelayer texturelayers[10];
} ty_land;
#endif

int parsebuffer_land(void *b)
{
  int n,n2,n3,n4;
  int i;
  int j;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int x,y,z;
  int sourcetexture;
  int targetquadrant;
  int targetlayer;
  ty_land *land;

  land = (ty_land *)malloc(sizeof(ty_land));
  land->hasvhgt = 0;
  land->hasvnml = 0;
  land->hasvclr = 0;


  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"DATA") == 0) {
      n = buffer_read_int(b);
      printf("LAND/DATA %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"VNML") == 0) {
      n = buffer_read_int(b);
      printf("LAND/VNML %i\n",n);
      for (j = 0; j < 65; j++) {
	for (i = 0; i < 65; i++) {
	  n = buffer_read_byte(b);
	  // printf("%i\n",n);
	  x = n;
	  n = buffer_read_byte(b);
	  // printf("%i\n",n);
	  y = n;
	  n = buffer_read_byte(b);
	  // printf("%i\n",n);
	  z = n;
	  printf("landnormal at (%i,%i): %i %i %i\n",i,j,x,y,z);
	  land->vnml[j*65*3 + i*3 + 0] = x;
	  land->vnml[j*65*3 + i*3 + 1] = y;
	  land->vnml[j*65*3 + i*3 + 2] = z;
	}
      }
      land->hasvnml = 1;
    } else if (strcmp(s,"VHGT") == 0) {
      n = buffer_read_int(b);
      printf("LAND/VHGT %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
      land->vhgtbase = f;
      for (j = 0; j < 65; j++) {
	for (i = 0; i < 65; i++) {
	  n = buffer_read_byte(b);
	  printf("landheight at (%i,%i): %i\n",i,j,n);
	  land->vhgt[j*65 + i] = n;
	}
      }
      land->hasvhgt = 1;
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"WNAM") == 0) {
      n = buffer_read_int(b);
      printf("LAND/WNAM %i\n",n);
      buffer_skip_bytes(b,n);
      printf("XXXX skipping LAND/WNAM\n");
    } else if (strcmp(s,"VCLR") == 0) {
      n = buffer_read_int(b);
      printf("LAND/VCLR %i\n",n);
      for (j = 0; j < 65; j++) {
	for (i = 0; i < 65; i++) {
	  n = buffer_read_ubyte(b);
	  x = n;
	  // printf("%i\n",n);
	  n = buffer_read_ubyte(b);
	  y = n;
	  // printf("%i\n",n);
	  n = buffer_read_ubyte(b);
	  z = n;
	  // printf("%i\n",n);
	  printf("landcolor at (%i,%i): %i %i %i\n",i,j,x,y,z);
	  land->vclr[j*33*3 + i*3 + 0] = x;
	  land->vclr[j*33*3 + i*3 + 1] = y;
	  land->vclr[j*33*3 + i*3 + 2] = z;
	}
      }
      land->hasvclr = 1;
    } else if (strcmp(s,"VTEX") == 0) {
      n = buffer_read_int(b);
      printf("LAND/VTEX %i\n",n);
      buffer_skip_bytes(b,n);
      printf("XXXX skipping LAND/VTEX\n");
    } else if (strcmp(s,"INTV") == 0) {
      n = buffer_read_int(b);
      printf("LAND/INTV %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of LAND\n");

  free(land);

  return -1;
}
