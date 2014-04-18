
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
    if (strcmp(s,"NAME") == 0) {
      n = buffer_read_int(b);
      printf("WEAP/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_int(b);
      printf("WEAP/FNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_int(b);
      printf("WEAP/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"WPDT") == 0) {
      n = buffer_read_int(b);
      printf("WEAP/WPDT %i\n",n);
      f = buffer_read_float(b);
      printf("Weight %f\n",f);
      n = buffer_read_int(b);
      printf("Value %i\n",n);
      n = buffer_read_short(b);
      printf("Type %i %% 11 MarksmanThrown\n",n);
      n = buffer_read_short(b);
      printf("Health %i\n",n);
      f = buffer_read_float(b);
      printf("Speed %f\n",f);
      f = buffer_read_float(b);
      printf("Reach %f\n",f);
      n = buffer_read_short(b);
      printf("Enchantment %i\n",n);
      n = buffer_read_byte(b);
      printf("Damage Chop Min %i\n",n);
      n = buffer_read_byte(b);
      printf("Damage Chop Max %i\n",n);
      n = buffer_read_byte(b);
      printf("Damage Slash Min %i\n",n);
      n = buffer_read_byte(b);
      printf("Damage Slash Max %i\n",n);
      n = buffer_read_byte(b);
      printf("Damage Thrust Min %i\n",n);
      n = buffer_read_byte(b);
      printf("Damage Thrust Max %i\n",n);
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
    } else if (strcmp(s,"ITEX") == 0) {
      n = buffer_read_int(b);
      printf("WEAP/ITEX %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Icon \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ENAM") == 0) {
      n = buffer_read_int(b);
      printf("WEAP/ENAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Enchanting \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_int(b);
      printf("WEAP/SCRI %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Script \"%s\"\n",s2);
      free(s2);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of WEAP\n");

  return -1;
}
