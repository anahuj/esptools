
int parsebuffer_soun(void *b)
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
      printf("SOUN/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_int(b);
      printf("SOUN/FNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Sound \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_int(b);
      printf("SOUN/DATA %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Volume %i (%f)\n",n,(float)n/255.0);
      n = buffer_read_ubyte(b);
      printf("Min Range %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Max Range %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of SOUN\n");

  return -1;
}
