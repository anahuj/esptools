
int parsebuffer_alch(void *b)
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
      printf("ALCH/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("ALCH/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("ALCH/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("ALCH/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("ALCH/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("ALCH/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Inventory Image \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("ALCH/DATA %i\n",n);
      f = buffer_read_float(b);
      printf("Weight %f\n",f);
    } else if (strcmp(s,"ENIT") == 0) { // F
      n = buffer_read_short(b);
      printf("ALCH/ENIT %i\n",n);
      n = buffer_read_int(b);
      printf("Potion Value %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^~Auto-Calculate\n");
      printf("       ^Food Item\n");
      printf("      ^Medicine\n");
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_int(b);
      printf("Addiction FormID %i\n",n);
#if 0
      n = buffer_read_int(b);
      printf("%i\n",n);
#else
      f = buffer_read_float(b);
      printf("Addiction Chance %f\n",f);
#endif
      n = buffer_read_int(b);
      printf("Use Sound FormID %i\n",n);
    } else if (strcmp(s,"EFID") == 0) { // F
      n = buffer_read_short(b);
      printf("ALCH/EFID %i\n",n);
      n = buffer_read_int(b);
      printf("Effect FormID %i\n",n);
    } else if (strcmp(s,"EFIT") == 0) {
      n = buffer_read_short(b);
      printf("ALCH/EFIT %i\n",n);
      parse_efit(b);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_short(b);
      printf("ALCH/SCRI %i\n",n);
      n = buffer_read_int(b);
      printf("Script FormID %i\n",n);
    } else if (strcmp(s,"SCIT") == 0) {
      n = buffer_read_short(b);
      printf("ALCH/SCIT %i\n",n);
      parse_scit(b,n);
    } else if (strcmp(s,"OBND") == 0) { // F
      n = buffer_read_short(b);
      printf("ALCH/OBND %i\n",n);
      parse_obnd(b);
    } else if (strcmp(s,"ETYP") == 0) { // F
      n = buffer_read_short(b);
      printf("ALCH/ETYP %i\n",n);
      n = buffer_read_int(b);
      printf("Equip Type %i %% 0 BigGuns 1 EnergyWeapons 2 SmallGuns 3 MeleeWeapons 4 UnarmedWeapons 5 ThrowWeapons 6 Mine 7 BodyWear 8 HeadWear 9 HandWear 10 Chems 11 Stimpack 12 Food 13 Alcohol\n",n);
    } else if (strcmp(s,"CTDA") == 0) { // F
      n = buffer_read_short(b);
      printf("ALCH/CTDA %i\n",n);
      parse_ctda(b,n);
    } else if (strcmp(s,"MICO") == 0) { // F
      n = buffer_read_short(b);
      printf("ALCH/MICO %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Message Icon \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"YNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("ALCH/YNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Pickup Sound FormID %i\n",n);
    } else if (strcmp(s,"ZNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("ALCH/ZNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Putdown Sound FormID %i\n",n);
    } else if (strcmp(s,"DEST") == 0) { // F
      n = buffer_read_short(b);
      printf("ALCH/DEST %i\n",n);
      parse_dest(b);
    } else if (strcmp(s,"DSTD") == 0) { // F
      n = buffer_read_short(b);
      printf("ALCH/DSTD %i\n",n);
      parse_dstd(b);
    } else if (strcmp(s,"DSTF") == 0) { // F
      n = buffer_read_short(b);
      printf("ALCH/DSTF %i\n",n);
      // Empty.
    } else if (strcmp(s,"DMDL") == 0) { // F
      n = buffer_read_short(b);
      printf("ALCH/DMDL %i\n",n);
      parse_dmdl(b,n);
    } else if (strcmp(s,"DMDT") == 0) { // F
      n = buffer_read_short(b);
      printf("ALCH/DMDT %i\n",n);
      parse_dmdt(b,n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of ALCH\n");

  return -1;
}
