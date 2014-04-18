
int parsebuffer_clmt(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int num;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("CLMT/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"WLST") == 0) { // F check REGN/RDWT
      n = buffer_read_short(b);
      printf("CLMT/WLST %i\n",n);
      num = n/12;
      for (i = 0; i < num; i++) {
	n = buffer_read_uint(b);
	printf("Weather Type FormID %i\n",n);
	n = buffer_read_int(b);
	printf("Chance %i\n",n);
	n = buffer_read_int(b); // F
	printf("Global %i\n",n);
      }
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_short(b);
      printf("CLMT/FNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Sun Texture \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"GNAM") == 0) {
      n = buffer_read_short(b);
      printf("CLMT/GNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Sun Glare Texture \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("CLMT/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Night Sky \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("CLMT/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("CLMT/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"TNAM") == 0) {
      n = buffer_read_short(b);
      printf("CLMT/TNAM %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Sunrise Begin %i (%.2i:%.2i)\n",n,(10*n)/60,(10*n)%60);
      n = buffer_read_ubyte(b);
      printf("Sunrise End %i (%.2i:%.2i)\n",n,(10*n)/60,(10*n)%60);
      n = buffer_read_ubyte(b);
      printf("Sunset Begin %i (%.2i:%.2i)\n",n,(10*n)/60,(10*n)%60);
      n = buffer_read_ubyte(b);
      printf("Sunset End %i (%.2i:%.2i)\n",n,(10*n)/60,(10*n)%60);
      n = buffer_read_ubyte(b);
      printf("Volatility %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("  ^^^^^^^Phase Length = %i (Complete Moon Cycle = 8 * %i = %i days)\n", 0x3f & n, 0x3f & n, 8*(0x3f & n));
      printf(" ^Secunda\n");
      printf("^Masser\n");
      printf("Note: Secunda and Masser are in Fallout 3 editor as well, weird\n");
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of CLMT\n");

  return -1;
}
