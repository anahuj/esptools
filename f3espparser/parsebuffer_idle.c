
int parsebuffer_idle(void *b)
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
      printf("IDLE/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"ANAM") == 0) { // F
      n = buffer_read_short(b);
      printf("IDLE/ANAM %i\n",n);
      size = n;
      n = buffer_read_int(b);
      printf("Parent IDLE FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Previous IDLE FormID %i\n",n);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("IDLE/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Art file \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("IDLE/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"CTDA") == 0) {
      n = buffer_read_short(b);
      printf("IDLE/CTDA %i\n",n);
      parse_ctda(b,n);
    } else if (strcmp(s,"CTDT") == 0) {
      n = buffer_read_short(b);
      printf("IDLE/CTDT %i\n",n);
      parse_ctdt(b);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("IDLE/DATA %i\n",n);
      size = n;
      if (size == 6) {
	n = buffer_read_ubyte(b);
	printflags8(n);
	//      0000,0000
	printf("     ^^^^Animation Type %i\n",0x7f & n);
	printf("^~Must return a file\n");
	// printf("Animation Type %i\n",0x7f & n);
	n = buffer_read_ubyte(b);
	printf("Looping Min %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Looping Max %i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("Replay Delay %i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
      } else {
	n = buffer_read_ubyte(b);
	printflags8(n);
	//      0000,0000
	printf("   ^^^^^^Animation Type %i\n",0x7f & n);
	printf("^~Must return a file\n");
	// printf("Animation Type %i\n",0x7f & n);
	n = buffer_read_ubyte(b);
	printf("Looping Min %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Looping Max %i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("Replay Delay %i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printflags8(n);
	//      0000,0000
	printf("        ^No Attacking\n");
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
      }
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of IDLE\n");

  return -1;
}
