
int parsebuffer_ltex(void *b)
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
      printf("LTEX/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("LTEX/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"HNAM") == 0) {
      n = buffer_read_short(b);
      printf("LTEX/HNAM %i\n",n);
      n = buffer_read_byte(b);
      printf("Material Type %i %% 0 Stone 1 Cloth 2 Dirt 3 Glass 4 Grass 5 Metal 6 Organic 7 Skin 8 Water 9 Wood 10 Heavy Stone 11 Heavy Metal 12 Heavy Wood 13 Chain 14 Bottlecap 15 Elevator 16 Hollow Metal 17 Sheet Metal 18 Sand 19 Broken Concrete 20 Vehicle Body 21 Vehicle Part Solid 22 Vehicle Part Hollow 23 Barrel 24 Bottle 25 Soda Can 26 Pistol 27 Rifle 28 Shopping Cart 29 Lunchbox 30 Baby Rattle 31 Rubber Ball\n",n);
      n = buffer_read_byte(b);
      printf("Friction %i\n",n);
      n = buffer_read_byte(b);
      printf("Restitution %i\n",n);
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_short(b);
      printf("LTEX/SNAM %i\n",n);
      n = buffer_read_byte(b);
      printf("Texture Specular Exponent %i\n",n);
    } else if (strcmp(s,"GNAM") == 0) {
      n = buffer_read_short(b);
      printf("LTEX/GNAM %i\n",n);
      n = buffer_read_uint(b);
      printf("Potential Grass FormID %i\n",n);
    } else if (strcmp(s,"TNAM") == 0) {
      n = buffer_read_short(b);
      printf("LTEX/TNAM %i\n",n);
      n = buffer_read_uint(b);
      printf("Texture Set FormID %i\n",n);
      printf("ltex %i txst %i\n",global_formid,n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of LTEX\n");

  return -1;
}
