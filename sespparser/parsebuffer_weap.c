
int parsebuffer_weap(void *b)
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
      printf("WEAP/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("WEAP/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("WEAP/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("WEAP/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("WEAP/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("WEAP/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Icon \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("WEAP/DATA %i\n",n);
      n = buffer_read_int(b);
      printf("Type %i %% 0 BladeOneHand 1 BladeTwoHand 2 BluntOneHand 3 BluntTwoHand 4 Staff 5 Bow\n",n);
      f = buffer_read_float(b);
      printf("Speed %f\n",f);
      f = buffer_read_float(b);
      printf("Reach %f\n",f);
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
      n = buffer_read_int(b);
      printf("Value %i\n",n);
      n = buffer_read_int(b);
      printf("Health %i\n",n);
      f = buffer_read_float(b);
      printf("Weight %f\n",f);
      n = buffer_read_short(b);
      printf("Damage %i\n",n);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_short(b);
      printf("WEAP/SCRI %i\n",n);
      n = buffer_read_int(b);
      printf("Script FormID %i\n",n);
    } else if (strcmp(s,"ENAM") == 0) {
      n = buffer_read_short(b);
      printf("WEAP/ENAM %i\n",n);
      n = buffer_read_int(b);
      printf("Enchanting FormID %i\n",n);
    } else if (strcmp(s,"ANAM") == 0) {
      n = buffer_read_short(b);
      printf("WEAP/ANAM %i\n",n);
      n = buffer_read_short(b);
      printf("Enchantment %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of WEAP\n");

  return -1;
}
