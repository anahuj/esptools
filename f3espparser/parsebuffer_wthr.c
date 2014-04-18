
int parsebuffer_wthr(void *b)
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
    if (strcmp(&(s[1]),"IAD") == 0) {
      printf("Chunk name: %.2iIAD\n",(int)(s[0]));
    } else {
      printf("Chunk name: %s\n",s);
    }
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("WTHR/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"CNAM") == 0) {
      n = buffer_read_short(b);
      printf("WTHR/CNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Cloud Textures Layer 1 \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DNAM") == 0) {
      n = buffer_read_short(b);
      printf("WTHR/DNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Cloud Textures Layer 0 \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"NAM0") == 0) {
      n = buffer_read_short(b);
      printf("WTHR/NAM0 %i\n",n);
      m = n/4;
      for (i = 0; i < m; i++) {
	printf("Type-Time %i:\n",i+1);
	n = buffer_read_ubyte(b);
	printf("Color R %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Color G %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Color B %i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
      }
    } else if (strcmp(s,"FNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WTHR/FNAM %i\n",n);
      f = buffer_read_float(b);
      printf("Fog Distance/Day/Near %f\n",f);
      f = buffer_read_float(b);
      printf("Fog Distance/Day/Far %f\n",f);
      f = buffer_read_float(b);
      printf("Fog Distance/Night/Near %f\n",f);
      f = buffer_read_float(b);
      printf("Fog Distance/Night/Far %f\n",f);
      f = buffer_read_float(b);
      printf("Fog Distance/Day/Pow %f\n",f);
      f = buffer_read_float(b);
      printf("Fog Distance/Night/Pow %f\n",f);
    } else if (strcmp(s,"HNAM") == 0) {
      n = buffer_read_short(b);
      printf("WTHR/HNAM %i\n",n);
      f = buffer_read_float(b);
      printf("Eye Adapt Speed %f\n",f);
      f = buffer_read_float(b);
      printf("Blur Radius %f\n",f);
      f = buffer_read_float(b);
      printf("Blur Passes %f\n",f);
      f = buffer_read_float(b);
      printf("Emissive Mult %f\n",f);
      f = buffer_read_float(b);
      printf("Target LUM %f\n",f);
      f = buffer_read_float(b);
      printf("Upper LUM Clamp %f\n",f);
      f = buffer_read_float(b);
      printf("Bright Scale %f\n",f);
      f = buffer_read_float(b);
      printf("Bright Clamp %f\n",f);
      f = buffer_read_float(b);
      printf("LUM Ramp No Tex %f\n",f);
      f = buffer_read_float(b);
      printf("LUM Ramp Min %f\n",f);
      f = buffer_read_float(b);
      printf("LUM Ramp Max %f\n",f);
      f = buffer_read_float(b);
      printf("Sunlight Dimmer %f\n",f);
      f = buffer_read_float(b);
      printf("Grass Dimmer %f\n",f);
      f = buffer_read_float(b);
      printf("Tree Dimmer %f\n",f);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("WTHR/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Precipitation Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("WTHR/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
#if 0
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("WTHR/MODT %i\n",n);
      parse_modt(b);
#endif
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("WTHR/DATA %i\n",n);
#if 1
      n = buffer_read_ubyte(b);
      printf("Wind Speed %i (%i/255.0 = %f)\n",n,n,(float)n/255.0);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("Trans Delta %i (0.01 + 0.24*%i/255.0 = %f)\n",n,n,0.01 + 0.24*(float)n/255.0);
      n = buffer_read_ubyte(b);
      printf("Sun Glare %i (%i/255.0 = %f)\n",n,n,(float)n/255.0);
      n = buffer_read_ubyte(b);
      printf("Sun Damage %i (%i/255.0 = %f)\n",n,n,(float)n/255.0);
      n = buffer_read_ubyte(b);
      printf("Precip/Begin Fade In %i (%i/255.0 = %f)\n",n,n,(float)n/255.0);
      n = buffer_read_ubyte(b);
      printf("Precip/End Fade Out %i (%i/255.0 = %f)\n",n,n,(float)n/255.0);
      n = buffer_read_ubyte(b);
      printf("ThunderLightning/Begin Fade In %i (%i/255.0 = %f)\n",n,n,(float)n/255.0);
      n = buffer_read_ubyte(b);
      printf("ThunderLightning/End Fade Out %i (%i/255.0 = %f)\n",n,n,(float)n/255.0);
      n = buffer_read_ubyte(b);
      printf("Frequency %i (0 = High, 255 = Low)\n",n);
      n = buffer_read_ubyte(b);
      printf("Weather Class:\n");
      printflags8(n);
      //      0000,0000
      printf("        ^Pleasant\n");
      printf("       ^Cloudy\n");
      printf("      ^Rainy\n");
      printf("     ^Snow\n");
      printf("     ^^^^0 = None\n");
      n = buffer_read_ubyte(b);
      printf("Lightning Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Lightning Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Lightning Color B %i\n",n);
#else
      n = buffer_read_ubyte(b);
      printf("Wind Speed %i (%i/255.0 = %f)\n",n,n,(float)n/255.0);
      n = buffer_read_ubyte(b);
      printf("Cloud Speed Lower %i (%i/2550.0 = %f)\n",n,n,(float)n/2550.0);
      n = buffer_read_ubyte(b);
      printf("Cloud Speed Upper %i (%i/2550.0 = %f)\n",n,n,(float)n/2550.0);
      n = buffer_read_ubyte(b);
      printf("Trans Delta %i (0.01 + %i/260.0 = %f)\n",n,n,0.01 + (float)n/260.0);
      n = buffer_read_ubyte(b);
      printf("Sun Glare %i (%i/255.0 = %f)\n",n,n,(float)n/255.0);
      n = buffer_read_ubyte(b);
      printf("Sun Damage %i (%i/255.0 = %f)\n",n,n,(float)n/255.0);
      n = buffer_read_ubyte(b);
      printf("Precipitation/Begin Fade In %i (%i/255.0 = %f)\n",n,n,(float)n/255.0);
      n = buffer_read_ubyte(b);
      printf("Precipitation/End Fade Out %i (%i/255.0 = %f)\n",n,n,(float)n/255.0);
      n = buffer_read_ubyte(b);
      printf("ThunderLightning/Begin Fade In %i (%i/255.0 = %f)\n",n,n,(float)n/255.0);
      n = buffer_read_ubyte(b);
      printf("ThunderLightning/End Fade Out %i (%i/255.0 = %f)\n",n,n,(float)n/255.0);
      n = buffer_read_ubyte(b);
      printf("Frequency %i (0 = High, 255 = Low)\n",n);
      n = buffer_read_ubyte(b);
      printf("Wheather Class ");
      printflags8(n);
      //      0000,0000
      printf("        ^Pleasant\n");
      printf("       ^Cloudy\n");
      printf("      ^Rainy\n");
      printf("     ^Snow\n");
      printf(" ^????\n");
      printf("^????\n");
      printf("     ^^^^0 = None\n");
      n = buffer_read_ubyte(b);
      printf("Lightning Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Lightning Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Lightning Color B %i\n",n);
#endif
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_short(b);
      printf("WTHR/SNAM %i\n",n);
      m = n/8;
      for (i = 0; i < m; i++) {
	n = buffer_read_int(b);
	printf("Sound FormID %i\n",n);
	n = buffer_read_int(b);
	printf("Sound Type %i %% 0 Default 1 Precip 2 Wind 3 Thunder\n",n);
      }
    } else if (strcmp(s,"\000IAD") == 0) { // F
      n = buffer_read_short(b);
      printf("WTHR/0IAD %i\n",n);
      n = buffer_read_int(b);
      printf("Sunrise ImageSpace Modifier FormID %i\n",n);
    } else if (strcmp(s,"\001IAD") == 0) { // F
      n = buffer_read_short(b);
      printf("WTHR/1IAD %i\n",n);
      n = buffer_read_int(b);
      printf("Day ImageSpace Modifier FormID %i\n",n);
    } else if (strcmp(s,"\002IAD") == 0) { // F
      n = buffer_read_short(b);
      printf("WTHR/2IAD %i\n",n);
      n = buffer_read_int(b);
      printf("Sunset ImageSpace Modifier FormID %i\n",n);
    } else if (strcmp(s,"\003IAD") == 0) { // F
      n = buffer_read_short(b);
      printf("WTHR/3IAD %i\n",n);
      n = buffer_read_int(b);
      printf("Night ImageSpace Modifier FormID %i\n",n);
    } else if (strcmp(s,"ANAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WTHR/ANAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Cloud Textures Layer 2 \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"BNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WTHR/BNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Cloud Textures Layer 3 \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"LNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WTHR/LNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Number of cloud texture layers %i ????\n",n);
    } else if (strcmp(s,"ONAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WTHR/ONAM %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Cloud Speed Layer 0 %i %% Editor shows %f\n",n,0.1*(float)n/255.0);
      n = buffer_read_ubyte(b);
      printf("Cloud Speed Layer 1 %i %% Editor shows %f\n",n,0.1*(float)n/255.0);
      n = buffer_read_ubyte(b);
      printf("Cloud Speed Layer 2 %i %% Editor shows %f\n",n,0.1*(float)n/255.0);
      n = buffer_read_ubyte(b);
      printf("Cloud Speed Layer 3 %i %% Editor shows %f\n",n,0.1*(float)n/255.0);
    } else if (strcmp(s,"PNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WTHR/PNAM %i\n",n);
      size = n;
      // colors
      for (i = 0; i < size/4; i++) {
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
      }
    } else if (strcmp(s,"INAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WTHR/INAM %i\n",n);
      size = n;
      for (i = 0; i < 32; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
      for (i = 0; i < 176; i++) {
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
      }
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of WTHR\n");

  return -1;
}
