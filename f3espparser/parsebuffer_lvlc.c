
int parsebuffer_lvlc(void *b)
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
      printf("LVLC/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"LVLD") == 0) {
      n = buffer_read_short(b);
      printf("LVLC/LVLD %i\n",n);
      n = buffer_read_byte(b);
      printf("Chance None %i\n",n);
    } else if (strcmp(s,"LVLF") == 0) {
      n = buffer_read_short(b);
      printf("LVLC/LVLF %i\n",n);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Calculate from all levels <= PC's level\n");
      printf("       ^Calculate for each item in count\n");
     } else if (strcmp(s,"LVLO") == 0) {
      n = buffer_read_short(b);
      printf("LVLC/LVLO %i\n",n);
      size = n;
      if (size == 12) {
	n = buffer_read_short(b);
	printf("Level %i\n",n);
	n = buffer_read_short(b); // unknown
	printf("XXXX LVLO unknown1 %i\n",n);
	n = buffer_read_int(b);
	printf("FormID %i\n",n);
	n = buffer_read_short(b);
	printf("Count %i\n",n);
	n = buffer_read_short(b); // unknown, does not equal to first unknown
	printf("XXXX LVLO unknown2 %i\n",n);
      } else if (size == 8) {
	n = buffer_read_int(b);
	printf("Level %i\n",n);
	n = buffer_read_int(b);
	printf("FormID %i\n",n);
	// Count = 1 by default.
      } else {
	fprintf(stderr,"LVLO error\n");
      }
    } else if (strcmp(s,"TNAM") == 0) {
      n = buffer_read_short(b);
      printf("LVLC/TNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Creature Template formid %i\n",n);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_short(b);
      printf("LVLC/SCRI %i\n",n);
      n = buffer_read_int(b);
      printf("Marker Script formid %i\n",n);
    } else if (strcmp(s,"OBND") == 0) { // F
      n = buffer_read_short(b);
      printf("LVLC/OBND %i\n",n);
      parse_obnd(b);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of LVLC\n");

  return -1;
}
