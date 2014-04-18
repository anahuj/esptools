
int parsebuffer_cell(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("CELL/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
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
      printf("        ^Can't Travel From Here\n");
      printf("       ^Has Water\n");
      printf("     ^Oblivion Interior\n");
      printf("  ^Public Area\n");
      printf(" ^Hand Changed\n");
      printf("^Behave Like Exterior\n");
    } else if (strcmp(s,"XCLL") == 0) {
      n = buffer_read_short(b);
      printf("CELL/XCLL %i\n",n);
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
    } else if (strcmp(s,"XOWN") == 0) {
      n = buffer_read_short(b);
      printf("CELL/XOWN %i\n",n);
      n = buffer_read_int(b);
      printf("Owner FormID %i\n",n);
    } else if (strcmp(s,"XGLB") == 0) {
      n = buffer_read_short(b);
      printf("CELL/XGLB %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
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
    } else if (strcmp(s,"XCLC") == 0) {
      n = buffer_read_short(b);
      printf("CELL/XCLC %i\n",n);
      n = buffer_read_int(b);
      // printf("Location X %i\n",n);
      m = buffer_read_int(b);
      // printf("Location Y %i\n",n);
      printf("Location x y %i %i\n",n,m);
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
      printf("%i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of CELL\n");

  return -1;
}
