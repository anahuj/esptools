
int parsebuffer_imgs(void *b)
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
      printf("IMGS/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"DNAM") == 0) {
      n = buffer_read_short(b);
      printf("IMGS/DNAM %i\n",n);
      size = n;
#if 0
      num = size/4;
      for (i = 0; i < num; i++) {
	n = buffer_read_int(b);
	printf("%i\n",n);
      }
#else
      // if (size >= 132) {
      f = buffer_read_float(b);
      printf("HDR Eye Adapt Speed %f\n",f);
      f = buffer_read_float(b);
      printf("HDR Blur Radius %f\n",f);
      f = buffer_read_float(b);
      printf("HDR Blur Passes %f\n",f);
      f = buffer_read_float(b);
      printf("HDR Emissive Mult %f\n",f);
      f = buffer_read_float(b);
      printf("HDR Target LUM %f\n",f);
      f = buffer_read_float(b);
      printf("HDR Upper LUM Clamp %f\n",f);
      f = buffer_read_float(b);
      printf("HDR Bright Scale %f\n",f);
      f = buffer_read_float(b);
      printf("HDR Bright Clamp %f\n",f);
      f = buffer_read_float(b);
      printf("HDR LUM Ramp No Tex %f\n",f);
      f = buffer_read_float(b);
      printf("HDR LUM Ramp Min %f\n",f);
      f = buffer_read_float(b);
      printf("HDR LUM Ramp Max %f\n",f);
      f = buffer_read_float(b);
      printf("HDR Sunlight Dimmer %f\n",f);
      f = buffer_read_float(b);
      printf("HDR Grass Dimmer %f\n",f);
      f = buffer_read_float(b);
      printf("HDR Tree Dimmer %f\n",f);
      f = buffer_read_float(b);
      printf("HDR Skin Dimmer %f\n",f);
      f = buffer_read_float(b);
      printf("Bloom Blur Radius %f\n",f);
      f = buffer_read_float(b);
      printf("Bloom Alpha Mult Interior %f\n",f);
      f = buffer_read_float(b);
      printf("Bloom Alpha Mult Exterior %f\n",f);
      f = buffer_read_float(b);
      printf("Get Hit Blur Radius %f\n",f);
      f = buffer_read_float(b);
      printf("Get Hit Blur Damping Constant %f\n",f);
      f = buffer_read_float(b);
      printf("Get Hit Damping Constant %f\n",f);
      f = buffer_read_float(b);
      printf("Night Eye Tint Color R %f\n",f);
      f = buffer_read_float(b);
      printf("Night Eye Tint Color G %f\n",f);
      f = buffer_read_float(b);
      printf("Night Eye Tint Color B %f\n",f);
      f = buffer_read_float(b);
      printf("Night Eye Brightness %f\n",f);
      f = buffer_read_float(b);
      printf("Cinematic Saturation Value %f\n",f);
      f = buffer_read_float(b);
      printf("Cinematic Contrast Avg Lum Value %f\n",f);
      f = buffer_read_float(b);
      printf("Cinematic Contrast Value %f\n",f);
      f = buffer_read_float(b);
      printf("Cinematic Brightness Value %f\n",f);
      f = buffer_read_float(b);
      printf("Cinematic Tint Color R %f\n",f);
      f = buffer_read_float(b);
      printf("Cinematic Tint Color G %f\n",f);
      f = buffer_read_float(b);
      printf("Cinematic Tint Color B %f\n",f);
      f = buffer_read_float(b);
      printf("Cinematic Tint Value %f\n",f);
      if (size >= 148) {
	n = buffer_read_ubyte(b);
	printflags8(n);
	//      0000,0000
	printf("     ^^^^Unknown flags\n");
	n = buffer_read_byte(b);
	printf("%i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
	n = buffer_read_int(b);
	printf("%i\n",n);
	n = buffer_read_int(b);
	printf("%i\n",n);
	n = buffer_read_int(b);
	printf("%i\n",n);
      }
      if (size >= 152) {
	n = buffer_read_ubyte(b);
	printflags8(n);
	//      0000,0000
	printf("        ^Cinematic Saturation Enable\n");
	printf("       ^Cinematic Contrast Enable\n");
	printf("      ^Cinematic Tint Enable\n");
	printf("     ^Cinematic Brightness Enable\n");
	n = buffer_read_byte(b);
	printf("%i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
      }
#endif
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of IMGS\n");

  return -1;
}
