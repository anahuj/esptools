
int parsebuffer_armo(void *b)
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
    } else if (strcmp(s,"BMDT") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/BMDT %i\n",n);
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
      printf("  ^Power Armor\n");
      printf(" ^~Playable\n");
      printf("^0 Light 1 Heavy\n");
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Male Biped Model \"%s\"\n",s2);
      free(s2);
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
    } else if (strcmp(s,"MOD4") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/MOD4 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Female World Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ICO2") == 0) {
      n = buffer_read_short(b);
      printf("ARMO/ICO2 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Female Icon Image \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMO/DATA %i\n",n);
      n = buffer_read_int(b);
      printf("Value %i\n",n);
      n = buffer_read_int(b);
      printf("Health %i\n",n);
      f = buffer_read_float(b);
      printf("Weight %f\n",f);
    } else if (strcmp(s,"OBND") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMO/OBND %i\n",n);
      parse_obnd(b);
    } else if (strcmp(s,"REPL") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMO/REPL %i\n",n);
      n = buffer_read_int(b);
      printf("Repair Item List FormID %i\n",n);
    } else if (strcmp(s,"ETYP") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMO/ETYP %i\n",n);
      n = buffer_read_int(b);
      printf("Equip Type %i %% 0 BigGuns 1 EnergyWeapons 2 SmallGuns 3 MeleeWeapons 4 UnarmedWeapons 5 ThrowWeapons 6 Mine 7 BodyWear 8 HeadWear 9 HandWear 10 Chems 11 Stimpack 12 Food 13 Alcohol\n",n);
    } else if (strcmp(s,"DNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMO/DNAM %i\n",n);
      n = buffer_read_short(b);
      printf("AR %i %% Editor displays AR/100\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Modulates Voice\n");
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"MODD") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMO/MODD %i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"MOSD") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMO/MOSD %i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"YNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMO/YNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Pickup Sound FormID %i\n",n);
    } else if (strcmp(s,"ZNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMO/ZNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Putdown Sound FormID %i\n",n);
    } else if (strcmp(s,"EITM") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMO/EITM %i\n",n);
      n = buffer_read_int(b);
      printf("Object Effect FormID %i\n",n);
    } else if (strcmp(s,"MODS") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMO/MODS %i\n",n);
      parse_mods(b);
    } else if (strcmp(s,"MO2S") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMO/MO2S %i\n",n);
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
    } else if (strcmp(s,"MO3S") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMO/MO3S %i\n",n);
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
    } else if (strcmp(s,"MO4S") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMO/MO4S %i\n",n);
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
    } else if (strcmp(s,"MICO") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMO/MICO %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Message Icon \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"BMCT") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMO/BMCT %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Ragdoll Constraint Template \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"BIPL") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMO/BIPL %i\n",n);
      n = buffer_read_int(b);
      printf("Biped Model List FormID %i\n",n);
    } else if (strcmp(s,"DEST") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMO/DEST %i\n",n);
      parse_dest(b);
    } else if (strcmp(s,"DSTD") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMO/DSTD %i\n",n);
      parse_dstd(b);
    } else if (strcmp(s,"DSTF") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMO/DSTF %i\n",n);
      // Empty.
    } else if (strcmp(s,"DMDL") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMO/DMDL %i\n",n);
      parse_dmdl(b,n);
    } else if (strcmp(s,"DMDT") == 0) { // F
      n = buffer_read_short(b);
      printf("ARMO/DMDT %i\n",n);
      parse_dmdt(b,n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of ARMO\n");

  return -1;
}
