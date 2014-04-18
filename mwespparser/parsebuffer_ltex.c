
int parsebuffer_ltex(void *b)
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
      printf("LTEX/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"INTV") == 0) {
      n = buffer_read_int(b);
      printf("LTEX/INTV %i\n",n);
      n = buffer_read_int(b);
      printf("Index %i\n",n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_int(b);
      printf("LTEX/DATA %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Texture Filename \"%s\"\n",s2);
      free(s2);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of LTEX\n");

  return -1;
}
