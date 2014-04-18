
int parsebuffer_sbsp(void *b)
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
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("SBSP/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"DNAM") == 0) {
      n = buffer_read_short(b);
      printf("SBSP/DNAM %i\n",n);
#if 0
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
#else
      f = buffer_read_float(b);
      printf("X %f\n",f);
      f = buffer_read_float(b);
      printf("Y %f\n",f);
      f = buffer_read_float(b);
      printf("Z %f\n",f);
#endif
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of SBSP\n");

  return -1;
}
