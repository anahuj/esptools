
#define PRINT_SCPT_SCTX_TO_FILE 0

#if PRINT_SCPT_SCTX_TO_FILE
int global_scpt_sctx_file_number = 1;
#endif

int parsebuffer_scpt(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  int *fint;
  unsigned char *fuc;
  unsigned int flags;
  unsigned char *cs;
  void *bcs;
  int numslcs1;
  int numslcs2;
  int numslcs3;

  numslcs1 = 0;
  numslcs2 = 0;
  numslcs3 = 0;

#if PRINT_SCPT_SCTX_TO_FILE
  char fname[20];
  FILE *fp;
#endif

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"SCHD") == 0) {
      n = buffer_read_int(b);
      printf("SCPT/SCHD %i\n",n);
      s2 = buffer_read_nstring(b,32);
      printf("Script Name \"%s\"\n",s2);
      free(s2);
      n = buffer_read_int(b);
      printf("Number of local variables %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("Size of the compiled script %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"SCDT") == 0) {
      n = buffer_read_int(b);
      printf("SCPT/SCDT %i\n",n);
#if 1
      cs = buffer_read_bytes(b,n);
      bcs = buffer_new(cs,n);
      parse_compiledscript_mw(bcs);
      buffer_free(bcs);
      free(cs);
#else
      buffer_skip_bytes(b,n);
      printf("XXXX skipping compiled script\n");
#endif
    } else if (strcmp(s,"SCTX") == 0) {
      n = buffer_read_int(b);
      printf("SCPT/SCTX %i\n",n);
      parse_sctx(b,n);
    } else if (strcmp(s,"SCVR") == 0) {
      n = buffer_read_int(b);
      printf("SCPT/SCVR %i\n",n);
      s2 = buffer_read_nstring(b,n);
      for (i = 0; i < n-1; i++) {
	if (s2[i] == 0) {
	  s2[i] = '\n';
	}
      }
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"SLCS") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("SCPT/SLCS %i\n",n);
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
      printf("SCPT/SLSD %i\n",n);
      printf("data given by numslcs1:\n");
      for (i = 0; i < numslcs1; i++) {
	n = buffer_read_short(b);
	printf("%i\n",n);
      }
    } else if (strcmp(s,"SLLD") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("SCPT/SLLD %i\n",n);
      printf("data given by numslcs2:\n");
      for (i = 0; i < numslcs2; i++) {
	n = buffer_read_int(b);
	printf("%i\n",n);
      }
    } else if (strcmp(s,"SLFD") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("SCPT/SLFD %i\n",n);
      printf("data given by numslcs3:\n");
      for (i = 0; i < numslcs3; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"RNAM") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("SCPT/RNAM %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else {
      printf("Unknown chunk name\n");
      printhexdump(b,-4,120);
      exit(-1);
    }
    free(s);
  }

  printf("End of SCPT\n");

  return -1;
}
