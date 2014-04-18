

int parsebuffer_hdpt(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int num;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("HDPT/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("HDPT/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("HDPT/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODS") == 0) {
      n = buffer_read_short(b);
      printf("HDPT/MODS %i\n",n);
      parse_mods(b);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("HDPT/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("HDPT/DATA %i\n",n);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Playable\n");
    } else if (strcmp(s,"HNAM") == 0) {
      n = buffer_read_short(b);
      printf("HDPT/HNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Extra Part Head Part FormID %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of HDPT\n");

  return -1;
}

