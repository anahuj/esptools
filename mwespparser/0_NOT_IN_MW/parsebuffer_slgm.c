
int parsebuffer_slgm(void *b)
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
      printf("SLGM/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("SLGM/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("SLGM/DATA %i\n",n);
      n = buffer_read_int(b);
      printf("Value %i\n",n);
      f = buffer_read_float(b);
      printf("Weight %f\n",f);
    } else if (strcmp(s,"SOUL") == 0) {
      n = buffer_read_short(b);
      printf("SLGM/SOUL %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Soul %i %% 0 None 1 Petty 2 Lesser 3 Common 4 Greater 5 Grand\n",n);
    } else if (strcmp(s,"SLCP") == 0) {
      n = buffer_read_short(b);
      printf("SLGM/SLCP %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Capacity %i %% 0 None 1 Petty 2 Lesser 3 Common 4 Greater 5 Grand\n",n);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_short(b);
      printf("SLGM/SCRI %i\n",n);
      n = buffer_read_int(b);
      printf("Script FormID %i\n",n);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("SLGM/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("SLGM/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("SLGM/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("SLGM/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of SLGM\n");

  return -1;
}
