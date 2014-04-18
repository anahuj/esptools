
int parsebuffer_gras(void *b)
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
      printf("GRAS/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("GRAS/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("GRAS/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("GRAS/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("GRAS/DATA %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Density %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Min Slope %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Max Slope %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_short(b);
      printf("Units from water %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_int(b);
      printf("Location %i %% 0 Above At Least 1 Above At Most 2 Below At Least 3 Below At Most 4 Either At Least 5 Either At Most 6 Either At Most Above 7 Either At Most Below\n",n);
      f = buffer_read_float(b);
      printf("Position Range %f\n",f);
      f = buffer_read_float(b);
      printf("Height Range %f\n",f);
      f = buffer_read_float(b);
      printf("Color Range %f\n",f);
      f = buffer_read_float(b);
      printf("Wave Period %f\n",f);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Vertex Lighting\n");
      printf("       ^Uniform Scaling\n");
      printf("      ^Fit to Slope\n");
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of GRAS\n");

  return -1;
}
