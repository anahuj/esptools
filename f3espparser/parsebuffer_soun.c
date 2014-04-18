
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
    } else if (strcmp(s,"SNDD") == 0) { // F
      n = buffer_read_short(b);
      printf("SOUN/SNDD %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Minimum Attenuation Distance %i (%i) %% 0 Default\n",n,5*n);
      n = buffer_read_ubyte(b);
      printf("Maximum Attenuation Distance %i (%i) %% 0 Default\n",n,100*n);
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
      printf("                            ^Dialogue Sound\n");
      printf("                           ^Envelope Fast\n");
      printf("                          ^Envelope Slow\n");
      printf("                         ^2D Radius\n");
      printf("                       ^Mute When Submerged\n");
      n = buffer_read_short(b);
      printf("Static Attenuation %i (%f dB)\n",n,-(float)n/100.0);
      n = buffer_read_ubyte(b);
      printf("Ends at %i (%.2i:%.2i)\n",n,(1440*n/256)/60,(1440*n/256)%60);
      n = buffer_read_ubyte(b);
      printf("Starts at %i (%.2i:%.2i)\n",n,(1440*n/256)/60,(1440*n/256)%60);
      n = buffer_read_short(b);
      printf("Attenuation Curve 1: %i\n",n);
      n = buffer_read_short(b);
      printf("Attenuation Curve 2: %i\n",n);
      n = buffer_read_short(b);
      printf("Attenuation Curve 3: %i\n",n);
      n = buffer_read_short(b);
      printf("Attenuation Curve 4: %i\n",n);
      n = buffer_read_short(b);
      printf("Attenuation Curve 5: %i\n",n);
      n = buffer_read_short(b);
      printf("Reverb Attenuation Control %i %% 0 Min 100 Max\n",n);
      n = buffer_read_int(b);
      printf("Priority %i %% 1 Min 255 Max\n",n);
      n = buffer_read_int(b);
      printf("Loop Points Begin %i\n",n);
      n = buffer_read_int(b);
      printf("Loop Points End %i\n",n);
    } else if (strcmp(s,"SNDX") == 0) {
      n = buffer_read_short(b);
      printf("SOUN/SNDX %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Minimum Attenuation Distance %i (%i) %% 0 Default\n",n,5*n);
      n = buffer_read_ubyte(b);
      printf("Maximum Attenuation Distance %i (%i) %% 0 Default\n",n,100*n);
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
      printf("                            ^Dialogue Sound\n");
      printf("                           ^Envelope Fast\n");
      printf("                         ^2D Radius\n");
      printf("                       ^Mute When Submerged\n");
      n = buffer_read_short(b);
      printf("Static Attenuation %i (%f dB)\n",n,-(float)n/100.0);
      n = buffer_read_ubyte(b);
      printf("Ends at %i (%.2i:%.2i)\n",n,(1440*n/256)/60,(1440*n/256)%60);
      n = buffer_read_ubyte(b);
      printf("Starts at %i (%.2i:%.2i)\n",n,(1440*n/256)/60,(1440*n/256)%60);
    } else if (strcmp(s,"OBND") == 0) { // F
      n = buffer_read_short(b);
      printf("SOUN/OBND %i\n",n);
      parse_obnd(b);
    } else if (strcmp(s,"ANAM") == 0) { // F
      n = buffer_read_short(b);
      printf("SOUN/ANAM %i\n",n);
      n = buffer_read_short(b);
      printf("%i\n",n);
      n = buffer_read_short(b);
      printf("%i\n",n);
      n = buffer_read_short(b);
      printf("%i\n",n);
      n = buffer_read_short(b);
      printf("%i\n",n);
      n = buffer_read_short(b);
      printf("%i\n",n);
    } else if (strcmp(s,"GNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("SOUN/GNAM %i\n",n);
      n = buffer_read_short(b);
      printf("%i\n",n);
    } else if (strcmp(s,"HNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("SOUN/HNAM %i\n",n);
      n = buffer_read_short(b);
      printf("%i\n",n);
      n = buffer_read_short(b);
      printf("%i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of SOUN\n");

  return -1;
}
