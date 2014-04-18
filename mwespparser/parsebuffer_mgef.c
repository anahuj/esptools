
int parsebuffer_mgef(void *b)
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
    if (strcmp(s,"INDX") == 0) {
      n = buffer_read_int(b);
      printf("MGEF/INDX %i\n",n);
      n = buffer_read_int(b);
      printf("Effect %i %% Index to GMST/sEffect list.\n",n);
    } else if (strcmp(s,"MEDT") == 0) {
      n = buffer_read_int(b);
      printf("MGEF/MEDT %i\n",n);
      n = buffer_read_int(b);
      printf("School %i %% 0 Alteration 1 Conjuration 2 Destruction 3 Illusion 4 Mysticism 5 Restoration\n",n);
      f = buffer_read_float(b);
      printf("Base Cost %f\n",f);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("       ^\n");
      printf("      ^\n");
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("Lighting Effect Color R %i\n",n);
      n = buffer_read_int(b);
      printf("Lighting Effect Color G %i\n",n);
      n = buffer_read_int(b);
      printf("Lighting Effect Color B %i\n",n);
      f = buffer_read_float(b);
      printf("Scale Size X %f\n",f);
      f = buffer_read_float(b);
      printf("Scale Speed X %f\n",f);
      f = buffer_read_float(b);
      printf("Scale Size Cap %f\n",f);
    } else if (strcmp(s,"ITEX") == 0) {
      n = buffer_read_int(b);
      printf("MGEF/ITEX %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Effect Icon \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"PTEX") == 0) {
      n = buffer_read_int(b);
      printf("MGEF/PTEX %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Particle Texture \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"AVFX") == 0) {
      n = buffer_read_int(b);
      printf("MGEF/AVFX %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Area Effects Visual \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"BVFX") == 0) {
      n = buffer_read_int(b);
      printf("MGEF/BVFX %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Bolt Effects Visual \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"CVFX") == 0) {
      n = buffer_read_int(b);
      printf("MGEF/CVFX %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Casting Effects Visual \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"HVFX") == 0) {
      n = buffer_read_int(b);
      printf("MGEF/HVFX %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Hit Effects Visual \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ASND") == 0) {
      n = buffer_read_int(b);
      printf("MGEF/ASND %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Area Effects Sound \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"BSND") == 0) {
      n = buffer_read_int(b);
      printf("MGEF/BSND %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Bolt Effects Sound \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"CSND") == 0) {
      n = buffer_read_int(b);
      printf("MGEF/CSND %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Casting Effects Sound \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"HSND") == 0) {
      n = buffer_read_int(b);
      printf("MGEF/HSND %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Hit Effects Sound \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DESC") == 0) {
      n = buffer_read_int(b);
      printf("MGEF/DESC %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Description \"%s\"\n",s2);
      free(s2);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of MGEF\n");

  return -1;
}
