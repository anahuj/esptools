
int parsebuffer_levi(void *b)
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
      printf("LEVI/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_int(b);
      printf("LEVI/DATA %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Calculate for each item in count\n");
      printf("       ^Calculate from all levels <= PC's level\n");
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"NNAM") == 0) {
      n = buffer_read_int(b);
      printf("LEVI/NNAM %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Chance None %i\n",n);
    } else if (strcmp(s,"INAM") == 0) {
      n = buffer_read_int(b);
      printf("LEVI/INAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Item Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"INDX") == 0) {
      n = buffer_read_int(b);
      printf("LEVI/INDX %i\n",n);
      n = buffer_read_int(b);
      printf("Number of levels %i\n",n);
    } else if (strcmp(s,"INTV") == 0) {
      n = buffer_read_int(b);
      printf("LEVI/INTV %i\n",n);
      n = buffer_read_short(b);
      printf("PC Level %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of LEVI\n");

  return -1;
}
