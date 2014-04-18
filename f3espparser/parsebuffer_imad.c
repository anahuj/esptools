
typedef struct {
  char *recordname;
  char *editorname;
  int numvalues;
} ty_imad_param;

ty_imad_param global_imad_curve_names[100] = {
  "00IAD", "HDR Eye Adapt Speed Mult", 1,
  "01IAD", "HDR Blur Radius Mult", 1,
  "02IAD", "HDR Skin Dimmer Mult", 1,
  "03IAD", "HDR Emissive Mult Mult", 1,
  "04IAD", "HDR Target LUM Mult", 1,
  "05IAD", "HDR Upper LUM Clamp Mult", 1,
  "06IAD", "HDR Bright Scale Mult", 1,
  "07IAD", "HDR Bright Clamp Mult", 1,
  "08IAD", "HDR LUM Ramp No Tex Mult", 1,
  "09IAD", "HDR LUM Ramp Min Mult", 1,
  "10IAD", "HDR LUM Ramp Max Mult", 1,
  "11IAD", "HDR Sunlight Dimmer Mult", 1,
  "12IAD", "HDR Grass Dimmer Mult", 1,
  "13IAD", "HDR Tree Dimmer Mult", 1,
  "14IAD", "Bloom Blur Radius Mult", 1,
  "15IAD", "Bloom Alpha Mult Interior Mult", 1,
  "16IAD", "Bloom Alpha Mult Exterior Mult", 1,
  "17IAD", "Cinematic Saturation Mult", 1,
  "18IAD", "Cinematic Contrast Mult", 1,
  "19IAD", "Cinematic Contrast Avg Lum Mult", 1,
  "20IAD", "Cinematic Brightness Mult", 1,
  "64IAD", "HDR Eye Adapt Speed Add", 1,
  "65IAD", "HDR Blur Radius Add", 1,
  "66IAD", "HDR Skin Dimmer Add", 1,
  "67IAD", "HDR Emissive Mult Add", 1,
  "68IAD", "HDR Target LUM Add", 1,
  "69IAD", "HDR Upper LUM Clamp Add", 1,
  "70IAD", "HDR Bright Scale Add", 1,
  "71IAD", "HDR Bright Clamp Add", 1,
  "72IAD", "HDR LUM Ramp No Tex Add", 1,
  "73IAD", "HDR LUM Ramp Min Add", 1,
  "74IAD", "HDR LUM Ramp Max Add", 1,
  "75IAD", "HDR Sunlight Dimmer Add", 1,
  "76IAD", "HDR Grass Dimmer Add", 1,
  "77IAD", "HDR Tree Dimmer Add", 1,
  "78IAD", "Bloom Blur Radius Add", 1,
  "79IAD", "Bloom Alpha Mult Interior Add", 1,
  "80IAD", "Bloom Alpha Mult Exterior Add", 1,
  "81IAD", "Cinematic Saturation Add", 1,
  "82IAD", "Cinematic Contrast Add", 1,
  "83IAD", "Cinematic Contrast Avg Lum Add", 1,
  "84IAD", "Cinematic Brightness Add", 1,
  "BNAM", "Blur Radius", 1,
  "NAM1", "Radial Blur Rampdown", 1,
  "NAM2", "Radial Blur DownStart", 1,
  "NAM3", "Cinematic Fade Color", 4, // RGBA color
  "NAM4", "FullScreen Motion Blur Strength", 1,
  "RNAM", "Radial Blur Str", 1,
  "SNAM", "Radial Blur Rampup", 1,
  "TNAM", "Cinematic Tint Color", 4, // RGBA color
  "UNAM", "Radial Blur Start", 1,
  "VNAM", "Double Vision Strength", 1,
  "WNAM", "Depth Of Field Strength", 1,
  "XNAM", "Depth Of Field Distance", 1,
  "YNAM", "Depth Of Field Range", 1,
  "END", "END", -1,
};


