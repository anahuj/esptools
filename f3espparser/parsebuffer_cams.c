
int parsebuffer_cams(void *b)
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
      printf("CAMS/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("CAMS/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Path \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("CAMS/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"MNAM") == 0) {
      n = buffer_read_short(b);
      printf("CAMS/MNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Imagespace Mod FormID %i\n",n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("CAMS/DATA %i\n",n);
      size = n;
      n = buffer_read_int(b);
      printf("Camera Action %i %% 0 Shoot 1 Fly 2 Hit\n",n);
      n = buffer_read_int(b);
      printf("Camera Location %i %% 0 Attacker 1 Projectile 2 Target\n",n);
      n = buffer_read_int(b);
      printf("Camera Target %i %% 0 Attacker 1 Projectile 2 Target\n",n);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Position Follows Location\n");
      printf("       ^Rotation Follows Target\n");
      printf("      ^Don't Follow Bone\n");
      printf("     ^First Person Camera\n");
      printf("   ^No Tracer\n");
      printf("  ^Start At Time Zero\n");
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      f = buffer_read_float(b);
      printf("Time Multipliers Player %f\n",f);
      f = buffer_read_float(b);
      printf("Time Multipliers Target %f\n",f);
      f = buffer_read_float(b);
      printf("Time Multipliers Global %f\n",f);
      f = buffer_read_float(b);
      printf("Max Time %f\n",f);
      f = buffer_read_float(b);
      printf("Min Time %f\n",f);
      if (size >= 40) {
	f = buffer_read_float(b);
	printf("Target %% Between Actors %f\n",f);
      }
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of CAMS\n");

  return -1;
}
