
int parsebuffer_acre(void *b)
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
      printf("ACRE/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"NAME") == 0) {
      n = buffer_read_short(b);
      printf("ACRE/NAME %i\n",n);
      n = buffer_read_int(b);
      printf("Base Object FormID %i\n",n);
    } else if (strcmp(s,"XRGD") == 0) {
      n = buffer_read_short(b);
      printf("ACRE/XRGD %i\n",n);
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
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("ACRE/DATA %i\n",n);
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
    } else if (strcmp(s,"XSCL") == 0) {
      n = buffer_read_short(b);
      printf("ACRE/XSCL %i\n",n);
      f = buffer_read_float(b);
      printf("Scale %f\n",f);
    } else if (strcmp(s,"XOWN") == 0) {
      n = buffer_read_short(b);
      printf("ACRE/XOWN %i\n",n);
      n = buffer_read_int(b);
      printf("Owner FormID %i\n",n);
    } else if (strcmp(s,"XESP") == 0) {
      n = buffer_read_short(b);
      printf("ACRE/XESP %i\n",n);
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
    } else if (strcmp(s,"XMRC") == 0) { // F
      n = buffer_read_short(b);
      printf("ACRE/XMRC %i\n",n);
      n = buffer_read_int(b);
      printf("Merchant's Container FormID %i\n",n);
    } else if (strcmp(s,"XLKR") == 0) { // F
      n = buffer_read_short(b);
      printf("ACRE/XLKR %i\n",n);
      n = buffer_read_int(b);
      printf("Linked Ref FormID %i\n",n);
    } else if (strcmp(s,"XLCM") == 0) { // F
      n = buffer_read_short(b);
      printf("ACRE/XLCM %i\n",n);
      n = buffer_read_int(b);
      printf("Level Modifier %i %% 0 Easy 1 Medium 2 Hard 3 Boss (no-XLCM is None)\n",n);
    } else if (strcmp(s,"XAPD") == 0) { // F
      n = buffer_read_short(b);
      printf("ACRE/XAPD %i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"XAPR") == 0) { // F
      n = buffer_read_short(b);
      printf("ACRE/XAPR %i\n",n);
      n = buffer_read_int(b);
      printf("Activate Parent Ref FormID %i\n",n);
      f = buffer_read_float(b);
      printf("Activate Parent Delay %f\n",f);
    } else if (strcmp(s,"XEMI") == 0) { // F
      n = buffer_read_short(b);
      printf("ACRE/XEMI %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"XEZN") == 0) { // F
      n = buffer_read_short(b);
      printf("ACRE/XEZN %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"XRGB") == 0) { // F
      n = buffer_read_short(b);
      printf("ACRE/XRGB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"XRDS") == 0) { // F
      n = buffer_read_short(b);
      printf("ACRE/XRDS %i\n",n);
      f = buffer_read_float(b);
      printf("Radius %f\n",f);
    } else if (strcmp(s,"XPRD") == 0) { // F
      n = buffer_read_short(b);
      printf("ACRE/XPRD %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"XPPA") == 0) { // F
      n = buffer_read_short(b);
      printf("ACRE/XPPA %i\n",n);
      // Empty.
    } else if (strcmp(s,"INAM") == 0) { // F
      n = buffer_read_short(b);
      printf("ACRE/INAM %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"SCHR") == 0) { // F
      n = buffer_read_short(b);
      printf("ACRE/SCHR %i\n",n);
      parse_schr(b);
    } else if (strcmp(s,"TNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("ACRE/TNAM %i\n",n);
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
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of ACRE\n");

  return -1;
}
