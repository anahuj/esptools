
int parsebuffer_ligh(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int size;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"NAME") == 0) {
      n = buffer_read_int(b);
      printf("LIGH/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_int(b);
      printf("LIGH/FNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_int(b);
      printf("LIGH/SNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Sound ID \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_int(b);
      printf("LIGH/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"LHDT") == 0) {
      n = buffer_read_int(b);
      printf("LIGH/LHDT %i\n",n);
      f = buffer_read_float(b);
      printf("Weight %f\n",f);
      n = buffer_read_int(b);
      printf("Value %i\n",n);
      n = buffer_read_int(b);
      printf("Time %i\n",n);
      n = buffer_read_int(b);
      printf("Radius %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused/Color A)\n",n);

      n = buffer_read_ushort(b);
      printflags16(n);
      //      0000,0000,0000,0000
      printf("                  ^Dynamic\n");
      printf("                 ^Can Carry\n");
      printf("                ^Negative\n");
      printf("               ^Flicker\n");
      printf("             ^Fire\n");
      printf("            ^Off by default\n");
      printf("           ^Flicker Slow\n");
      printf("          ^Pulse\n");
      printf("        ^Pulse Slow\n");
      n = buffer_read_ushort(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"ITEX") == 0) {
      n = buffer_read_int(b);
      printf("LIGH/ITEX %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Icon \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_int(b);
      printf("LIGH/SCRI %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Script \"%s\"\n",s2);
      free(s2);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of LIGH\n");

  return -1;
}