int parsebuffer_imad(void *b)
{
  int n;
  int i;
  int j;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int size;
  int num;
  int numvals;
  char recname[6];

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    if (strcmp(&(s[1]),"IAD") == 0) {
      printf("Chunk name: %.2iIAD\n",(int)(s[0]));
      sprintf(recname,"%.2iIAD",(int)(s[0]));
    } else {
      printf("Chunk name: %s\n",s);
      sprintf(recname,"%s",s);
    }
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("IMAD/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"DNAM") == 0) {
      n = buffer_read_short(b);
      printf("IMAD/DNAM %i\n",n);
      size = n;
#if 0
      num = size/4;
      for (i = 0; i < num; i++) {
	n = buffer_read_int(b);
	printf("%i\n",n);
      }
#else
      if (size >= 188) {
	n = buffer_read_int(b);
	printf("Animatable %i %% 0 Disabled 1 Enabled\n",n);
	f = buffer_read_float(b);
	printf("Duration %f\n",f);
	n = buffer_read_int(b);
	printf("Animation keys for HDR Eye Adapt Speed Mult %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR Eye Adapt Speed Add %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR Blur Radius Mult %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR Blur Radius Add %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR Skin Dimmer Mult %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR Skin Dimmer Add %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR Emissive Mult Mult %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR Emissive Mult Add %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR Target LUM Mult %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR Target LUM Add %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR Upper LUM Clamp Mult %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR Upper LUM Clamp Add %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR Bright Scale Mult %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR Bright Scale Add %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR Bright Clamp Mult %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR Bright Clamp Add %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR LUM Ramp No Tex Mult %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR LUM Ramp No Tex Add %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR LUM Ramp Min Mult %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR LUM Ramp Min Add %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR LUM Ramp Max Mult %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR LUM Ramp Max Add %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR Sunlight Dimmer Mult %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR Sunlight Dimmer Add %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR Grass Dimmer Mult %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR Grass Dimmer Add %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR Tree Dimmer Mult %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for HDR Tree Dimmer Add %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for Bloom Blur Radius Mult %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for Bloom Blur Radius Add %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for Bloom Alpha Mult Interior Mult %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for Bloom Alpha Mult Interior Add %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for Bloom Alpha Mult Exterior Mult %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for Bloom Alpha Mult Exterior Add %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for Cinematic Saturation Mult %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for Cinematic Saturation Add %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for Cinematic Contrast Mult %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for Cinematic Contrast Add %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for Cinematic Contrast Avg Lum Mult %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for Cinematic Contrast Avg Lum Add %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for Cinematic Brightness Mult %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for Cinematic Brightness Add %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for Cinematic Tint Color %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for Blur Radius %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for Double Vision Strength %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for Radial Blur Str %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for Radial Blur Rampup %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for Radial Blur Start %i\n",n);
	n = buffer_read_int(b);
	printf("Radial Blur Use Target %i %% 0 Disabled 1 Enabled\n",n);
	f = buffer_read_float(b);
	printf("Radial Blur Center X %f\n",f);
	f = buffer_read_float(b);
	printf("Radial Blur Center Y %f\n",f);
	n = buffer_read_int(b);
	printf("Animation keys for Depth Of Field Strength %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for Depth Of Field Distance %i\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for Depth Of Field Range %i\n",n);
	n = buffer_read_byte(b);
	printf("Depth Of Field Use Target %i %% 0 Disabled 1 Enabled\n",n);
	n = buffer_read_byte(b);
	printf("Depth Of Field Mode %i %% 0 Front/Back 1 Front 2 Back\n",n);
	n = buffer_read_byte(b);
	printf("%i (unused)\n",n);
	n = buffer_read_byte(b);
	printf("%i (unused)\n",n);
	n = buffer_read_int(b);
	printf("Animation keys for Radial Blur Rampdown %i\n",n);
      }
      if (size >= 236) {
	n = buffer_read_int(b);
	printf("Animation keys for Radial Blur DownStart %i\n",n);
      }
      if (size >= 240) {
	n = buffer_read_int(b);
	printf("Animation keys for Cinematic Fade Color %i\n",n);
      }
      if (size >= 244) {
	n = buffer_read_int(b);
	printf("Animation keys for FullScreen Motion Blur Strength %i\n",n);
      }
#endif
#if 0
    } else if (strcmp(s,"BNAM") == 0) {
      n = buffer_read_short(b);
      printf("IMAD/BNAM %i\n",n);
      size = n;
      num = size/4;
      for (i = 0; i < num; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"VNAM") == 0) {
      n = buffer_read_short(b);
      printf("IMAD/VNAM %i\n",n);
      size = n;
      num = size/4;
      for (i = 0; i < num; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"TNAM") == 0) {
      n = buffer_read_short(b);
      printf("IMAD/TNAM %i\n",n);
      size = n;
      num = size/4/5;
      for (i = 0; i < num; i++) {
	f = buffer_read_float(b);
	printf("Time %f\n",f);
	f = buffer_read_float(b);
	printf("Cinematic Tint Color R %f\n",f);
	f = buffer_read_float(b);
	printf("Cinematic Tint Color G %f\n",f);
	f = buffer_read_float(b);
	printf("Cinematic Tint Color B %f\n",f);
	f = buffer_read_float(b);
	printf("Cinematic Tint Color A %f\n",f);
      }
    } else if (strcmp(s,"NAM3") == 0) {
      n = buffer_read_short(b);
      printf("IMAD/NAM3 %i\n",n);
      size = n;
      num = size/4/5;
      for (i = 0; i < num; i++) {
	f = buffer_read_float(b);
	printf("Time %f\n",f);
	f = buffer_read_float(b);
	printf("Cinematic Fade Color R %f\n",f);
	f = buffer_read_float(b);
	printf("Cinematic Fade Color G %f\n",f);
	f = buffer_read_float(b);
	printf("Cinematic Fade Color B %f\n",f);
	f = buffer_read_float(b);
	printf("Cinematic Fade Color A %f\n",f);
      }
    } else if (strcmp(s,"RNAM") == 0) {
      n = buffer_read_short(b);
      printf("IMAD/RNAM %i\n",n);
      size = n;
      num = size/4;
      for (i = 0; i < num; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_short(b);
      printf("IMAD/SNAM %i\n",n);
      size = n;
      num = size/4;
      for (i = 0; i < num; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"UNAM") == 0) {
      n = buffer_read_short(b);
      printf("IMAD/UNAM %i\n",n);
      size = n;
      num = size/4;
      for (i = 0; i < num; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"NAM1") == 0) {
      n = buffer_read_short(b);
      printf("IMAD/NAM1 %i\n",n);
      size = n;
      num = size/4;
      for (i = 0; i < num; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"NAM2") == 0) {
      n = buffer_read_short(b);
      printf("IMAD/NAM2 %i\n",n);
      size = n;
      num = size/4;
      for (i = 0; i < num; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"WNAM") == 0) {
      n = buffer_read_short(b);
      printf("IMAD/WNAM %i\n",n);
      size = n;
      num = size/4;
      for (i = 0; i < num; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"XNAM") == 0) {
      n = buffer_read_short(b);
      printf("IMAD/XNAM %i\n",n);
      size = n;
      num = size/4;
      for (i = 0; i < num; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"YNAM") == 0) {
      n = buffer_read_short(b);
      printf("IMAD/YNAM %i\n",n);
      size = n;
      num = size/4;
      for (i = 0; i < num; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"NAM4") == 0) {
      n = buffer_read_short(b);
      printf("IMAD/NAM4 %i\n",n);
      size = n;
      num = size/4;
      for (i = 0; i < num; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(&(s[1]),"IAD") == 0) {
      n = buffer_read_short(b);
      printf("IMAD/%.2iIAD %i\n",(int)(s[0]),n);
      size = n;
      printf("%s\n",global_imad_curve_names[(int)(s[0])]);
      num = size/4/2;
      for (i = 0; i < num; i++) {
	f = buffer_read_float(b);
	// printf("%f\n",f);
	f2 = buffer_read_float(b);
	printf("%f %f\n",f,f2);
      }
#endif
    } else {
      // Search the subrecord table.
      m = -1;
      for (i = 0; strcmp(global_imad_curve_names[i].recordname,"END") != 0; i++) {
	if (strcmp(global_imad_curve_names[i].recordname,recname) == 0) {
	  m = i;
	  // Exit the loop here. Use "continue"?
	}
      }
      if (m != -1) {
	n = buffer_read_short(b);
	printf("IMAD/%s %i\n",global_imad_curve_names[m].recordname,n);
	size = n;
	printf("%s:\n",global_imad_curve_names[m].editorname);
	numvals = global_imad_curve_names[m].numvalues;
	num = size/4/(1+numvals);
	for (i = 0; i < num; i++) {
	  f = buffer_read_float(b);
	  printf("Time %f Values",f);
	  for (j = 0; j < numvals; j++) {
	    f = buffer_read_float(b);
	    printf(" %f",f);
	  }
	  printf("\n");
	}
      } else {
	printf("Unknown chunk name\n");
	exit(-1);
      }
    }
    free(s);
  }

  printf("End of IMAD\n");

  return -1;
}
