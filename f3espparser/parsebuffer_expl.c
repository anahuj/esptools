
int parsebuffer_expl(void *b)
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
      printf("EXPL/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("EXPL/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("EXPL/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Art file \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("EXPL/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"MNAM") == 0) {
      n = buffer_read_short(b);
      printf("EXPL/MNAM %i\n",n);
      n = buffer_read_int(b);
      printf("IS Mod FormID %i\n",n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("EXPL/DATA %i\n",n);
      f = buffer_read_float(b);
      printf("Force %f\n",f);
      f = buffer_read_float(b);
      printf("Damage %f\n",f);
      f = buffer_read_float(b);
      printf("Radius %f\n",f);
      n = buffer_read_int(b);
      printf("Light FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Sound 1 FormID %i\n",n);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("       ^Always Uses World Orientation\n");
      printf("     ^^Knock Down Living Actors: 00 Never 01 Always 10 By Formula\n");
      printf("   ^Ignore LOS Check\n");
      printf("  ^Push Exposion Source Ref Only\n");
      printf(" ^Ignore Imagespace Swap\n");
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      f = buffer_read_float(b);
      printf("IS Radius %f\n",f);
      n = buffer_read_int(b);
      printf("Impact Data Set %i\n",n);
      n = buffer_read_int(b);
      printf("Sound 2 FormID %i\n",n);
      f = buffer_read_float(b);
      printf("RAD Level %f\n",f);
      f = buffer_read_float(b);
      printf("Dissipation Time %f\n",f);
      f = buffer_read_float(b);
      printf("Radius %f\n",f);
      n = buffer_read_int(b);
      printf("Sound Level %i %% 0 Loud 1 Normal 2 Silent\n",n);
    } else if (strcmp(s,"OBND") == 0) {
      n = buffer_read_short(b);
      printf("EXPL/OBND %i\n",n);
      parse_obnd(b);
    } else if (strcmp(s,"EITM") == 0) { // F
      n = buffer_read_short(b);
      printf("EXPL/EITM %i\n",n);
      n = buffer_read_int(b);
      printf("Enchantment FormID %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of EXPL\n");

  return -1;
}
