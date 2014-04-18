
int parsebuffer_levc(void *b)
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
      printf("LEVC/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_int(b);
      printf("LEVC/DATA %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Calculate from all levels <= PC's level\n");
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"NNAM") == 0) {
      n = buffer_read_int(b);
      printf("LEVC/NNAM %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Chance None %i\n",n);
    } else if (strcmp(s,"CNAM") == 0) {
      n = buffer_read_int(b);
      printf("LEVC/CNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Creature Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"INDX") == 0) {
      n = buffer_read_int(b);
      printf("LEVC/INDX %i\n",n);
      n = buffer_read_int(b);
      printf("Number of levels %i\n",n);
    } else if (strcmp(s,"INTV") == 0) {
      n = buffer_read_int(b);
      printf("LEVC/INTV %i\n",n);
      n = buffer_read_short(b);
      printf("PC Level %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of LEVC\n");

  return -1;
}
