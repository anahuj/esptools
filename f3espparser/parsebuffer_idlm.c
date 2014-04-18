
int parsebuffer_idlm(void *b)
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
      printf("IDLM/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"OBND") == 0) {
      n = buffer_read_short(b);
      printf("IDLM/OBND %i\n",n);
      parse_obnd(b);
    } else if (strcmp(s,"IDLF") == 0) { // F
      n = buffer_read_short(b);
      printf("IDLM/IDLF %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^0 Random 1 Run In Sequence\n");
      printf("      ^Do Once\n");
    } else if (strcmp(s,"IDLC") == 0) { // F
      n = buffer_read_short(b);
      printf("IDLM/IDLC %i\n",n);
      size = n;
      if (size == 1) {
	n = buffer_read_ubyte(b);
	printf("Number of Idles %i\n",n);
      }
      if (size == 4) {
	n = buffer_read_int(b);
	printf("Number of Idles %i\n",n);
      }
    } else if (strcmp(s,"IDLT") == 0) { // F
      n = buffer_read_short(b);
      printf("IDLM/IDLT %i\n",n);
      f = buffer_read_float(b);
      printf("Idle Timer Setting %f\n",f);
    } else if (strcmp(s,"IDLA") == 0) { // F
      n = buffer_read_short(b);
      printf("IDLM/IDLA %i\n",n);
      // num = value of IDLC
      num = n/4;
      for (i = 0; i < num; i++) {
	n = buffer_read_int(b);
	printf("Idle FormID %i\n",n);
      }
#if 0
      // Strange. No IDLB in Fallout3.esm at the second look.
    } else if (strcmp(s,"IDLB") == 0) { // F
      n = buffer_read_short(b);
      printf("IDLM/IDLB %i\n",n);
      // num = value of IDLC  XXXX verify
      num = n/4;
      for (i = 0; i < num; i++) {
	n = buffer_read_int(b);
	printf("%i\n",n);
      }
#endif
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of IDLM\n");

  return -1;
}
