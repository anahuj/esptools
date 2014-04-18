
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

#if PRINT_SCPT_SCTX_TO_FILE
  char fname[20];
  FILE *fp;
#endif

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("SCPT/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"SCHR") == 0) {
      n = buffer_read_short(b);
      printf("SCPT/SCHR %i\n",n);
      parse_schr(b);
#if 0
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("Number of the script objects (SCRO) and refs (SCRV) %i\n",n);
      n = buffer_read_int(b);
      printf("Size of the compiled script %i\n",n);
      n = buffer_read_int(b);
      printf("Number of the script variables %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
#endif
    } else if (strcmp(s,"SCDA") == 0) {
      n = buffer_read_short(b);
      printf("SCPT/SCDA %i\n",n);
      parse_scda(b,n);
    } else if (strcmp(s,"SCTX") == 0) {
      n = buffer_read_ushort(b);
      printf("SCPT/SCTX %i\n",n);
      parse_sctx(b,n);
    } else if (strcmp(s,"SCRV") == 0) {
      n = buffer_read_short(b);
      printf("SCPT/SCRV %i\n",n);
      n = buffer_read_int(b);
      printf("Ref variable index %i\n",n);
    } else if (strcmp(s,"SCRO") == 0) {
      n = buffer_read_short(b);
      printf("SCPT/SCRO %i\n",n);
      parse_scro(b);
#if 0
      n = buffer_read_int(b);
      printf("Script object FormID %i %% 20 means Player\n",n);
#endif
    } else if (strcmp(s,"SLSD") == 0) {
      n = buffer_read_short(b);
      printf("SCPT/SLSD %i\n",n);
      parse_slsd(b);
#if 0
      n = buffer_read_int(b);
      printf("Index of the script variable %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_byte(b);
      printf("Type of the script variable %i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
#if 1
      // How to get these bits as float?
      // ((float *)(&n))[0] does not work.
      // Copying data byte by byte fails for the same reason
      // as above.
      // Do I really have to check each bit and built the float value
      // myself? I have no idea what is the format of float.
      m = buffer_getloc(b);
      n = buffer_read_int(b);
      printf("%i -- ",n);
      buffer_setloc(b,m);
      f = buffer_read_float(b);
      printf("%f\n",f);
#else
      // Why ((int *)(&f))[0] does not work?
      // Strange: fint = &f technique first did not work, but
      // adding fuc technique, fint techniues started working.
      // What is the proper way to examine bits of a float variable?
      f = buffer_read_float(b);
      // printf("%i -- %f\n",((int *)(&f))[0],f);
      fuc = &f;
      fint = &f;
      printf("%i -- %f -- %i %i %i %i\n",*fint,f,fuc[0],fuc[1],fuc[2],fuc[3]);
#endif
#endif
    } else if (strcmp(s,"SCVR") == 0) {
      n = buffer_read_short(b);
      printf("SCPT/SCVR %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Variable name \"%s\"\n",s2);
      free(s2);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of SCPT\n");

  return -1;
}
