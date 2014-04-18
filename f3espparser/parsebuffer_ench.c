
int parsebuffer_ench(void *b)
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
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("ENCH/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("ENCH/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ENIT") == 0) {
      n = buffer_read_short(b);
      printf("ENCH/ENIT %i\n",n);
      n = buffer_read_int(b);
      printf("Type %i %% 2 Weapon 3 Apparel\n",n);
      n = buffer_read_int(b);
      printf("%i unknown\n",n);
      n = buffer_read_int(b);
      printf("%i unknown\n",n);
      flags = buffer_read_ubyte(b);
      printf("enchenitflags\n");
      printflags8(flags);
      //      0000,0000
      printf("        ^~Auto-Calculate\n");
      printf("       ^????\n");
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"EFID") == 0) {
      n = buffer_read_short(b);
      printf("ENCH/EFID %i\n",n);
      n = buffer_read_int(b); // F
      printf("Effect FormID %i\n",n);
    } else if (strcmp(s,"EFIT") == 0) {
      n = buffer_read_short(b);
      printf("ENCH/EFIT %i\n",n);
      parse_efit(b);
    } else if (strcmp(s,"SCIT") == 0) {
      n = buffer_read_short(b);
      printf("ENCH/SCIT %i\n",n);
      parse_scit(b,n);
    } else if (strcmp(s,"CTDA") == 0) { // F
      n = buffer_read_short(b);
      printf("ENCH/CTDA %i\n",n);
      parse_ctda(b,n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of ENCH\n");

  return -1;
}
