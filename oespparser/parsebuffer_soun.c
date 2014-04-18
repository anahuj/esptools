
int parsebuffer_soun(void *b)
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
      printf("SOUN/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_short(b);
      printf("SOUN/FNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Sound \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SNDD") == 0) {
      n = buffer_read_short(b);
      printf("SOUN/SNDD %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Minimum Attenuation Distance %i (%i)\n",n,5*n);
      n = buffer_read_ubyte(b);
      printf("Maximum Attenuation Distance %i (%i)\n",n,100*n);
      // Might not be correct, even UESP doc says so.
      n = buffer_read_byte(b);
      printf("Frequency Adjustment(%%) %i\n",n);
      n = buffer_read_byte(b); // This has value = 1 in two examples.
      printf("%i\n",n);
      n = buffer_read_uint(b);
      printflags(n);
      //      0000,0000,0000,0000,0000,0000,0000,0000
      printf("                                      ^Random Frequency Shift\n");
      printf("                                     ^Play At Random\n");
      printf("                                    ^Environment Ignored\n");
      printf("                                   ^Random Location\n");
      printf("                                 ^Loop\n");
      printf("                                ^Menu Sound\n");
      printf("                               ^2D\n");
      printf("                              ^360 LFE\n");
    } else if (strcmp(s,"SNDX") == 0) {
      n = buffer_read_short(b);
      printf("SOUN/SNDX %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Minimum Attenuation Distance %i (%i)\n",n,5*n);
      n = buffer_read_ubyte(b);
      printf("Maximum Attenuation Distance %i (%i)\n",n,100*n);
      n = buffer_read_byte(b);
      printf("Frequency Adjustment(%%) %i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_uint(b);
      printflags(n);
      //      0000,0000,0000,0000,0000,0000,0000,0000
      printf("                                      ^Random Frequency Shift\n");
      printf("                                     ^Play At Random\n");
      printf("                                    ^Environment Ignored\n");
      printf("                                   ^Random Location\n");
      printf("                                 ^Loop\n");
      printf("                                ^Menu Sound\n");
      printf("                               ^2D\n");
      printf("                              ^360 LFE\n");
      n = buffer_read_short(b);
      printf("Static Attenuation %i (%f dB)\n",n,-(float)n/100.0);
      n = buffer_read_ubyte(b);
      printf("Ends at %i (%.2i:%.2i)\n",n,(1440*n/256)/60,(1440*n/256)%60);
      n = buffer_read_ubyte(b);
      printf("Starts at %i (%.2i:%.2i)\n",n,(1440*n/256)/60,(1440*n/256)%60);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of SOUN\n");

  return -1;
}
