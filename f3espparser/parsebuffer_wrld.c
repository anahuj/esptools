
int parsebuffer_wrld(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int numxxxx;
  float xmin,xmax,ymin,ymax;
  int x0,y0,xsize,ysize;
  int *ofst;
  int hasmins;
  int hasmaxs;
  int x,y;
  int size;
  int num;

  ofst = NULL;
  hasmins = 0;
  hasmaxs = 0;

  sprintf(global_worldspace,"");
  numxxxx = -1;
  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("WRLD/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      sprintf(global_worldspace,s2);
      free(s2);
    } else if (strcmp(s,"NAM2") == 0) {
      n = buffer_read_short(b);
      printf("WRLD/NAM2 %i\n",n);
      n = buffer_read_int(b);
      printf("Water FormID %i\n",n);
    } else if (strcmp(s,"WNAM") == 0) {
      n = buffer_read_short(b);
      printf("WRLD/WNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Parent Worldspace %i\n",n);
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_short(b);
      printf("WRLD/SNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Music %i %% 1 Public 2 Dungeon\n",n);
    } else if (strcmp(s,"CNAM") == 0) {
      n = buffer_read_short(b);
      printf("WRLD/CNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Climate FormID %i\n",n);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("WRLD/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("WRLD/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Map Image \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MNAM") == 0) {
      n = buffer_read_short(b);
      printf("WRLD/MNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Usable Dimensions X %i\n",n);
      n = buffer_read_int(b);
      printf("Usable Dimensions Y %i\n",n);
      n = buffer_read_short(b);
      printf("Cell Coords/NW Cell X %i\n",n);
      n = buffer_read_short(b);
      printf("Cell Coords/NW Cell Y %i\n",n);
      n = buffer_read_short(b);
      printf("Cell Coords/SE Cell X %i\n",n);
      n = buffer_read_short(b);
      printf("Cell Coords/SE Cell Y %i\n",n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("WRLD/DATA %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Small World\n");
      printf("       ^Can't Fast Travel From Here\n");
      printf("   ^No LOD Water\n");
      printf("  ^No LOD Noise\n");
      printf(" ^~Allow NPC Fall Damage\n");
    } else if (strcmp(s,"NAM0") == 0) {
      n = buffer_read_short(b);
      printf("WRLD/NAM0 %i\n",n);
      f = buffer_read_float(b);
      printf("Min X %f\n",f);
      xmin = f;
      f = buffer_read_float(b);
      printf("Min Y %f\n",f);
      ymin = f;
      hasmins = 1;
    } else if (strcmp(s,"NAM9") == 0) {
      n = buffer_read_short(b);
      printf("WRLD/NAM9 %i\n",n);
      f = buffer_read_float(b);
      printf("Max X %f\n",f);
      xmax = f;
      f = buffer_read_float(b);
      printf("Max Y %f\n",f);
      ymax = f;
      hasmaxs = 1;
    } else if (strcmp(s,"XXXX") == 0) {
      n = buffer_read_short(b);
      printf("WRLD/XXXX %i\n",n);
      n = buffer_read_int(b);
      numxxxx = n;
      printf("%i\n",n);
    } else if (strcmp(s,"OFST") == 0) {
      n = buffer_read_short(b);
      printf("WRLD/OFST %i\n",n);
      if (numxxxx > 0) {
	n = numxxxx;
	numxxxx = -1;
      }
      ofst = (int *)malloc(n*sizeof(char));
      buffer_read_bytes_in(b,n,(char *)ofst);
    } else if (strcmp(s,"NAM3") == 0) { // F
      n = buffer_read_short(b);
      printf("WRLD/NAM3 %i\n",n);
      n = buffer_read_int(b);
      printf("LOD Water Type FormID %i\n",n);
    } else if (strcmp(s,"NAM4") == 0) { // F
      n = buffer_read_short(b);
      printf("WRLD/NAM4 %i\n",n);
      f = buffer_read_float(b);
      printf("LOD Water Height %f\n",f);
    } else if (strcmp(s,"DNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WRLD/DNAM %i\n",n);
      f = buffer_read_float(b);
      printf("Default Land Height %f\n",f);
      f = buffer_read_float(b);
      printf("Default Water Height %f\n",f);
    } else if (strcmp(s,"ONAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WRLD/ONAM %i\n",n);
      f = buffer_read_float(b);
      printf("World Map Scale %f\n",f);
      f = buffer_read_float(b);
      printf("Cell X Offset %f\n",f);
      f = buffer_read_float(b);
      printf("Cell Y Offset %f\n",f);
    } else if (strcmp(s,"INAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WRLD/INAM %i\n",n);
      n = buffer_read_int(b);
      printf("Imagespace FormID %i\n",n);
    } else if (strcmp(s,"NNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WRLD/NNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Canopy Shadow \"%s\"\n",s2);
    } else if (strcmp(s,"XNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WRLD/XNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Water Noise Texture \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"XEZN") == 0) { // F
      n = buffer_read_short(b);
      printf("WRLD/XEZN %i\n",n);
      n = buffer_read_int(b);
      printf("Encounter Zone FormID %i\n",n);
    } else if (strcmp(s,"PNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WRLD/PNAM %i\n",n);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Use Land Data\n");
      printf("       ^Use LOD Data\n");
      printf("      ^Use Map Data\n");
      printf("     ^Use Water Data\n");
      printf("   ^Use Climate Data\n");
      printf("  ^Use Image Space Data\n");
      n = buffer_read_byte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"ZNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WRLD/ZNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Music FormID %i\n",n);
    } else if (strcmp(s,"IMPF") == 0) { // F
      n = buffer_read_short(b);
      printf("WRLD/IMPF %i\n",n);
      size = n;
      s2 = buffer_read_nstring(b,30);
      printf("ConcSolid \"%s\"\n",s2);
      s2 = buffer_read_nstring(b,30);
      printf("ConcBroken \"%s\"\n",s2);
      s2 = buffer_read_nstring(b,30);
      printf("MetalSolid \"%s\"\n",s2);
      s2 = buffer_read_nstring(b,30);
      printf("MetalHollow \"%s\"\n",s2);
      s2 = buffer_read_nstring(b,30);
      printf("MetalSheet \"%s\"\n",s2);
      s2 = buffer_read_nstring(b,30);
      printf("Wood \"%s\"\n",s2);
      s2 = buffer_read_nstring(b,30);
      printf("Sand \"%s\"\n",s2);
      s2 = buffer_read_nstring(b,30);
      printf("Dirt \"%s\"\n",s2);
      s2 = buffer_read_nstring(b,30);
      printf("Grass \"%s\"\n",s2);
      s2 = buffer_read_nstring(b,30);
      printf("Water \"%s\"\n",s2);
    } else if (strcmp(s,"IMPS") == 0) { // F
      n = buffer_read_short(b);
      printf("WRLD/IMPS %i\n",n);
      n = buffer_read_int(b);
      printf("Type %i %% 0 Stone 1 Dirt 2 Grass 3 Glass 4 Metal 5 Wood 6 Organic 7 Cloth 8 Water 9 Hollow Metal 10 Organic Bug 11 Organic Glow\n",n);
      n = buffer_read_int(b);
      printf("Orig Data FormID %i\n",n);
      n = buffer_read_int(b);
      printf("New Data FormID %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  // Print OFST info.
  if ((ofst != NULL) && (hasmins == 1) && (hasmaxs == 1)) {
    x0 = 2.0*(-xmin)/8192.0;
    y0 = 2.0*(-ymin)/8192.0;
    xsize = 2.0*(xmax-xmin)/8192.0 + 1.0;
    ysize = 2.0*(ymax-ymin)/8192.0 + 1.0;
    for (y = 0; y < ysize; y++) {
      for (x = 0; x < xsize; x++) {
	printf("cell (%i, %i) offset = %i\n",x-x0,y-y0,ofst[y*xsize + x]);
      }
    }
  }

  if (ofst != NULL) {
    free(ofst);
  }

  printf("End of WRLD\n");

  return -1;
}
