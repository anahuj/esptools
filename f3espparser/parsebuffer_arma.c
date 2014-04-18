
int parsebuffer_arma(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int num;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("ARMA/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("ARMA/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"BMDT") == 0) {
      n = buffer_read_short(b);
      printf("ARMA/BMDT %i\n",n);
      n = buffer_read_uint(b);
      printflags(n);
      //      0000,0000,0000,0000,0000,0000,0000,0000
      printf("                                      ^Head\n");
      printf("                                     ^Hair\n");
      printf("                                    ^UpperBody\n");
      printf("                                   ^LeftHand\n");
      printf("                                 ^RightHand\n");
      printf("                                ^Weapon\n");
      printf("                               ^PipBoy\n");
      printf("                              ^Backpack\n");
      printf("                            ^Necklace\n");
      printf("                           ^Headband\n");
      printf("                          ^Hat\n");
      printf("                         ^EyeGlasses\n");
      printf("                       ^NoseRing\n");
      printf("                      ^Earrings\n");
      printf("                     ^Mask\n");
      printf("                    ^Choker\n");
      printf("                  ^MouthObject\n");
      printf("                 ^BodyAddOn1\n");
      printf("                ^BodyAddOn2\n");
      printf("               ^BodyAddOn3\n");
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("   ^????\n");
      printf(" ^????\n");
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("ARMA/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Male Biped Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("ARMA/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"MO2T") == 0) {
      n = buffer_read_short(b);
      printf("ARMA/MO2T %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"MO3T") == 0) {
      n = buffer_read_short(b);
      printf("ARMA/MO3T %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"MOD2") == 0) {
      n = buffer_read_short(b);
      printf("ARMA/MOD2 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Male World Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("ARMA/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Male Icon Image \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MOD3") == 0) {
      n = buffer_read_short(b);
      printf("ARMA/MOD3 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Female Biped Mode \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ICO2") == 0) {
      n = buffer_read_short(b);
      printf("ARMA/ICO2 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Female Icon Image \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMA/DATA %i\n",n);
#if 0
      n = buffer_read_short(b);
      printf("AR*100 %i\n",n);
#endif
      n = buffer_read_int(b);
      printf("Value %i\n",n);
      n = buffer_read_int(b);
      printf("Health %i\n",n);
      f = buffer_read_float(b);
      printf("Weight %f\n",f);
    } else if (strcmp(s,"OBND") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMA/OBND %i\n",n);
      parse_obnd(b);
    } else if (strcmp(s,"ETYP") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMA/ETYP %i\n",n);
      n = buffer_read_int(b);
      printf("Equip Type %i %% 0 BigGuns 1 EnergyWeapons 2 SmallGuns 3 MeleeWeapons 4 UnarmedWeapons 5 ThrowWeapons 6 Mine 7 BodyWear 8 HeadWear 9 HandWear 10 Chems 11 Stimpack 12 Food 13 Alcohol\n",n);
    } else if (strcmp(s,"DNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMA/DNAM %i\n",n);
      n = buffer_read_short(b);
      printf("%i %% unknown, values 0 200 500 1000 in Fallout3.esm\n",n);
      n = buffer_read_byte(b);
      printf("Modulates Voice %i %% 0 Disabled 1 Enabled\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"MODD") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMA/MODD %i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"MOSD") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMA/MOSD %i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"MODS") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMA/MODS %i\n",n);
      parse_mods(b);
#if 0
      // MO3S but not MO2S?? Keep this.
    } else if (strcmp(s,"MO2S") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMA/MO2S %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      num = n;
      for (i = 0; i < num; i++) {
	s2 = buffer_read_intstring(b);
	printf("%s\n",s2);
	free(s2);
	n = buffer_read_int(b);
	printf("%i\n",n);
	n = buffer_read_int(b);
	printf("%i\n",n);
      }
#endif
    } else if (strcmp(s,"MO3S") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMA/MO3S %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      num = n;
      for (i = 0; i < num; i++) {
	s2 = buffer_read_intstring(b);
	printf("%s\n",s2);
	free(s2);
	n = buffer_read_int(b);
	printf("%i\n",n);
	n = buffer_read_int(b);
	printf("%i\n",n);
      }
    } else if (strcmp(s,"DEST") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMA/DEST %i\n",n);
      parse_dest(b);
    } else if (strcmp(s,"DSTD") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMA/DSTD %i\n",n);
      parse_dstd(b);
    } else if (strcmp(s,"DSTF") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMA/DSTF %i\n",n);
      // Empty.
    } else if (strcmp(s,"DMDL") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMA/DMDL %i\n",n);
      parse_dmdl(b,n);
    } else if (strcmp(s,"DMDT") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMA/DMDT %i\n",n);
      parse_dmdt(b,n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of ARMA\n");

  return -1;
}
