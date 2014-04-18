
int parsebuffer_scpt(void *b)
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
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
#endif
    } else if (strcmp(s,"SCDA") == 0) {
      n = buffer_read_short(b);
      printf("SCPT/SCDA %i\n",n);
      parse_scda(b,n);
    } else if (strcmp(s,"SCTX") == 0) {
      n = buffer_read_short(b);
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
    } else if (strcmp(s,"SLSD") == 0) {
      n = buffer_read_short(b);
      printf("SCPT/SLSD %i\n",n);
      parse_slsd(b);
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
