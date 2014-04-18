
int parsebuffer_spel(void *b)
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
      printf("SPEL/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("SPEL/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SPIT") == 0) {
      n = buffer_read_short(b);
      printf("SPEL/SPIT %i\n",n);
      n = buffer_read_int(b);
      printf("Type %i %% 0 Actor Effect 1 Disease 2 Power 3 Lesser Power 4 Ability 5 Poison 10 Addiction\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n); // Always 0 in Fallout3.esm.
      n = buffer_read_int(b);
      printf("%i\n",n); // Always 0 in Fallout3.esm.
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^~Auto-Calculate\n");
      printf("      ^PC Start Effect\n");
      printf("   ^Area Effect Ignores LOS\n");
      printf("  ^Script Effect Always Applies\n");
      printf(" ^Disallow Absorb/Reflect\n");
      printf("^Force Touch Explode\n");
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"EFID") == 0) {
      n = buffer_read_short(b);
      printf("SPEL/EFID %i\n",n);
      n = buffer_read_int(b);
      printf("Effect FormID %i\n",n);
    } else if (strcmp(s,"EFIT") == 0) {
      n = buffer_read_short(b);
      printf("SPEL/EFIT %i\n",n);
      parse_efit(b);
    } else if (strcmp(s,"SCIT") == 0) {
      n = buffer_read_short(b);
      printf("SPEL/SCIT %i\n",n);
      parse_scit(b,n);
    } else if (strcmp(s,"CTDA") == 0) { // F
      n = buffer_read_short(b);
      printf("SPEL/CTDA %i\n",n);
      parse_ctda(b,n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of SPEL\n");

  return -1;
}
