

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
      n = buffer_read_short(b);
      printf("LAND/DATA %i\n",n);
      flags = buffer_read_uint(b);
      printflags(flags);
    } else if (strcmp(s,"VNML") == 0) {
      n = buffer_read_short(b);
      printf("LAND/VNML %i\n",n);
      for (j = 0; j < 33; j++) {
	for (i = 0; i < 33; i++) {
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
	  land->vnml[j*33*3 + i*3 + 0] = x;
	  land->vnml[j*33*3 + i*3 + 1] = y;
	  land->vnml[j*33*3 + i*3 + 2] = z;
	}
      }
      land->hasvnml = 1;
    } else if (strcmp(s,"VHGT") == 0) {
      n = buffer_read_short(b);
      printf("LAND/VHGT %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
      land->vhgtbase = f;
      for (j = 0; j < 33; j++) {
	for (i = 0; i < 33; i++) {
	  n = buffer_read_byte(b);
	  printf("landheight at (%i,%i): %i\n",i,j,n);
	  land->vhgt[j*33 + i] = n;
	}
      }
      land->hasvhgt = 1;
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"VCLR") == 0) {
      n = buffer_read_short(b);
      printf("LAND/VCLR %i\n",n);
      for (j = 0; j < 33; j++) {
	for (i = 0; i < 33; i++) {
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
    } else if (strcmp(s,"BTXT") == 0) {
      n = buffer_read_short(b);
      printf("LAND/BTXT %i\n",n);
      n = buffer_read_int(b);
      printf("Land Texture FormID %i\n",n);
      sourcetexture = n;
      n = buffer_read_byte(b);
      printf("Quadrant %i\n",n);
      targetquadrant = n;
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_short(b);
      printf("%i\n",n);

      // B texture can be filled here.

    } else if (strcmp(s,"ATXT") == 0) {
      n = buffer_read_short(b);
      printf("LAND/ATXT %i\n",n);
      n = buffer_read_int(b);
      printf("Land Texture FormID %i\n",n);
      sourcetexture = n;
      n = buffer_read_byte(b);
      printf("Quadrant %i\n",n);
      targetquadrant = n;
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_short(b);
      printf("Layer %i\n",n);
      targetlayer = n;

      // A texture will be filled in VTXT subrecord.

    } else if (strcmp(s,"VTXT") == 0) {
      n = buffer_read_short(b);
      printf("LAND/VTXT %i\n",n);
      m = n/8;
      for (i = 0; i < m; i++) {
	n = buffer_read_short(b);
	// printf("%i\n",n);
	n2 = buffer_read_byte(b);
	// printf("%i\n",n);
	n3 = buffer_read_byte(b);
	// printf("%i\n",n);
	f = buffer_read_float(b);
	// printf("%f\n",f);
	printf("%3i %4i %4i %8f\n",n,n2,n3,f);
      }
    } else if (strcmp(s,"VTEX") == 0) {
      n = buffer_read_short(b);
      printf("LAND/VTEX %i\n",n);
      buffer_skip_bytes(b,n);
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
