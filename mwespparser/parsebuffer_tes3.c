
int parsebuffer_tes3(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  unsigned char *buf;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    printf("loc = %i\n",loc);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"HEDR") == 0) {
      n = buffer_read_int(b);
      printf("TES3/HEDR %i\n",n);
      m = n;
      f = buffer_read_float(b);
      printf("Version %f\n",f);
      if (fabs(f - 1.2) < 0.001) {
	global_version = 0;
      }
      if (fabs(f - 1.3) < 0.001) {
	global_version = 1;
      }
      n = buffer_read_int(b);
      printf("%i\n",n);
      s2 = buffer_read_nstring(b,32);
      printf("%s\n",s2);
      free(s2);
      s2 = buffer_read_nstring(b,64);
      printf("%s\n",s2);
      free(s2);

      buffer_setloc(b, loc+8 + m-4);
      printf("loc = %i\n",loc+8 + m-4);

      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"MAST") == 0) { // Tribunal.
      n = buffer_read_int(b);
      printf("TES3/MAST %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) { // Tribunal.
      n = buffer_read_int(b);
      printf("TES3/DATA %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"GMDT") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("TES3/GMDT %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      s2 = buffer_read_nstring(b,64);
      printf("%s\n",s2);
      free(s2);
      f = buffer_read_float(b);
      printf("%f\n",f);
      s2 = buffer_read_nstring(b,32);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"SCRD") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("TES3/SCRD %i\n",n);
      printf("Red color mask:\n");
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      printf("Green color mask:\n");
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      printf("Blue color mask:\n");
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i unknown\n",n);
      n = buffer_read_int(b);
      printf("Bits per pixel %i\n",n);
    } else if (strcmp(s,"SCRS") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("TES3/SCRS %i\n",n);
      buf = buffer_getbuf_atloc(b);
      printf("Raw 128x128 saveimage saved to tes3scrs.bgra\n");
      buffer2file(buf,n,"tes3scrs.bgra");
      buffer_skip_bytes(b,n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of TES3\n");

  return -1;
}
