
int parsebuffer_debr(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int size;
  int num;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("DEBR/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("DEBR/DATA %i\n",n);
      size = n;
      n = buffer_read_byte(b);
      printf("Percent %i\n",n);
      s2 = buffer_read_nstring(b,size-2);
      printf("Model Filename \"%s\"\n",s2);
      free(s2);
      n = buffer_read_byte(b);
      printf("Has Collision Data %i %% 0 No 1 Yes\n",n);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("DEBR/MODT %i\n",n);
      parse_modt(b,n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of DEBR\n");

  return -1;
}
