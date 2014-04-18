
int parsebuffer_ipct(void *b)
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
      printf("IPCT/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("IPCT/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Effect Impact NIF \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("IPCT/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("IPCT/DATA %i\n",n);
      f = buffer_read_float(b);
      printf("Effect Duration %f\n",f);
      n = buffer_read_int(b);
      printf("Effect Orientation %i %% 0 Surface Normal 1 Projectile Vector 2 Projectile Reflection \n",n);
      f = buffer_read_float(b);
      printf("Angle Threshold %f\n",f);
      f = buffer_read_float(b);
      printf("Placement Radius %f\n",f);
      n = buffer_read_int(b);
      printf("Sound Level %i %% 0 Loud 1 Normal 2 Silent\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^~Has Own Decal Data\n");
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"DODT") == 0) {
      n = buffer_read_short(b);
      printf("IPCT/DODT %i\n",n);
      f = buffer_read_float(b);
      printf("Min Width %f\n",f);
      f = buffer_read_float(b);
      printf("Max Width %f\n",f);
      f = buffer_read_float(b);
      printf("Min Height %f\n",f);
      f = buffer_read_float(b);
      printf("Max Height %f\n",f);
      f = buffer_read_float(b);
      printf("Depth %f\n",f);
      f = buffer_read_float(b);
      printf("Shininess %f\n",f);
      f = buffer_read_float(b);
      printf("Parallax Scale %f\n",f);
      n = buffer_read_ubyte(b);
      printf("Parallax Passes %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Parallax\n");
      printf("       ^Alpha Blending\n");
      printf("      ^Alpha Testing\n");
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_short(b);
      printf("IPCT/SNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Impact Sounds Sound 1 FormID %i\n",n);
    } else if (strcmp(s,"NAM1") == 0) {
      n = buffer_read_short(b);
      printf("IPCT/NAM1 %i\n",n);
      n = buffer_read_int(b);
      printf("Impact Sounds Sound 2 FormID %i\n",n);
    } else if (strcmp(s,"DNAM") == 0) {
      n = buffer_read_short(b);
      printf("IPCT/DNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Texture Set FormID %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of IPCT\n");

  return -1;
}
