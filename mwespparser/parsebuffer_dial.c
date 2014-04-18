
int parsebuffer_dial(void *b)
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
      printf("DIAL/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_int(b);
      printf("DIAL/DATA %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Dialogue Type %i %% 0 Topic 1 Voice 2 Greeting 3 Persuasion 4 Journal\n",n);
    } else if (strcmp(s,"XIDX") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("DIAL/XIDX %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else {
      printf("Unknown chunk name\n");
      printhexdump(b,-4,120);
      exit(-1);
    }
    free(s);
  }

  printf("End of DIAL\n");

  return -1;
}
