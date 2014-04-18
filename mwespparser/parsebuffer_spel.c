
char spel_effectname[100];

int parsebuffer_spel(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int enamindex;

  enamindex = 0;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"NAME") == 0) {
      n = buffer_read_int(b);
      printf("SPEL/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      spel_effectname[0] = '\0';
      strcpy(spel_effectname,s2);
      free(s2);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_int(b);
      printf("SPEL/FNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Full Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SPDT") == 0) {
      n = buffer_read_int(b);
      printf("SPEL/SPDT %i\n",n);
      n = buffer_read_int(b);
      printf("Type %i %% 0 Spells 1 Abilities 2 Blight Disease 3 Disease 4 Curse 5 Powers\n",n);
      n = buffer_read_int(b);
      printf("Spell Cost %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Auto Calculate Cost\n");
      printf("       ^PC Start Spell\n");
      printf("      ^Always Succeeds\n");
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"ENAM") == 0) {
      n = buffer_read_int(b);
      printf("SPEL/ENAM %i\n",n);
      n = buffer_read_short(b);
      printf("Effect %i\n",n);
      enamindex++;
      printf("xxxxspeleffect %i : %s / %i\n",n,spel_effectname,enamindex);
      n = buffer_read_byte(b);
      printf("%i (unknown)\n",n);
      n = buffer_read_byte(b);
      printf("Effect Parameter %i\n",n);
      n = buffer_read_int(b);
      printf("Range %i %% 0 Self 1 Touch 2 Target\n",n);
      n = buffer_read_int(b);
      printf("Area %i\n",n);
      n = buffer_read_int(b);
      printf("Duration %i\n",n);
      n = buffer_read_int(b);
      printf("Magnitude Min %i\n",n);
      n = buffer_read_int(b);
      printf("Magnitude Max %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of SPEL\n");

  return -1;
}
