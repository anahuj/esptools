
int parsebuffer_splm(void *b)
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
      printf("SPLM/NAME %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"SPDT") == 0) {
      n = buffer_read_int(b);
      printf("SPLM/SPDT %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      s2 = buffer_read_nstring(b,24);
      printf("%s\n",s2);
      free(s2);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
      n = buffer_read_int(b);
      printf("%i\n",n);
      s2 = buffer_read_nstring(b,32);
      printf("%s\n",s2);
      free(s2);
      s2 = buffer_read_nstring(b,32);
      printf("%s\n",s2);
      free(s2);
#if 0
      n = buffer_read_int(b);
      printf("%i\n",n);
#else
      f = buffer_read_float(b);
      printf("%f\n",f);
#endif
      for (i = 0; i < 9; i++) { // 3th string?
	n = buffer_read_int(b);
	printf("%i\n",n);
      }
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"NPDT") == 0) {
      n = buffer_read_int(b);
      printf("SPLM/NPDT %i\n",n);
      s2 = buffer_read_nstring(b,16);
      printf("%s\n",s2);
      free(s2);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"NAM0") == 0) {
      n = buffer_read_int(b);
      printf("SPLM/NAM0 %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"XNAM") == 0) {
      n = buffer_read_int(b);
      printf("SPLM/XNAM %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"INAM") == 0) {
      n = buffer_read_int(b);
      printf("SPLM/INAM %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      s2 = buffer_read_nstring(b,23);
      printf("%s\n",s2);
      free(s2);
      n = buffer_read_int(b);
      printf("%i\n",n);
#if 1
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
#else
      // Not floats.
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
#endif
    } else if (strcmp(s,"TNAM") == 0) {
      n = buffer_read_int(b);
      printf("SPLM/TNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"VNAM") == 0) {
      n = buffer_read_int(b);
      printf("SPLM/VNAM %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else {
      printf("Unknown chunk name\n");
      printhexdump(b,-4,120);
      exit(-1);
    }
    free(s);
  }

  printf("End of SPLM\n");

  return -1;
}
