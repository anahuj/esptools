
int parsebuffer_watr(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int size;
  int loc1;
  int loc2;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("WATR/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) { // F
      n = buffer_read_short(b);
      printf("WATR/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"TNAM") == 0) {
      n = buffer_read_short(b);
      printf("WATR/TNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Texture image \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ANAM") == 0) {
      n = buffer_read_short(b);
      printf("WATR/ANAM %i\n",n);
      n = buffer_read_byte(b);
      printf("Opacity %i\n",n);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_short(b);
      printf("WATR/FNAM %i\n",n);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Causes Damage\n");
      printf("       ^Reflective\n");
    } else if (strcmp(s,"MNAM") == 0) {
      n = buffer_read_short(b);
      printf("WATR/MNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Material ID \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_short(b);
      printf("WATR/SNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Sound FormID %i\n",n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("WATR/DATA %i\n",n);
      size = n;
      if (size == 2) {
	n = buffer_read_short(b);
	printf("%i\n",n);
      } else {
      loc1 = buffer_getloc(b);
      f = buffer_read_float(b);
      printf("XX Wind Velocity %f\n",f); // 1
      f = buffer_read_float(b);
      printf("Wind Direction %f\n",f); // 2
      f = buffer_read_float(b);
      printf("XX Wave Amplitude %f\n",f); // 3
      f = buffer_read_float(b);
      printf("XX Wave Frequency %f\n",f); // 4
      f = buffer_read_float(b);
      printf("Sun Power %f\n",f); // 5
      f = buffer_read_float(b);
      printf("Reflectivity Amount %f\n",f); // 6
      f = buffer_read_float(b);
      printf("Fresnel Amount %f\n",f); // 7
      f = buffer_read_float(b);
      printf("XX Scroll X Speed %f\n",f); // 8
#if 0
      f = buffer_read_float(b);
      printf("Scroll Y Speed %f\n",f); // 9
#endif
      f = buffer_read_float(b);
      printf("Fog Distance Near Plane (Above Water) %f\n",f); // 10
      f = buffer_read_float(b);
      printf("Fog Distance Far Plane (Above Water) %f\n",f);
      n = buffer_read_ubyte(b);
      printf("Shallow Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Shallow Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Shallow Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("Deep Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Deep Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Deep Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("Reflection Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Reflection Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Reflection Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("XX Texture Blend %i\n",n);
      n = buffer_read_ubyte(b);
      printf("XX Texture Blend Color R (from the texture image) %i\n",n);
      n = buffer_read_ubyte(b);
      printf("XX Texture Blend Color G (from the texture image) %i\n",n);
      n = buffer_read_ubyte(b);
      printf("XX Texture Blend Color B (from the texture image) %i\n",n);
      f = buffer_read_float(b);
      printf("RainSim/Force %f\n",f);
      f = buffer_read_float(b);
      printf("RainSim/Velocity %f\n",f);
      f = buffer_read_float(b);
      printf("RainSim/Falloff %f\n",f);
      f = buffer_read_float(b);
      printf("RainSim/Dampner %f\n",f);
      f = buffer_read_float(b);
      printf("RainSim/Starting Size %f\n",f);
      f = buffer_read_float(b);
      printf("DispSim/Force %f\n",f);
      f = buffer_read_float(b);
      printf("DispSim/Velocity %f\n",f);
      f = buffer_read_float(b);
      printf("DispSim/Falloff %f\n",f);
      f = buffer_read_float(b);
      printf("DispSim/Dampner %f\n",f);
      f = buffer_read_float(b);
      printf("DispSim/Starting Size %f\n",f);
#if 0
      n = buffer_read_short(b);
      printf("Damage per second %i\n",n);
#endif
      f = buffer_read_float(b);
      printf("Noise Scale %f\n",f);
      f = buffer_read_float(b);
      printf("Wind Direction %f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("Wind Speed %f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      n = buffer_read_int(b);
      printf("%i\n",n);
      f = buffer_read_float(b);
      printf("Depth Falloff End %f\n",f);
      f = buffer_read_float(b);
      printf("Fog Amount (Above Water) %f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("Fog Amount (Under Water) %f\n",f);
      f = buffer_read_float(b);
      printf("Fog Distance Near Plane (Under Water) %f\n",f);
      f = buffer_read_float(b);
      printf("Fog Distance Far Plane (Under Water) %f\n",f);
      f = buffer_read_float(b);
      printf("Distortion Amount %f\n",f);
      f = buffer_read_float(b);
      printf("Shininess %f\n",f);
      f = buffer_read_float(b);
      printf("Reflection HDR Multiplier %f\n",f);
      f = buffer_read_float(b);
      printf("Light Radius %f\n",f);
      f = buffer_read_float(b);
      printf("Light Brightness %f\n",f);
      f = buffer_read_float(b);
      printf("UV Scale %f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      n = buffer_read_short(b);
      printf("%i\n",n);
#if 1
      loc2 = buffer_getloc(b);
      buffer_skip_bytes(b,size-(loc2-loc1));
      printf("Skipping %i bytes\n",size-(loc2-loc1));
#endif
#if 0
      if (size >= 196) {
	f = buffer_read_float(b);
	printf("Amplitude Scale %f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
#endif
#if 0
	printf("Unknown water data size %i\n",size);
	buffer_skip_bytes(b,size);
#endif
      }
    } else if (strcmp(s,"DNAM") == 0) { // F  DATA moved here?
      n = buffer_read_short(b);
      printf("WATR/DNAM %i\n",n);
      size = n;
      // Oblivion size divisions:
      // if (size >= 42) {
      // if (size >= 62) {
      // if (size >= 86) {
      // if (size >= 102) {
      loc1 = buffer_getloc(b);
      f = buffer_read_float(b);
      printf("XX Wind Velocity %f\n",f); // 1
      f = buffer_read_float(b);
      printf("Wind Direction %f\n",f); // 2
      f = buffer_read_float(b);
      printf("XX Wave Amplitude %f\n",f); // 3
      f = buffer_read_float(b);
      printf("XX Wave Frequency %f\n",f); // 4
      f = buffer_read_float(b);
      printf("Sun Power %f\n",f); // 5
      f = buffer_read_float(b);
      printf("Reflectivity Amount %f\n",f); // 6
      f = buffer_read_float(b);
      printf("Fresnel Amount %f\n",f); // 7
      f = buffer_read_float(b);
      printf("XX Scroll X Speed %f\n",f); // 8
#if 0
      f = buffer_read_float(b);
      printf("Scroll Y Speed %f\n",f); // 9
#endif
      f = buffer_read_float(b);
      printf("Fog Distance Near Plane (Above Water) %f\n",f); // 10
      f = buffer_read_float(b);
      printf("Fog Distance Far Plane (Above Water) %f\n",f);
      n = buffer_read_ubyte(b);
      printf("Shallow Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Shallow Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Shallow Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("Deep Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Deep Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Deep Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("Reflection Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Reflection Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Reflection Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("XX Texture Blend %i\n",n);
      n = buffer_read_ubyte(b);
      printf("XX Texture Blend Color R (from the texture image) %i\n",n);
      n = buffer_read_ubyte(b);
      printf("XX Texture Blend Color G (from the texture image) %i\n",n);
      n = buffer_read_ubyte(b);
      printf("XX Texture Blend Color B (from the texture image) %i\n",n);
      f = buffer_read_float(b);
      printf("RainSim/Force %f\n",f);
      f = buffer_read_float(b);
      printf("RainSim/Velocity %f\n",f);
      f = buffer_read_float(b);
      printf("RainSim/Falloff %f\n",f);
      f = buffer_read_float(b);
      printf("RainSim/Dampner %f\n",f);
      f = buffer_read_float(b);
      printf("RainSim/Starting Size %f\n",f);
      f = buffer_read_float(b);
      printf("DispSim/Force %f\n",f);
      f = buffer_read_float(b);
      printf("DispSim/Velocity %f\n",f);
      f = buffer_read_float(b);
      printf("DispSim/Falloff %f\n",f);
      f = buffer_read_float(b);
      printf("DispSim/Dampner %f\n",f);
      f = buffer_read_float(b);
      printf("DispSim/Starting Size %f\n",f);
#if 0
      n = buffer_read_short(b);
      printf("Damage per second %i\n",n);
#endif
      f = buffer_read_float(b);
      printf("Noise Scale %f\n",f);
      f = buffer_read_float(b);
      printf("Wind Direction %f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("Wind Speed %f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      n = buffer_read_int(b);
      printf("%i\n",n);
      f = buffer_read_float(b);
      printf("Depth Falloff End %f\n",f);
      f = buffer_read_float(b);
      printf("Fog Amount (Above Water) %f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("Fog Amount (Under Water) %f\n",f);
      f = buffer_read_float(b);
      printf("Fog Distance Near Plane (Under Water) %f\n",f);
      f = buffer_read_float(b);
      printf("Fog Distance Far Plane (Under Water) %f\n",f);
      f = buffer_read_float(b);
      printf("Distortion Amount %f\n",f);
      f = buffer_read_float(b);
      printf("Shininess %f\n",f);
      f = buffer_read_float(b);
      printf("Reflection HDR Multiplier %f\n",f);
      f = buffer_read_float(b);
      printf("Light Radius %f\n",f);
      f = buffer_read_float(b);
      printf("Light Brightness %f\n",f);
      f = buffer_read_float(b);
      printf("UV Scale %f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      if (size >= 196) {
	f = buffer_read_float(b);
	printf("Amplitude Scale %f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
#if 1
      loc2 = buffer_getloc(b);
      buffer_skip_bytes(b,size-(loc2-loc1));
      printf("Skipping %i bytes\n",size-(loc2-loc1));
#endif
    } else if (strcmp(s,"GNAM") == 0) {
      n = buffer_read_short(b);
      printf("WATR/GNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Daytime FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Nighttime FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Underwater FormID %i\n",n);
    } else if (strcmp(s,"NNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WATR/NNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Noise texture \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"XNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WATR/XNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Effect FormID %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of WATR\n");

  return -1;
}
