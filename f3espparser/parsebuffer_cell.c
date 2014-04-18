
int parsebuffer_cell(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int size;
  int num;

  sprintf(global_cell,"");
  global_cell_x = 0x0fffffff;
  global_cell_y = 0x0fffffff;
  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("CELL/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      sprintf(global_cell,s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("CELL/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("CELL/DATA %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Interior Can't Travel From Here\n");
      printf("       ^Has Water\n");
      printf("      ^Exterior Can't Travel From Here\n");
      printf("     ^No LOD Water\n");
      printf("  ^Public Area\n");
      printf(" ^Hand Changed\n");
      printf("^Behave Like Exterior\n");
    } else if (strcmp(s,"XCLL") == 0) { // F
      n = buffer_read_short(b);
      printf("CELL/XCLL %i\n",n);
      size = n;
      n = buffer_read_ubyte(b);
      printf("Ambient Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Ambient Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Ambient Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("Directional Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Directional Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Directional Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("Fog Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Fog Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Fog Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      f = buffer_read_float(b);
      printf("Fog Near %f\n",f);
      f = buffer_read_float(b);
      printf("Fog Far %f\n",f);
      n = buffer_read_int(b);
      printf("Rotation XY %i\n",n);
      n = buffer_read_int(b);
      printf("Rotation Z %i\n",n);
      f = buffer_read_float(b);
      printf("Fade %f\n",f);
      f = buffer_read_float(b);
      printf("Fog Clip Dist %f\n",f);
      if (size == 40) {              // F
	f = buffer_read_float(b);
	printf("Fog Pow %f\n",f);
      }
    } else if (strcmp(s,"XOWN") == 0) {
      n = buffer_read_short(b);
      printf("CELL/XOWN %i\n",n);
      n = buffer_read_int(b);
      printf("Owner FormID %i\n",n);
#if 0
      // Not in Fallout3.esm.
    } else if (strcmp(s,"XGLB") == 0) {
      n = buffer_read_short(b);
      printf("CELL/XGLB %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
#endif
    } else if (strcmp(s,"XCCM") == 0) {
      n = buffer_read_short(b);
      printf("CELL/XCCM %i\n",n);
      n = buffer_read_int(b);
      printf("Climate FormID %i\n",n);
    } else if (strcmp(s,"XCMT") == 0) {
      n = buffer_read_short(b);
      printf("CELL/XCMT %i\n",n);
      n = buffer_read_byte(b);
      printf("Music Type %i %% 1 Public 2 Dungeon\n",n);
    } else if (strcmp(s,"XCLC") == 0) { // F
      n = buffer_read_short(b);
      printf("CELL/XCLC %i\n",n);
      size = n;
      n = buffer_read_int(b);
      printf("Location X %i\n",n);
      global_cell_x = n;
      n = buffer_read_int(b);
      printf("Location Y %i\n",n);
      global_cell_y = n;
      if (size == 12) { // F
	n = buffer_read_byte(b);
	printflags8(n);
	//      0000,0000
	printf("        ^Force Hide Land Quad 1\n");
	printf("       ^Force Hide Land Quad 2\n");
	printf("      ^Force Hide Land Quad 3\n");
	printf("     ^Force Hide Land Quad 4\n");
	n = buffer_read_byte(b);
	printf("%i (unused)\n",n);
	n = buffer_read_byte(b);
	printf("%i (unused)\n",n);
	n = buffer_read_byte(b);
	printf("%i (unused)\n",n);
      }
    } else if (strcmp(s,"XCLR") == 0) {
      n = buffer_read_short(b);
      printf("CELL/XCLR %i\n",n);
      m = n/4;
      for (i = 0; i < m; i++) {
	n = buffer_read_int(b);
	printf("Region FormID %i\n",n);
      }
    } else if (strcmp(s,"XCLW") == 0) {
      n = buffer_read_short(b);
      printf("CELL/XCLW %i\n",n);
      f = buffer_read_float(b);
      printf("Water Height %f\n",f);
    } else if (strcmp(s,"XCWT") == 0) {
      n = buffer_read_short(b);
      printf("CELL/XCWT %i\n",n);
      n = buffer_read_int(b);
      printf("Water FormID %i\n",n);
    } else if (strcmp(s,"XRNK") == 0) {
      n = buffer_read_short(b);
      printf("CELL/XRNK %i\n",n);
      n = buffer_read_int(b);
      printf("Required Rank %i %% 0 DUMMY\n",n);
    } else if (strcmp(s,"LTMP") == 0) { // F
      n = buffer_read_short(b);
      printf("CELL/LTMP %i\n",n);
      n = buffer_read_int(b);
      printf("Lighting Template FormID %i\n",n);
    } else if (strcmp(s,"LNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("CELL/LNAM %i\n",n);
      n = buffer_read_short(b);
      printf("Lighting Template Inherit:\n");
      printflags16(n);
      //      0000,0000,0000,0000
      printf("                  ^Ambient Color\n");
      printf("                 ^Directional Color\n");
      printf("                ^Fog Color\n");
      printf("               ^Fog Near\n");
      printf("             ^Fog Far\n");
      printf("            ^Directional Rot\n");
      printf("           ^Directional Fade\n");
      printf("          ^Clip Distance\n");
      printf("        ^Fog Power\n");
      n = buffer_read_short(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"XNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("CELL/XNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Water Noise Texture \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"XCIM") == 0) { // F
      n = buffer_read_short(b);
      printf("CELL/XCIM %i\n",n);
      n = buffer_read_int(b);
      printf("ImageSpace FormID %i\n",n);
    } else if (strcmp(s,"XEZN") == 0) { // F
      n = buffer_read_short(b);
      printf("CELL/XEZN %i\n",n);
      n = buffer_read_int(b);
      printf("Encounter Zone FormID %i\n",n);
    } else if (strcmp(s,"XCMO") == 0) { // F
      n = buffer_read_short(b);
      printf("CELL/XCMO %i\n",n);
      n = buffer_read_int(b);
      printf("Music type FormID %i\n",n);
    } else if (strcmp(s,"XCAS") == 0) { // F
      n = buffer_read_short(b);
      printf("CELL/XCAS %i\n",n);
      n = buffer_read_int(b);
      printf("Default Acoustic FormID %i\n",n);
    } else if (strcmp(s,"XCET") == 0) { // F
      n = buffer_read_short(b);
      printf("CELL/XCET %i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"IMPF") == 0) { // F
      n = buffer_read_short(b);
      printf("CELL/IMPF %i\n",n);
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
      printf("CELL/IMPS %i\n",n);
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

  printf("End of CELL\n");

  return -1;
}
