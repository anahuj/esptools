
int parsebuffer_armo(void *b)
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
      printf("ARMO/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/SCRI %i\n",n);
      n = buffer_read_int(b);
      printf("Script FormID %i\n",n);
    } else if (strcmp(s,"ANAM") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/ANAM %i\n",n);
      n = buffer_read_short(b);
      printf("%i\n",n);
    } else if (strcmp(s,"ENAM") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/ENAM %i\n",n);
      n = buffer_read_int(b);
      printf("Enchanting FormID %i\n",n);
    } else if (strcmp(s,"BMDT") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/BMDT %i\n",n);
      n = buffer_read_uint(b);
      printflags(n);
      //      0000,0000,0000,0000,0000,0000,0000,0000
      printf("                                      ^Head\n");
      printf("                                     ^Hair\n");
      printf("                                    ^UpperBody\n");
      printf("                                   ^LowerBody\n");
      printf("                                 ^Hand\n");
      printf("                                ^Foot\n");
      printf("                               ^RightRing\n");
      printf("                              ^LeftRing\n");
      printf("                            ^Amulet\n");
      printf("                           ^Weapon\n");
      printf("                          ^BackWeapon\n");
      printf("                         ^SideWeapon\n");
      printf("                       ^Quiver\n");
      printf("                      ^Shield\n");
      printf("                     ^Torch\n");
      printf("                    ^Tail\n");
      printf("                  ^Hide Rings\n");
      printf("                 ^Hide Amulet\n");
      printf("           ^~Playable\n");
      printf("          ^Heavy (1) Light (0)\n");
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Male Biped Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"MO2T") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/MO2T %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"MO3T") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/MO3T %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"MO4T") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/MO4T %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"MOD2") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/MOD2 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Male World Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MO2B") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/MO2B %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Male Icon Image \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MOD3") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/MOD3 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Female Biped Mode \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MO3B") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/MO3B %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"MOD4") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/MOD4 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Female World Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MO4B") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/MO4B %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"ICO2") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/ICO2 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Female Icon Image \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/DATA %i\n",n);
      n = buffer_read_short(b);
      printf("AR*100 %i\n",n);
      n = buffer_read_int(b);
      printf("Value %i\n",n);
      n = buffer_read_int(b);
      printf("Health %i\n",n);
      f = buffer_read_float(b);
      printf("Weight %f\n",f);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of ARMO\n");

  return -1;
}
