
int parsebuffer_glob(void *b)
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
      printf("GLOB/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_int(b);
      printf("GLOB/FNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Variable Type \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"FLTV") == 0) {
      n = buffer_read_int(b);
      printf("GLOB/FLTV %i\n",n);
      m = buffer_getloc(b);
      f = buffer_read_float(b);
      buffer_setloc(b,m);
      s2 = buffer_read_nstring(b,n);
      printf("Value %f / \"%s\"\n",f,s2);
      free(s2);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of GLOB\n");

  return -1;
}
