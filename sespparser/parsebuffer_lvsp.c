
int parsebuffer_lvsp(void *b)
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
      printf("LVSP/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"LVLD") == 0) {
      n = buffer_read_short(b);
      printf("LVSP/LVLD %i\n",n);
      n = buffer_read_byte(b);
      printf("Chance None %i\n",n);
    } else if (strcmp(s,"LVLF") == 0) {
      n = buffer_read_short(b);
      printf("LVSP/LVLF %i\n",n);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Calculate from all levels <= PC's level\n");
      printf("       ^Calculate for each item in count\n");
      printf("      ^Use All Spells\n");
    } else if (strcmp(s,"LVLO") == 0) {
      n = buffer_read_short(b);
      printf("LVSP/LVLO %i\n",n);
      size = n;
      if (size == 12) {
	n = buffer_read_short(b);
	printf("Level %i\n",n);
	n = buffer_read_short(b);
	printf("%i\n",n);
	n = buffer_read_int(b);
	printf("FormID %i\n",n);
	n = buffer_read_short(b);
	printf("Count %i\n",n);
	n = buffer_read_short(b);
	printf("%i\n",n);
#if 0
      } else if (size == 8) {
	// Not in Oblivion.esm
	n = buffer_read_int(b);
	printf("Level %i\n",n);
	n = buffer_read_int(b);
	printf("FormID %i\n",n);
#endif
      } else {
	fprintf(stderr,"LVLO error\n");
      }
#if 0
    } else if (strcmp(s,"DATA") == 0) {
      // Not in Oblivion.esm
      n = buffer_read_short(b);
      printf("LVSP/DATA %i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
#endif
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of LVSP\n");

  return -1;
}
