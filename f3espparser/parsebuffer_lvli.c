
int parsebuffer_lvli(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int size;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("LVLI/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"LVLD") == 0) {
      n = buffer_read_short(b);
      printf("LVLI/LVLD %i\n",n);
      n = buffer_read_ubyte(b);
#if 1
      printf("Chance None %i\n",n);
#else
      // Not used in Fallout3.esm.
      printf("Chance None %i\n",n & 0x7f);
      if (n & 0x80) {
	printf("  Flagged: Calculate from all levels <= PC's level\n");
      }
#endif
    } else if (strcmp(s,"LVLF") == 0) {
      n = buffer_read_short(b);
      printf("LVLI/LVLF %i\n",n);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Calculate from all levels <= PC's level\n");
      printf("       ^Calculate for each item in count\n");
      printf("      ^Use All\n");
    } else if (strcmp(s,"LVLO") == 0) {
      n = buffer_read_short(b);
      printf("LVLI/LVLO %i\n",n);
      size = n;
      if (size == 12) {
	n = buffer_read_short(b);
	printf("Level %i\n",n);
	n = buffer_read_short(b);
	printf("%i unknown\n",n);
	n = buffer_read_int(b);
	printf("Leveled Item FormID %i\n",n);
	n = buffer_read_short(b);
	printf("Count %i\n",n);
	n = buffer_read_short(b);
	printf("%i unknown\n",n);
#if 0
	// Not in Fallout3.esm.
      } else if (size == 8) {
	n = buffer_read_int(b);
	printf("Level %i\n",n);
	n = buffer_read_int(b);
	printf("Leveled Item FormID %i\n",n);
#endif
      } else {
	fprintf(stderr,"LVLO error\n");
      }
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("LVLI/DATA %i\n",n);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Calculate for each item in count\n");
    } else if (strcmp(s,"OBND") == 0) { // F
      n = buffer_read_short(b);
      printf("LVLI/OBND %i\n",n);
      parse_obnd(b);
    } else if (strcmp(s,"COED") == 0) { // F
      n = buffer_read_short(b);
      printf("LVLI/COED %i\n",n);
      parse_coed(b);
    } else if (strcmp(s,"LVLG") == 0) { // F
      n = buffer_read_short(b);
      printf("LVLI/LVLG %i\n",n);
      n = buffer_read_int(b);
      printf("Chance None Use Global FormID %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of LVLI\n");

  return -1;
}
