
int parsebuffer_pgre(void *b)
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

  printf("refsearch 0x%.8x (dec%i) in %s, %s, %i, %i\n",global_formid,global_formid,global_worldspace,global_cell,global_cell_x,global_cell_y);

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("PGRE/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"NAME") == 0) {
      n = buffer_read_short(b);
      printf("PGRE/NAME %i\n",n);
      n = buffer_read_int(b);
      printf("Base Object FormID %i\n",n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("PGRE/DATA %i\n",n);
      f = buffer_read_float(b);
      printf("Position X %f\n",f);
      f = buffer_read_float(b);
      printf("Position Y %f\n",f);
      f = buffer_read_float(b);
      printf("Position Z %f\n",f);
      f = buffer_read_float(b);
      printf("Rotation X %f\n",f);
      f = buffer_read_float(b);
      printf("Rotation Y %f\n",f);
      f = buffer_read_float(b);
      printf("Rotation Z %f\n",f);
    } else if (strcmp(s,"XOWN") == 0) {
      n = buffer_read_short(b);
      printf("PGRE/XOWN %i\n",n);
      n = buffer_read_int(b);
      printf("Owner FormID %i\n",n);
    } else if (strcmp(s,"XRGD") == 0) { // F
      n = buffer_read_short(b);
      printf("PGRE/XRGD %i\n",n);
      m = n/28;
      for (i = 0; i < m; i++) {
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
	f = buffer_read_float(b);
	printf("%f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"XPWR") == 0) { // F
      n = buffer_read_short(b);
      printf("PGRE/XPWR %i\n",n);
#if 1
      n = buffer_read_int(b);
      printf("Placeable Water Ref FormID %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Reflected\n");
      printf("       ^Refracted\n");
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
#else
      n = buffer_read_int(b);
      printf("Refracted by Ref FormID %i ???? Placeable Water Ref FormID\n",n);
      n = buffer_read_int(b);
      printf("%i unknown ???? Flags: 1 Reflected 2 Refracted\n",n);
#endif
    } else if (strcmp(s,"XHLP") == 0) { // F
      n = buffer_read_short(b);
      printf("PGRE/XHLP %i\n",n);
      f = buffer_read_float(b);
      printf("Health%% %f %% Editor displays 100x\n",f);
    } else if (strcmp(s,"XSCL") == 0) {
      n = buffer_read_short(b);
      printf("PGRE/XSCL %i\n",n);
      f = buffer_read_float(b);
      printf("Scale %f\n",f);
    } else if (strcmp(s,"XESP") == 0) {
      n = buffer_read_short(b);
      printf("PGRE/XESP %i\n",n);
      n = buffer_read_int(b);
      printf("Enable Parent FormID %i\n",n);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Set Enable State to Opposite of Parent\n");
      printf("       ^Pop In\n");
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of PGRE\n");

  return -1;
}
