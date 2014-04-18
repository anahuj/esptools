
int parsebuffer_eczn(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int size;
  int num;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("ECZN/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("ECZN/DATA %i\n",n);
      n = buffer_read_int(b);
      printf("Owner FormID %i\n",n);
      n = buffer_read_byte(b);
      printf("Required Rank %i %% -1 NONE 0 DUMMY\n",n);
      n = buffer_read_byte(b);
      printf("Minimum Level %i\n",n);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Never Resets\n");
      printf("       ^Match PC Below Minimum Level\n");
      n = buffer_read_byte(b);
      printf("%i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of ECZN\n");

  return -1;
}
