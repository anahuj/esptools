
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
      } else if (size == 42) {
	f = buffer_read_float(b);
	printf("Wind Velocity %f\n",f);
	f = buffer_read_float(b);
	printf("Wind Direction %f\n",f);
	f = buffer_read_float(b);
	printf("Wave Amplitude %f\n",f);
	f = buffer_read_float(b);
	printf("Wave Frequency %f\n",f);
	f = buffer_read_float(b);
	printf("Sun Power %f\n",f);
	f = buffer_read_float(b);
	printf("Reflectivity Amount %f\n",f);
	f = buffer_read_float(b);
	printf("Fresnel Amount %f\n",f);
	n = buffer_read_int(b);
	printf("%i\n",n);
	n = buffer_read_int(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
      } else if (size == 62) {
	f = buffer_read_float(b);
	printf("Wind Velocity %f\n",f);
	f = buffer_read_float(b);
	printf("Wind Direction %f\n",f);
	f = buffer_read_float(b);
	printf("Wave Amplitude %f\n",f);
	f = buffer_read_float(b);
	printf("Wave Frequency %f\n",f);
	f = buffer_read_float(b);
	printf("Sun Power %f\n",f);
	f = buffer_read_float(b);
	printf("Reflectivity Amount %f\n",f);
	f = buffer_read_float(b);
	printf("Fresnel Amount %f\n",f);
	f = buffer_read_float(b);
	printf("Scroll X Speed %f\n",f);
	f = buffer_read_float(b);
	printf("Scroll Y Speed %f\n",f);
	f = buffer_read_float(b);
	printf("Fog Distance - Near Plane %f\n",f);
	f = buffer_read_float(b);
	printf("Fog Distance - Far Plane %f\n",f);
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
	printf("Texture Blend %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Texture Blend Color R (from the texture image) %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Texture Blend Color G (from the texture image) %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Texture Blend Color B (from the texture image) %i\n",n);
	n = buffer_read_short(b);
	printf("Damage per second %i\n",n);
      } else if (size == 86) {
	f = buffer_read_float(b);
	printf("Wind Velocity %f\n",f);
	f = buffer_read_float(b);
	printf("Wind Direction %f\n",f);
	f = buffer_read_float(b);
	printf("Wave Amplitude %f\n",f);
	f = buffer_read_float(b);
	printf("Wave Frequency %f\n",f);
	f = buffer_read_float(b);
	printf("Sun Power %f\n",f);
	f = buffer_read_float(b);
	printf("Reflectivity Amount %f\n",f);
	f = buffer_read_float(b);
	printf("Fresnel Amount %f\n",f);
	f = buffer_read_float(b);
	printf("Scroll X Speed %f\n",f);
	f = buffer_read_float(b);
	printf("Scroll Y Speed %f\n",f);
	f = buffer_read_float(b);
	printf("Fog Distance - Near Plane %f\n",f);
	f = buffer_read_float(b);
	printf("Fog Distance - Far Plane %f\n",f);
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
	printf("Texture Blend %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Texture Blend Color R (from the texture image) %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Texture Blend Color G (from the texture image) %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Texture Blend Color B (from the texture image) %i\n",n);
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
	n = buffer_read_short(b);
	printf("Damage per second %i\n",n);
      } else if (size == 102) {
	f = buffer_read_float(b);
	printf("Wind Velocity %f\n",f);
	f = buffer_read_float(b);
	printf("Wind Direction %f\n",f);
	f = buffer_read_float(b);
	printf("Wave Amplitude %f\n",f);
	f = buffer_read_float(b);
	printf("Wave Frequency %f\n",f);
	f = buffer_read_float(b);
	printf("Sun Power %f\n",f);
	f = buffer_read_float(b);
	printf("Reflectivity Amount %f\n",f);
	f = buffer_read_float(b);
	printf("Fresnel Amount %f\n",f);
	f = buffer_read_float(b);
	printf("Scroll X Speed %f\n",f);
	f = buffer_read_float(b);
	printf("Scroll Y Speed %f\n",f);
	f = buffer_read_float(b);
	printf("Fog Distance - Near Plane %f\n",f);
	f = buffer_read_float(b);
	printf("Fog Distance - Far Plane %f\n",f);
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
	printf("Texture Blend %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Texture Blend Color R (from the texture image) %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Texture Blend Color G (from the texture image) %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Texture Blend Color B (from the texture image) %i\n",n);
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
	n = buffer_read_short(b);
	printf("Damage per second %i\n",n);
      } else {
	printf("Unknown water data size %i\n",size);
	buffer_skip_bytes(b,size);
      }
    } else if (strcmp(s,"GNAM") == 0) {
      n = buffer_read_short(b);
      printf("WATR/GNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Daytime FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Nighttime FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Underwater FormID %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of WATR\n");

  return -1;
}