
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

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("ENCH/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("ENCH/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"ENIT") == 0) {
      n = buffer_read_short(b);
      printf("ENCH/ENIT %i\n",n);
      n = buffer_read_int(b);
      printf("Type %i %% 0 Scroll 1 Staff 2 Weapon 3 Apparel\n",n);
      n = buffer_read_int(b);
      printf("Charge Amount %i\n",n);
      n = buffer_read_int(b);
      printf("Enchantment Cost %i\n",n);
      flags = buffer_read_uint(b);
      printflags(flags);
      //      0000,0000,0000,0000,0000,0000,0000,0000
      printf("                                      ^~Auto-Calculate\n");
    } else if (strcmp(s,"EFID") == 0) {
      n = buffer_read_short(b);
      printf("ENCH/EFID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"EFIT") == 0) {
      n = buffer_read_short(b);
      printf("ENCH/EFIT %i\n",n);
      parse_efit(b);
    } else if (strcmp(s,"SCIT") == 0) {
      n = buffer_read_short(b);
      printf("ENCH/SCIT %i\n",n);
      parse_scit(b,n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of ENCH\n");

  return -1;
}
