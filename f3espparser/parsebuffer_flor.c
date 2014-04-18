
int parsebuffer_flor(void *b)
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
      n = buffer_read_short(b);
      printf("FLOR/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("FLOR/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_short(b);
      printf("FLOR/SCRI %i\n",n);
      n = buffer_read_int(b);
      printf("Script FormID %i\n",n);
    } else if (strcmp(s,"PFIG") == 0) {
      n = buffer_read_short(b);
      printf("FLOR/PFIG %i\n",n);
      n = buffer_read_int(b);
      printf("Ingredient FormID %i\n",n);
    } else if (strcmp(s,"PFPC") == 0) {
      n = buffer_read_short(b);
      printf("FLOR/PFPC %i\n",n);
      n = buffer_read_byte(b);
      printf("Spring %i\n",n);
      n = buffer_read_byte(b);
      printf("Summer %i\n",n);
      n = buffer_read_byte(b);
      printf("Fall %i\n",n);
      n = buffer_read_byte(b);
      printf("Winter %i\n",n);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("FLOR/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("FLOR/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("FLOR/MODT %i\n",n);
      parse_modt(b,n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of FLOR\n");

  return -1;
}
