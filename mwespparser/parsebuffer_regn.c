
int parsebuffer_regn(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f,g;
  unsigned int flags;
  int num;
  int tmploc;
  int size;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"NAME") == 0) {
      n = buffer_read_int(b);
      printf("REGN/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_int(b);
      printf("REGN/FNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"WEAT") == 0) {
      n = buffer_read_int(b);
      printf("REGN/WEAT %i\n",n);
      size = n;
      if (size >= 8) {
	n = buffer_read_ubyte(b);
	printf("Clear %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Cloudy %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Foggy %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Overcast %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Rain %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Thunder %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Ash %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Blight %i\n",n);
      }
      if (size >= 10) {
	// Tribunal
	n = buffer_read_ubyte(b);
	printf("Snow %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Blizzard %i\n",n);
      }
    } else if (strcmp(s,"BNAM") == 0) {
      n = buffer_read_int(b);
      printf("REGN/BNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Sleep Creature \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"CNAM") == 0) {
      n = buffer_read_int(b);
      printf("REGN/CNAM %i\n",n);
      // Color.
      n = buffer_read_ubyte(b);
      printf("Region Map Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Region Map Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Region Map Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_int(b);
      printf("REGN/SNAM %i\n",n);
      s2 = buffer_read_nstring(b,16);
      printf("Sound ID \"%s\"\n",s2);
      free(s2);
      // Color.
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      // Color.
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      // Color.
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      // Color.
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);

      n = buffer_read_ubyte(b);
      printf("Chance %i\n",n);
    } else if (strcmp(s,"WNAM") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("REGN/WNAM %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of REGN\n");

  return -1;
}
