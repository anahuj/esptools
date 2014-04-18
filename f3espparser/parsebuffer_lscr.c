
int parsebuffer_lscr(void *b)
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
      n = buffer_read_ushort(b);
      printf("LSCR/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_ushort(b);
      printf("LSCR/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Loading Screen Image \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DESC") == 0) {
      n = buffer_read_ushort(b);
      printf("LSCR/DESC %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Loading Screen Text \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"LNAM") == 0) {
      n = buffer_read_ushort(b);
      printf("LSCR/LNAM %i\n",n);
      n = buffer_read_uint(b);
      printf("FormID %i\n",n);
#if 0
      n = buffer_read_uint(b);
      printf("World Space FormID %i\n",n);
      n = buffer_read_short(b);
      printf("WS Cell X Coordinate %i\n",n);
      n = buffer_read_short(b);
      printf("WS Cell Y Coordinate %i\n",n);
#else
      n = buffer_read_uint(b);
      printf("%i\n",n);
      n = buffer_read_short(b);
      printf("%i\n",n);
      n = buffer_read_short(b);
      printf("%i\n",n);
#endif
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of LSCR\n");

  return -1;
}
