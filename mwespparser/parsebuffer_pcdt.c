
int parsebuffer_pcdt(void *b)
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
    if (strcmp(s,"DNAM") == 0) {
      n = buffer_read_int(b);
      printf("PCDT/DNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"PNAM") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("PCDT/PNAM %i\n",n);
      // Floats has been verified to be floats. Ints are floats, ints, or unknown.
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      for (i = 0; i < 16; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
#if 0
      n = buffer_read_int(b); // bytes? e.g. 0x02000001
      printf("%i\n",n);
      n = buffer_read_int(b); // bytes? e.g. 0x00010605
      printf("%i\n",n);
#else
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
#endif
      n = buffer_read_int(b);
      printf("%i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
      for (i = 0; i < 3; i++) {
	n = buffer_read_int(b);
	printf("%i\n",n);
      }
      for (i = 0; i < 4; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b); // int
      printf("%i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      n = buffer_read_int(b);
      printf("%i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
#if 1
      n = buffer_read_int(b);
      printf("%i\n",n);
#else
      // Not float.
      f = buffer_read_float(b);
      printf("%f\n",f);
#endif
    } else if (strcmp(s,"BNAM") == 0) {
      n = buffer_read_int(b);
      printf("PCDT/BNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"ENAM") == 0) {
      n = buffer_read_int(b);
      printf("PCDT/ENAM %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"LNAM") == 0) {
      n = buffer_read_int(b);
      printf("PCDT/LNAM %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"KNAM") == 0) {
      n = buffer_read_int(b);
      printf("PCDT/KNAM %i\n",n);
      for (i = 0; i < 10; i++) {
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	s2 = buffer_read_nstring(b,27);
	printf("%s\n",s2);
	free(s2);
	n = buffer_read_int(b); // part of the above string?
	printf("%i\n",n);
	n = buffer_read_int(b); // part of the above string?
	printf("%i\n",n);
	n = buffer_read_int(b);
	printf("%i\n",n);
      }
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_int(b);
      printf("PCDT/SNAM %i\n",n);
      for (i = 0; i < 90; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"NAM9") == 0) {
      n = buffer_read_int(b);
      printf("PCDT/NAM9 %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_int(b);
      printf("PCDT/FNAM %i\n",n);
      size = n;
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      // We assume the rest of FNAM is garbage.
      s2 = buffer_read_nstring(b,32);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"MNAM") == 0) {
      n = buffer_read_int(b);
      printf("PCDT/MNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"NAM0") == 0) {
      n = buffer_read_int(b);
      printf("PCDT/NAM0 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"NAM1") == 0) {
      n = buffer_read_int(b);
      printf("PCDT/NAM1 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"NAM2") == 0) {
      n = buffer_read_int(b);
      printf("PCDT/NAM2 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"NAM3") == 0) {
      n = buffer_read_int(b);
      printf("PCDT/NAM3 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"CNAM") == 0) {
      n = buffer_read_int(b);
      printf("PCDT/CNAM %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else {
      printf("Unknown chunk name\n");
      printhexdump(b,-4,120);
      exit(-1);
    }
    free(s);
  }

  printf("End of PCDT\n");

  return -1;
}
