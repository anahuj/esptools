
int parsebuffer_bsgn(void *b)
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
      printf("BSGN/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_int(b);
      printf("BSGN/FNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"TNAM") == 0) {
      n = buffer_read_int(b);
      printf("BSGN/TNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Constellation Image \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DESC") == 0) {
      n = buffer_read_int(b);
      printf("BSGN/DESC %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Description \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"NPCS") == 0) {
      n = buffer_read_int(b);
      printf("BSGN/NPCS %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Spell \"%s\"\n",s2);
      free(s2);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of BSGN\n");

  return -1;
}
