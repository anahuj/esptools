
int parsebuffer_sndg(void *b)
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
    if (strcmp(s,"NAME") == 0) {
      n = buffer_read_int(b);
      printf("SNDG/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_int(b);
      printf("SNDG/DATA %i\n",n);
      n = buffer_read_int(b);
      printf("Type %i %% 0 Left 1 Right 2 SwimLeft 3 SwimRight 4 Moan 5 Roar 6 Scream 7 Land\n",n);
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_int(b);
      printf("SNDG/SNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Sound \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"CNAM") == 0) {
      n = buffer_read_int(b);
      printf("SNDG/CNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Creature \"%s\"\n",s2);
      free(s2);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of SNDG\n");

  return -1;
}
