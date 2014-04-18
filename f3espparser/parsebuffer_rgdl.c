
int parsebuffer_rgdl(void *b)
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
      printf("RGDL/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"ANAM") == 0) {
      n = buffer_read_short(b);
      printf("RGDL/ANAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Pose Matching Pose File \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"NVER") == 0) {
      n = buffer_read_short(b);
      printf("RGDL/NVER %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("RGDL/DATA %i\n",n);
      n = buffer_read_short(b);
      printf("%i\n",n);
      n = buffer_read_short(b);
      printf("Foot IK %i %% 0 Disabled 1 Enabled ????\n",n);
      n = buffer_read_short(b);
      printf("Look IK %i %% ????\n",n);
      n = buffer_read_short(b);
      printf("Grab IK %i %% ????\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_byte(b);
      printf("Foot IK %i %% 0 Disabled 1 Enabled\n",n);
      n = buffer_read_byte(b);
      printf("Look IK %i %% ????\n",n);
      n = buffer_read_byte(b);
      printf("Grab IK %i %% ????\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"TNAM") == 0) {
      n = buffer_read_short(b);
      printf("RGDL/TNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Body Part Data FormID %i\n",n);
    } else if (strcmp(s,"XNAM") == 0) {
      n = buffer_read_short(b);
      printf("RGDL/XNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Preview Actor FormID %i\n",n);
    } else if (strcmp(s,"RAFD") == 0) {
      n = buffer_read_short(b);
      printf("RGDL/RAFD %i\n",n);
      f = buffer_read_float(b);
      printf("Feedback Dynamic/Keyframe Blend Amount %f\n",f);
      f = buffer_read_float(b);
      printf("Feedback Hierarchy Gain %f\n",f);
      f = buffer_read_float(b);
      printf("Feedback Position Gain %f\n",f);
      f = buffer_read_float(b);
      printf("Feedback Velocity Gain %f\n",f);
      f = buffer_read_float(b);
      printf("Feedback Acceleration Gain %f\n",f);
      f = buffer_read_float(b);
      printf("Feedback Snap Gain %f\n",f);
      f = buffer_read_float(b);
      printf("Feedback Velocity Damping %f\n",f);
      f = buffer_read_float(b);
      printf("Feedback Snap Max Settings Linear Velocity %f\n",f);
      f = buffer_read_float(b);
      printf("Feedback Snap Max Settings Angular Velocity %f\n",f);
      f = buffer_read_float(b);
      printf("Feedback Snap Max Settings Linear Distance %f\n",f);
      f = buffer_read_float(b);
      printf("Feedback Snap Max Settings Angular Distance %f\n",f);
      f = buffer_read_float(b);
      printf("Feedback Position Max Velocity Linear %f\n",f);
      f = buffer_read_float(b);
      printf("Feedback Position Max Velocity Angular %f\n",f);
      n = buffer_read_int(b);
      printf("Feedback Applied Impulse Projectile %i %% Value/1000 is displayed\n",n);
      n = buffer_read_int(b);
      printf("Feedback Applied Impulse Melee %i %% Value/1000 is displayed\n",n);
    } else if (strcmp(s,"RAFB") == 0) {
      n = buffer_read_short(b);
      printf("RGDL/RAFB %i\n",n);
      size = n;
      num = size/2;
      printf("List of Dynamic Bones:\n");
      for (i = 0; i < num; i++) {
	n = buffer_read_short(b);
	printf("%i\n",n);
      }
    } else if (strcmp(s,"RAPS") == 0) {
      n = buffer_read_short(b);
      printf("RGDL/RAPS %i\n",n);
      n = buffer_read_short(b);
      printf("Pose Matching Match Bone 1 %i\n",n);
      n = buffer_read_short(b);
      printf("Pose Matching Match Bone 2 %i\n",n);
      n = buffer_read_short(b);
      printf("Pose Matching Match Bone 3 %i\n",n);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Disable on move\n");
      n = buffer_read_byte(b);
      printf("%i\n",n);
      f = buffer_read_float(b);
      printf("Pose Matching Motors Strength %f %% min 0.0 max 10000.0\n",f);
      f = buffer_read_float(b);
      printf("Pose Matching Pose Activation Delay Time %f %% min 0.0 max 10.0\n",f);
      f = buffer_read_float(b);
      printf("Pose Matching Match Error Allowance %f %% min 0.0 max 1.0\n",f);
      f = buffer_read_float(b);
      printf("Pose Matching Displacement to disable %f %% min 0.0 max 10.0\n",f);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of RGDL\n");

  return -1;
}
