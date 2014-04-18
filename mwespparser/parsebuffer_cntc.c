
int parsebuffer_cntc(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int size;
  int numslcs1;
  int numslcs2;
  int numslcs3;

  numslcs1 = 0;
  numslcs2 = 0;
  numslcs3 = 0;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"NAME") == 0) {
      n = buffer_read_int(b);
      printf("CNTC/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"NPCO") == 0) {
      n = buffer_read_int(b);
      printf("CNTC/NPCO %i\n",n);
      n = buffer_read_int(b);
      printf("Item Count %i\n",n);
      s2 = buffer_read_nstring(b,32);
      printf("Item Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"INDX") == 0) {
      n = buffer_read_int(b);
      printf("CNTC/INDX %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"XIDX") == 0) {
      n = buffer_read_int(b);
      printf("CNTC/XIDX %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_int(b);
      printf("CNTC/SCRI %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Script \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SLCS") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CNTC/SLCS %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      numslcs1 = n;
      n = buffer_read_int(b);
      printf("%i\n",n);
      numslcs2 = n;
      n = buffer_read_int(b);
      printf("%i\n",n);
      numslcs3 = n;
    } else if (strcmp(s,"SLSD") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CNTC/SLSD %i\n",n);
      printf("data given by numslcs1:\n");
      for (i = 0; i < numslcs1; i++) {
	n = buffer_read_short(b);
	printf("%i\n",n);
      }
    } else if (strcmp(s,"SLLD") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CNTC/SLLD %i\n",n);
      printf("data given by numslcs2:\n");
      for (i = 0; i < numslcs2; i++) {
	n = buffer_read_int(b);
	printf("%i\n",n);
      }
    } else if (strcmp(s,"SLFD") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CNTC/SLFD %i\n",n);
      printf("data given by numslcs3:\n");
      for (i = 0; i < numslcs3; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"XHLT") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CNTC/XHLT %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"XCHG") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CNTC/XCHG %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"XSOL") == 0) {
      n = buffer_read_int(b);
      printf("CNTC/XSOL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else {
      printf("Unknown chunk name\n");
      printhexdump(b,-4,120);
      exit(-1);
    }
    free(s);
  }

  printf("End of CNTC\n");

  return -1;
}
