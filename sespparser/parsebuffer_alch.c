
int parsebuffer_alch(void *b)
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
      printf("ALCH/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("ALCH/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("ALCH/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("ALCH/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("ALCH/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("ALCH/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("ALCH/DATA %i\n",n);
      f = buffer_read_float(b);
      printf("Weight %f\n",f);
    } else if (strcmp(s,"ENIT") == 0) {
      n = buffer_read_short(b);
      printf("ALCH/ENIT %i\n",n);
      n = buffer_read_int(b);
      printf("Potion Value %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^~Auto-Calculate\n");
      printf("       ^Food Item\n");
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"EFID") == 0) {
      n = buffer_read_short(b);
      printf("ALCH/EFID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"EFIT") == 0) {
      n = buffer_read_short(b);
      printf("ALCH/EFIT %i\n",n);
      parse_efit(b);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_short(b);
      printf("ALCH/SCRI %i\n",n);
      n = buffer_read_int(b);
      printf("Script FormID %i\n",n);
    } else if (strcmp(s,"SCIT") == 0) {
      n = buffer_read_short(b);
      printf("ALCH/SCIT %i\n",n);
      parse_scit(b,n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of ALCH\n");

  return -1;
}
