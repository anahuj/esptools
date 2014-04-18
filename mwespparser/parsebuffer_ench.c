
char ench_effectname[100];

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
  int enamindex;

  enamindex = 0;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"NAME") == 0) {
      n = buffer_read_int(b);
      printf("ENCH/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      ench_effectname[0] = '\0';
      strcpy(ench_effectname,s2);
      free(s2);
    } else if (strcmp(s,"ENDT") == 0) {
      n = buffer_read_int(b);
      printf("ENCH/ENDT %i\n",n);
      n = buffer_read_int(b);
      printf("Cast Type %i %% 0 Cast Once 1 Cast When Strikes 2 Cast When Used 3 Constant Effect\n",n);
      n = buffer_read_int(b);
      printf("Enchantment Cost %i\n",n);
      n = buffer_read_int(b);
      printf("Charge Amount %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Auto Calculate\n");
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"ENAM") == 0) {
      n = buffer_read_int(b);
      printf("ENCH/ENAM %i\n",n);
      n = buffer_read_short(b);
      printf("Effect %i\n",n);
      enamindex++;
      printf("xxxxencheffect %i : %s / %i\n",n,ench_effectname,enamindex);
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

  printf("End of ENCH\n");

  return -1;
}
