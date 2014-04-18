
int parsebuffer_game(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int size;
  unsigned char *buf;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"NAME") == 0) {
      n = buffer_read_int(b);
      printf("GAME/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"ONAM") == 0) {
      n = buffer_read_int(b);
      printf("GAME/ONAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"GMDT") == 0) {
      n = buffer_read_int(b);
      printf("GAME/GMDT %i\n",n);
      s2 = buffer_read_nstring(b,n-4*13);
      printf("%s\n",s2);
      free(s2);
      for (i = 0; i < 13; i++) {
	n = buffer_read_int(b);
	printf("%i\n",n);
      }
    } else {
      printf("Unknown chunk name\n");
      printhexdump(b,-4,120);
      exit(-1);
    }
    free(s);
  }

  printf("End of GAME\n");

  return -1;
}
