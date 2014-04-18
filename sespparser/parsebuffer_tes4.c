
int parsebuffer_tes4(void *b)
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
    if (strcmp(s,"HEDR") == 0) {
      n = buffer_read_short(b);
      printf("TES4/HEDR %i\n",n);
      f = buffer_read_float(b);
      printf("Version %f\n",f);
      n = buffer_read_int(b);
      printf("Number of records after TES4 record %i\n",n);
      n = buffer_read_uint(b);
      printf("%i\n",(int)n);
    } else if (strcmp(s,"CNAM") == 0) {
      n = buffer_read_short(b);
      printf("TES4/CNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_short(b);
      printf("TES4/SNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"MAST") == 0) {
      n = buffer_read_short(b);
      printf("TES4/MAST %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"OFST") == 0) {
      n = buffer_read_short(b);
      printf("TES4/OFST %i\n",n);
      buffer_skip_bytes(b,n);
    } else if (strcmp(s,"DELE") == 0) {
      n = buffer_read_short(b);
      printf("TES4/DELE %i\n",n);
      buffer_skip_bytes(b,n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("TES4/DATA %i\n",n);
      // Next is actually uint64.
      n = buffer_read_uint(b);
      printf("%i\n",n);
      n = buffer_read_uint(b);
      printf("%i\n",n);
    } else if (strcmp(s,"INTV") == 0) {
      n = buffer_read_short(b);
      printf("TES4/INTV %i\n",n);
      n = buffer_read_int(b);
      printf("unknown int %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of TES4\n");

  return -1;
}
