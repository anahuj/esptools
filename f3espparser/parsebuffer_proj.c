
int parsebuffer_proj(void *b)
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
      printf("PROJ/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("PROJ/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("PROJ/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Art file \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("PROJ/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"VNAM") == 0) {
      n = buffer_read_short(b);
      printf("PROJ/VNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Detection Sound Level %i %% 0 Loud 1 Normal 2 Silent\n",n);
    } else if (strcmp(s,"NAM1") == 0) {
      n = buffer_read_short(b);
      printf("PROJ/NAM1 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Muzzle Flash NIF \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"NAM2") == 0) {
      n = buffer_read_short(b);
      printf("PROJ/NAM2 %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"OBND") == 0) {
      n = buffer_read_short(b);
      printf("PROJ/OBND %i\n",n);
      parse_obnd(b);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("PROJ/DATA %i\n",n);
      n = buffer_read_short(b);
      printflags16(n);
      //      0000,0000,0000,0000
      printf("                  ^Hitscan (Visible in VATS Only)\n");
      printf("                 ^Explosion\n");
      printf("                ^0 Trigger on Impact 1 Alt. Trigger\n");
      printf("               ^Muzzle Flash\n");
      printf("            ^Can be Disabled\n");
      printf("           ^Can be Picked Up\n");
      printf("          ^Supersonic\n");
      printf("        ^Crit Effect: Pins Limbs\n");
      printf("       ^Pass Through Small Transparent\n");
      n = buffer_read_short(b);
      printf("Projectile Type %i %% 1 Missile 2 Lobber 4 Beam 8 Flame\n",n);
      f = buffer_read_float(b);
      printf("Gravity %f\n",f);
      f = buffer_read_float(b);
      printf("Speed %f\n",f);
      f = buffer_read_float(b);
      printf("Range %f\n",f);
      n = buffer_read_int(b);
      printf("Light FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Muzzle Flash Light FormID %i\n",n);
      f = buffer_read_float(b);
      printf("Tracer Chance %f\n",f);
      f = buffer_read_float(b);
      printf("Explosion Proximity %f\n",f);
      f = buffer_read_float(b);
      printf("Explosion Timer %f\n",f);
      n = buffer_read_int(b);
      printf("Explosion Type FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Sound FormID %i\n",n);
      f = buffer_read_float(b);
      printf("Muzzle Flash Duration %f\n",f);
      f = buffer_read_float(b);
      printf("Fade Duration %f\n",f);
      f = buffer_read_float(b);
      printf("Impact Force %f\n",f);
      n = buffer_read_int(b);
      printf("Explosion Countdown Sound FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Disable Sound FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Default Weapon Source FormID %i\n",n);
    } else if (strcmp(s,"DEST") == 0) {
      n = buffer_read_short(b);
      printf("PROJ/DEST %i\n",n);
      parse_dest(b);
    } else if (strcmp(s,"DSTD") == 0) {
      n = buffer_read_short(b);
      printf("PROJ/DSTD %i\n",n);
      parse_dstd(b);
    } else if (strcmp(s,"DSTF") == 0) {
      n = buffer_read_short(b);
      printf("PROJ/DSTF %i\n",n);
      // Empty.
    } else if (strcmp(s,"DMDL") == 0) { // F
      n = buffer_read_short(b);
      printf("PROJ/DMDL %i\n",n);
      parse_dmdl(b,n);
    } else if (strcmp(s,"DMDT") == 0) { // F
      n = buffer_read_short(b);
      printf("PROJ/DMDT %i\n",n);
      parse_dmdt(b,n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of PROJ\n");

  return -1;
}
