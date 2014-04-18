
int parsebuffer_mstt(void *b)
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
      printf("MSTT/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("MSTT/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"OBND") == 0) {
      n = buffer_read_short(b);
      printf("MSTT/OBND %i\n",n);
      parse_obnd(b);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("MSTT/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("MSTT/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("MSTT/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_short(b);
      printf("MSTT/SNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Looping Sound FormID %i\n",n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("MSTT/DATA %i\n",n);
      n = buffer_read_byte(b);
      printf("On Local Map %i %% 0 Disabled 1 Enabled %% Duplicate from header flags 1\n",n);
    } else if (strcmp(s,"DEST") == 0) {
      n = buffer_read_short(b);
      printf("MSTT/DEST %i\n",n);
      parse_dest(b);
    } else if (strcmp(s,"DSTD") == 0) {
      n = buffer_read_short(b);
      printf("MSTT/DSTD %i\n",n);
      parse_dstd(b);
    } else if (strcmp(s,"DSTF") == 0) {
      n = buffer_read_short(b);
      printf("MSTT/DSTF %i\n",n);
      // Empty.
    } else if (strcmp(s,"DMDL") == 0) { // F
      n = buffer_read_short(b);
      printf("MSTT/DMDL %i\n",n);
      parse_dmdl(b,n);
    } else if (strcmp(s,"DMDT") == 0) { // F
      n = buffer_read_short(b);
      printf("MSTT/DMDT %i\n",n);
      parse_dmdt(b,n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of MSTT\n");

  return -1;
}
