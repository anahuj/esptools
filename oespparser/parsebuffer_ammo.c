
int parsebuffer_ammo(void *b)
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
      printf("AMMO/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("AMMO/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("AMMO/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("AMMO/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("AMMO/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("AMMO/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Icon \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ENAM") == 0) {
      n = buffer_read_short(b);
      printf("AMMO/ENAM %i\n",n);
      n = buffer_read_int(b);
      printf("Enchanting FormID %i\n",n);
    } else if (strcmp(s,"ANAM") == 0) {
      n = buffer_read_short(b);
      printf("AMMO/ANAM %i\n",n);
      n = buffer_read_ushort(b);
      printf("Enchantment %i\n",n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("AMMO/DATA %i\n",n);
      f = buffer_read_float(b);
      printf("Speed %f\n",f);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Ignores Normal Weapon Resistance\n");
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_uint(b);
      printf("Value %i\n",n);
      f = buffer_read_float(b);
      printf("Weight %f\n",f);
      n = buffer_read_ushort(b);
      printf("Damage %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of AMMO\n");

  return -1;
}
