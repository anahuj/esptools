
int parsebuffer_achr(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int size;

  printf("refsearch 0x%.8x (dec%i) in %s, %s, %i, %i\n",global_formid,global_formid,global_worldspace,global_cell,global_cell_x,global_cell_y);

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("ACHR/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"NAME") == 0) {
      n = buffer_read_short(b);
      printf("ACHR/NAME %i\n",n);
      n = buffer_read_int(b);
      printf("Base Object FormID %i\n",n);
    } else if (strcmp(s,"FULL") == 0) { // Not in Fallout3.esm
      n = buffer_read_short(b);
      printf("ACHR/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"XESP") == 0) {
      n = buffer_read_short(b);
      printf("ACHR/XESP %i\n",n);
      n = buffer_read_int(b);
      printf("Enable Parent FormID %i\n",n);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Set Enable State to Opposite of Parent\n");
      printf("       ^Pop In\n");
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"XLOD") == 0) { // Not in Fallout3.esm
      n = buffer_read_short(b);
      printf("ACHR/XLOD %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"XHRS") == 0) { // Not in Fallout3.esm
      n = buffer_read_short(b);
      printf("ACHR/XHRS %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"XMRC") == 0) {
      n = buffer_read_short(b);
      printf("ACHR/XMRC %i\n",n);
      n = buffer_read_int(b);
      printf("Merchant Container FormID %i\n",n);
    } else if (strcmp(s,"XRGD") == 0) {
      n = buffer_read_short(b);
      printf("ACHR/XRGD %i\n",n);
      m = n/28;
      for (i = 0; i < m; i++) {
	n = buffer_read_byte(b);
	printf("%i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
	f = buffer_read_float(b);
	printf("%f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"XSCL") == 0) {
      n = buffer_read_short(b);
      printf("ACHR/XSCL %i\n",n);
      f = buffer_read_float(b);
      printf("Scale %f\n",f);
    } else if (strcmp(s,"XPCI") == 0) { // Not in Fallout3.esm
      n = buffer_read_short(b);
      printf("ACHR/XPCI %i\n",n);
      n = buffer_read_int(b);
      printf("unknown Cell(?) FormID %i\n",n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("ACHR/DATA %i\n",n);
      f = buffer_read_float(b);
      printf("Position X %f\n",f);
      f = buffer_read_float(b);
      printf("Position Y %f\n",f);
      f = buffer_read_float(b);
      printf("Position Z %f\n",f);
      f = buffer_read_float(b);
      printf("Rotation X %f\n",f);
      f = buffer_read_float(b);
      printf("Rotation Y %f\n",f);
      f = buffer_read_float(b);
      printf("Rotation Z %f\n",f);
    } else if (strcmp(s,"XLCM") == 0) { // F
      n = buffer_read_short(b);
      printf("ACHR/XLCM %i\n",n);
      n = buffer_read_int(b);
      printf("Level Modifier %i %% 0 Easy 1 Medium 2 Hard 3 Boss (no-XLCM is None)\n",n);
    } else if (strcmp(s,"XLKR") == 0) { // F
      n = buffer_read_short(b);
      printf("ACHR/XLKR %i\n",n);
      n = buffer_read_int(b);
      printf("Linked Ref FormID %i\n",n);
    } else if (strcmp(s,"XRGB") == 0) { // F
      n = buffer_read_short(b);
      printf("ACHR/XRGB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"XEZN") == 0) { // F
      n = buffer_read_short(b);
      printf("ACHR/XEZN %i\n",n);
      n = buffer_read_int(b);
      printf("Encounter Zone FormID %i\n",n);
    } else if (strcmp(s,"XRDS") == 0) { // F
      n = buffer_read_short(b);
      printf("ACHR/XRDS %i\n",n);
      f = buffer_read_float(b);
      printf("Radius %f\n",f);
    } else if (strcmp(s,"XIBS") == 0) { // F
      n = buffer_read_short(b);
      printf("ACHR/XIBS %i\n",n);
      // Empty.
      printf("Ignored By Sandbox\n");
    } else if (strcmp(s,"XPRD") == 0) { // F
      n = buffer_read_short(b);
      printf("ACHR/XPRD %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"XPPA") == 0) { // F
      n = buffer_read_short(b);
      printf("ACHR/XPPA %i\n",n);
      // Empty.
    } else if (strcmp(s,"INAM") == 0) { // F
      n = buffer_read_short(b);
      printf("ACHR/INAM %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"SCHR") == 0) { // F
      n = buffer_read_short(b);
      printf("ACHR/SCHR %i\n",n);
      parse_schr(b);
    } else if (strcmp(s,"TNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("ACHR/TNAM %i\n",n);
      size = n;
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      if (size == 4) {
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
      }
    } else if (strcmp(s,"XAPD") == 0) { // Not in Fallout3.esm. In esp.
      n = buffer_read_short(b);
      printf("ACHR/XAPD %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Parent Activate Only\n");
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of ACHR\n");

  return -1;
}
