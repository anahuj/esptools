
char alch_effectname[100];

int parsebuffer_alch(void *b)
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
      printf("ALCH/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      alch_effectname[0] = '\0';
      strcpy(alch_effectname,s2);
      free(s2);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_int(b);
      printf("ALCH/FNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_int(b);
      printf("ALCH/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"TEXT") == 0) {
      n = buffer_read_int(b);
      printf("ALCH/TEXT %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Icon \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ALDT") == 0) {
      n = buffer_read_int(b);
      printf("ALCH/ALDT %i\n",n);
      f = buffer_read_float(b);
      printf("Weight %f\n",f);
      n = buffer_read_int(b);
      printf("Potion Value %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Auto Calculate Value\n");
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"ENAM") == 0) {
      n = buffer_read_int(b);
      printf("ALCH/ENAM %i\n",n);
      n = buffer_read_short(b);
      printf("Effect %i\n",n);
      enamindex++;
      printf("xxxxalcheffect %i : %s / %i\n",n,alch_effectname,enamindex);
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
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_int(b);
      printf("ALCH/SCRI %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Script \"%s\"\n",s2);
      free(s2);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of ALCH\n");

  return -1;
}
