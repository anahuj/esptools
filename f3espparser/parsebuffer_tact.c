
int parsebuffer_tact(void *b)
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
      printf("TACT/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("TACT/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("TACT/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("TACT/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"VNAM") == 0) {
      n = buffer_read_short(b);
      printf("TACT/VNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Voice Type FormID %i\n",n);
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_short(b);
      printf("TACT/SNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Looping Sound FormID %i\n",n);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_short(b);
      printf("TACT/SCRI %i\n",n);
      n = buffer_read_int(b);
      printf("Script FormID %i\n",n);
    } else if (strcmp(s,"OBND") == 0) {
      n = buffer_read_short(b);
      printf("TACT/OBND %i\n",n);
      parse_obnd(b);
    } else if (strcmp(s,"DEST") == 0) {
      n = buffer_read_short(b);
      printf("TACT/DEST %i\n",n);
      parse_dest(b);
    } else if (strcmp(s,"DSTD") == 0) {
      n = buffer_read_short(b);
      printf("TACT/DSTD %i\n",n);
      parse_dstd(b);
    } else if (strcmp(s,"DSTF") == 0) {
      n = buffer_read_short(b);
      printf("TACT/DSTF %i\n",n);
      // Empty.
    } else if (strcmp(s,"DMDL") == 0) { // F
      n = buffer_read_short(b);
      printf("TACT/DMDL %i\n",n);
      parse_dmdl(b,n);
    } else if (strcmp(s,"DMDT") == 0) { // F
      n = buffer_read_short(b);
      printf("TACT/DMDT %i\n",n);
      parse_dmdt(b,n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of TACT\n");

  return -1;
}
