
int parsebuffer_lgtm(void *b)
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
      printf("LGTM/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("LGTM/DATA %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Ambient Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Ambient Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Ambient Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("Directional Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Directional Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Directional Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("Fog Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Fog Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Fog Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Fog Near %i\n",n);
      f = buffer_read_float(b);
      printf("Fog Far %f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      n = buffer_read_int(b);
      printf("Directional Rotation XY %i\n",n);
      n = buffer_read_int(b);
      printf("Directional Rotation Z %i\n",n);
      f = buffer_read_float(b);
      printf("Directional Fade %f\n",f);
      f = buffer_read_float(b);
      printf("Fog Clip Dist %f\n",f);
      f = buffer_read_float(b);
      printf("Fog Pow %f\n",f);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of LGTM\n");

  return -1;
}
