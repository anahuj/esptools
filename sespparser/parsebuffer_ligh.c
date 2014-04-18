
int parsebuffer_ligh(void *b)
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
      printf("LIGH/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("LIGH/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_short(b);
      printf("LIGH/SCRI %i\n",n);
      n = buffer_read_int(b);
      printf("Script FormID %i\n",n);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("LIGH/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("LIGH/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("LIGH/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("LIGH/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Icon Image \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("LIGH/DATA %i\n",n);
      size = n;
      if (size >= 24) {
	n = buffer_read_int(b);
	printf("Time %i\n",n);
	n = buffer_read_int(b);
	printf("Radius %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Color R %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Color G %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Color B %i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	flags = buffer_read_uint(b);
	printflags(flags);
	//      0000,0000,0000,0000,0000,0000,0000,0000
	printf("                                      ^Dynamic\n");
	printf("                                     ^Can Carry\n");
	printf("                                    ^Negative\n");
	printf("                                   ^Flicker\n");
	printf("                                ^Off by default\n");
	printf("                               ^Flicker Slow\n");
	printf("                              ^Pulse\n");
	printf("                            ^Pulse Slow\n");
	printf("                           ^Spot Light\n");
	printf("                          ^Spot Shadow\n");
	f = buffer_read_float(b);
	printf("Falloff Exponent %f\n",f);
	f = buffer_read_float(b);
	printf("FOV %f\n",f);
      }
      if (size >= 32) {
	n = buffer_read_int(b);
	printf("Value %i\n",n);
	f = buffer_read_float(b);
	printf("Weight %f\n",f);
      }
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_short(b);
      printf("LIGH/FNAM %i\n",n);
      f = buffer_read_float(b);
      printf("Fade %f\n",f);
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_short(b);
      printf("LIGH/SNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Sound FormID %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of LIGH\n");

  return -1;
}
