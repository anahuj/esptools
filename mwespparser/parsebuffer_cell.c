
int parsebuffer_cell(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int isfirstdata;
  int int1ext2;
  int numslcs1;
  int numslcs2;
  int numslcs3;
  int size;

  numslcs1 = 0;
  numslcs2 = 0;
  numslcs3 = 0;

  isfirstdata = 0;
  int1ext2 = -1;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"NAME") == 0) {
      n = buffer_read_int(b);
      printf("CELL/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      if (isfirstdata == 0) {
	printf("%s\n",s2);
      } else {
	printf("Reference Object \"%s\"\n",s2);
      }
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_int(b);
      printf("CELL/DATA %i\n",n);
      if (isfirstdata == 0) {
	n = buffer_read_ubyte(b);
	printflags8(n);
	//      0000,0000
	printf("        ^Interior\n");
	printf("       ^Exterior\n");
	printf("       ^^11 Interior + Has Water\n");
	printf("      ^Illegal To Sleep Here\n");
	printf("     ^(??savefile related??)\n");
	printf("   ^(??savefile related??)\n");
	printf("  ^(??savefile related??)\n");
	printf(" ^Map Color (Exterior)\n");
	printf("^Behave Like Exterior\n");
	int1ext2 = n & 0x3;
	n = buffer_read_ubyte(b);
	printf("%i (unused)\n",n);
	n = buffer_read_ubyte(b);
	printf("%i (unused)\n",n);
	n = buffer_read_ubyte(b);
	printf("%i (unused)\n",n);

	if (int1ext2 == 2) {
	  n = buffer_read_int(b);
	  printf("Cell Location X %i\n",n);
	  n = buffer_read_int(b);
	  printf("Cell Location Y %i\n",n);
	} else if (int1ext2 == 1) {
#if 1
	  n = buffer_read_ubyte(b);
	  printf("Fog Color R %i\n",n);
	  n = buffer_read_ubyte(b);
	  printf("Fog Color G %i\n",n);
	  n = buffer_read_ubyte(b);
	  printf("Fog Color B %i\n",n);
	  n = buffer_read_ubyte(b);
	  printf("%i\n",n);
	  f = buffer_read_float(b);
	  printf("Fog Density %f\n",f);
#else
	  n = buffer_read_int(b);
	  printf("%i\n",n);
	  f = buffer_read_float(b);
	  printf("%f\n",f);
#endif
	} else if (int1ext2 == 3) {
	  n = buffer_read_ubyte(b);
	  printf("Fog Color R %i\n",n);
	  n = buffer_read_ubyte(b);
	  printf("Fog Color G %i\n",n);
	  n = buffer_read_ubyte(b);
	  printf("Fog Color B %i\n",n);
	  n = buffer_read_ubyte(b);
	  printf("%i\n",n);
	  f = buffer_read_float(b);
	  printf("Fog Density %f\n",f);
	} else {
	  f = buffer_read_float(b);
	  printf("%f\n",f);
	  f = buffer_read_float(b);
	  printf("%f\n",f);
#if 0
	  printf("Cell is not interior nor exterior\n");
	  exit(-1);
#endif
	}
	isfirstdata = 1;
      } else {
	// XXXX We should read this DATA as part of FRMR section.
	f = buffer_read_float(b);
	printf("Position X %f\n",f);
	f = buffer_read_float(b);
	printf("Position X %f\n",f);
	f = buffer_read_float(b);
	printf("Position X %f\n",f);
	f = buffer_read_float(b);
	printf("Rotation X %f\n",f);
	f = buffer_read_float(b);
	printf("Rotation Y %f\n",f);
	f = buffer_read_float(b);
	printf("Rotation Z %f\n",f);
      }
    } else if (strcmp(s,"RGNN") == 0) {
      n = buffer_read_int(b);
      printf("CELL/RGNN %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Region (Weather Type) \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"NAM0") == 0) {
      n = buffer_read_int(b);
      printf("CELL/NAM0 %i\n",n);
      n = buffer_read_int(b);
      printf("Reference Count %i\n",n);
    } else if (strcmp(s,"NAM5") == 0) {
      n = buffer_read_int(b);
      printf("CELL/NAM5 %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Map Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Map Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Map Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"NAM9") == 0) {
      n = buffer_read_int(b);
      printf("CELL/NAM9 %i\n",n);
      n = buffer_read_int(b);
      printf("%i %% Extra Data flag??\n",n);
    } else if (strcmp(s,"FRMR") == 0) {
      n = buffer_read_int(b);
      printf("CELL/FRMR %i\n",n);
      n = buffer_read_int(b);
      printf("FormID %i\n",n);
    } else if (strcmp(s,"XSCL") == 0) {
      n = buffer_read_int(b);
      printf("CELL/XSCL %i\n",n);
      f = buffer_read_float(b);
      printf("3D Scale %f\n",f);
    } else if (strcmp(s,"DODT") == 0) {
      n = buffer_read_int(b);
      printf("CELL/DODT %i\n",n);
      f = buffer_read_float(b);
      printf("Position X %f\n",f);
      f = buffer_read_float(b);
      printf("Position X %f\n",f);
      f = buffer_read_float(b);
      printf("Position X %f\n",f);
      f = buffer_read_float(b);
      printf("Rotation X %f\n",f);
      f = buffer_read_float(b);
      printf("Rotation Y %f\n",f);
      f = buffer_read_float(b);
      printf("Rotation Z %f\n",f);
    } else if (strcmp(s,"DNAM") == 0) {
      n = buffer_read_int(b);
      printf("CELL/DNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Cell \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ANAM") == 0) {
      n = buffer_read_int(b);
      printf("CELL/ANAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Reference Assignable Data Owner \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"BNAM") == 0) {
      n = buffer_read_int(b);
      printf("CELL/BNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Global Variable / Rank \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"KNAM") == 0) {
      n = buffer_read_int(b);
      printf("CELL/KNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Ref Locked Key \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"CNAM") == 0) {
      n = buffer_read_int(b);
      printf("CELL/CNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Reference Assignable Data Owner Faction \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"TNAM") == 0) {
      n = buffer_read_int(b);
      printf("CELL/TNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Ref Locked Trap \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"UNAM") == 0) {
      n = buffer_read_int(b);
      printf("CELL/UNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Reference Blocked \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"XSOL") == 0) {
      n = buffer_read_int(b);
      printf("CELL/XSOL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Ref Extra Data Soul %s\n",s2);
      free(s2);
    } else if (strcmp(s,"INTV") == 0) {
      n = buffer_read_int(b);
      printf("CELL/INTV %i\n",n);
      m = buffer_getloc(b);
      n = buffer_read_int(b);
      buffer_setloc(b,m);
      f = buffer_read_float(b);
      printf("Reference Extra Data Health Left %i / Interior Water Height %i / %f\n",n,n,f);
    } else if (strcmp(s,"FLTV") == 0) {
      n = buffer_read_int(b);
      printf("CELL/FLTV %i\n",n);
      m = buffer_getloc(b);
      n = buffer_read_int(b);
      buffer_setloc(b,m);
      f = buffer_read_float(b);
      printf("%i / %f\n",n,f);
    } else if (strcmp(s,"INDX") == 0) {
      n = buffer_read_int(b);
      printf("CELL/INDX %i\n",n);
      n = buffer_read_int(b);
      printf("Rank Index %i\n",n);
    } else if (strcmp(s,"AMBI") == 0) {
      n = buffer_read_int(b);
      printf("CELL/AMBI %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Ambient Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Ambient Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Ambient Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("Sunlight Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Sunlight Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Sunlight Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("Fog Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Fog Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Fog Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      f = buffer_read_float(b);
      printf("Fog Density %f\n",f);
    } else if (strcmp(s,"XCHG") == 0) {
      n = buffer_read_int(b);
      printf("CELL/XCHG %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"WHGT") == 0) { // Tribunal.
      n = buffer_read_int(b);
      printf("CELL/WHGT %i\n",n);
      f = buffer_read_float(b);
      printf("Water Height %f\n",f);
    } else if (strcmp(s,"ZNAM") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/ZNAM %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"LVCR") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/LVCR %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"SCRI") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/SCRI %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Script \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SLCS") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/SLCS %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      numslcs1 = n;
      n = buffer_read_int(b);
      printf("%i\n",n);
      numslcs2 = n;
      n = buffer_read_int(b);
      printf("%i\n",n);
      numslcs3 = n;
    } else if (strcmp(s,"SLSD") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/SLSD %i\n",n);
      printf("data given by numslcs1:\n");
      for (i = 0; i < numslcs1; i++) {
	n = buffer_read_short(b);
	printf("%i\n",n);
      }
    } else if (strcmp(s,"SLLD") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/SLLD %i\n",n);
      printf("data given by numslcs2:\n");
      for (i = 0; i < numslcs2; i++) {
	n = buffer_read_int(b);
	printf("%i\n",n);
      }
    } else if (strcmp(s,"SLFD") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/SLFD %i\n",n);
      printf("data given by numslcs3:\n");
      for (i = 0; i < numslcs3; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"ACDT") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/ACDT %i\n",n);
      n = buffer_read_int(b); // == 0 so far
      printf("%i\n",n);
      n = buffer_read_int(b); // == 0 so far
      printf("%i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
      n = buffer_read_int(b); // int
      printf("%i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      n = buffer_read_int(b); // int
      printf("%i\n",n);
      n = buffer_read_int(b); // int
      printf("%i\n",n);
      for (i = 0; i < 8; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
      f = buffer_read_float(b);
      printf("%f\n",f);
      for (i = 0; i < 17; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
      n = buffer_read_int(b); // == 0 so far
      printf("%i\n",n);
      n = buffer_read_int(b); // == 0 so far
      printf("%i\n",n);
      n = buffer_read_int(b); // 6 int
      printf("%i\n",n);
      n = buffer_read_int(b); // 7 int
      printf("%i\n",n);
      n = buffer_read_int(b); // 8 int
      printf("%i\n",n);
      n = buffer_read_int(b); // 9 int
      printf("%i\n",n);
      n = buffer_read_int(b); // 10 int
      printf("%i\n",n);
      n = buffer_read_int(b); // 11 == 0 so far
      printf("%i\n",n);
      n = buffer_read_int(b); // 12 == 0 so far
      printf("%i\n",n);
      n = buffer_read_int(b); // 13 int
      printf("%i\n",n);
      n = buffer_read_int(b); // 14 int
      printf("%i\n",n);
      n = buffer_read_int(b); // 15 int
      printf("%i\n",n);
      n = buffer_read_int(b); // 16 int
      printf("%i\n",n);
      n = buffer_read_int(b); // 17 == 0 so far
      printf("%i\n",n);
      n = buffer_read_int(b); // 18 == 0 so far
      printf("%i\n",n);
      n = buffer_read_int(b); // 19 == 0 so far
      printf("%i\n",n);
      n = buffer_read_int(b); // 20 == 0 so far
      printf("%i\n",n);
      n = buffer_read_int(b); // 21 == 0 so far
      printf("%i\n",n);
      n = buffer_read_int(b); // 22 == 0 so far
      printf("%i\n",n);
      n = buffer_read_int(b); // 23 == 0 so far
      printf("%i\n",n);
      n = buffer_read_int(b); // 24 == 0 so far
      printf("%i\n",n);
      n = buffer_read_int(b); // 25 == 0 so far
      printf("%i\n",n);
      n = buffer_read_int(b); // 26 int
      printf("%i\n",n);
      n = buffer_read_int(b); // 27 == 0 so far
      printf("%i\n",n);
#if 0
      for (i = 0; i < 22; i++) {
	n = buffer_read_int(b);
	printf("acdtunk%i %i\n",6+i,n);
      }
#endif
      n = buffer_read_int(b); // int
      printf("%i\n",n);
      n = buffer_read_int(b); // int
      printf("%i\n",n);
      n = buffer_read_int(b); // int
      printf("%i\n",n);
      n = buffer_read_int(b); // int
      printf("%i\n",n);
      n = buffer_read_int(b); // int
      printf("%i\n",n);
      n = buffer_read_int(b); // int
      printf("%i\n",n);
    } else if (strcmp(s,"ACSC") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/ACSC %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      f = buffer_read_float(b); // XXXX nan but has also valid float values
      printf("%f\n",f);
      n = buffer_read_int(b);
      printf("%i\n",n);
      f = buffer_read_float(b); // XXXX nan but has also valid float values
      printf("%f\n",f);
      n = buffer_read_int(b);
      printf("%i\n",n);
      f = buffer_read_float(b); // XXXX nan but has also valid float values
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
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
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"ACSL") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/ACSL %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
#if 1
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
#else
      f = buffer_read_float(b); // 0  0 40 34 prints as 0.000000; not float
      printf("%f\n",f);
#endif
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
#if 0
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
#else
      f = buffer_read_float(b); // ff ff 80 bf prints as -1.007812; float?
      printf("%f\n",f);
#endif
      f = buffer_read_float(b); // X?
      printf("%f\n",f);
      f = buffer_read_float(b); // Y?
      printf("%f\n",f);
      f = buffer_read_float(b); // Z?
      printf("%f\n",f);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"CRED") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/CRED %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"STPR") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/STPR %i\n",n);
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
    } else if (strcmp(s,"NAM8") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/NAM8 %i\n",n);
      size = n;
      for (i = 0; i < size; i++) {
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
      }
    } else if (strcmp(s,"ACTN") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/ACTN %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"CHRD") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/CHRD %i\n",n);
      size = n;
      for (i = 0; i < size/4; i++) {
	n = buffer_read_int(b);
	printf("%i\n",n);
      }
    } else if (strcmp(s,"DELE") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/DELE %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"MNAM") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/MNAM %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"LSTN") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/LSTN %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"ND3D") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/ND3D %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"ANIS") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/ANIS %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"FGTN") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/FGTN %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"MVRF") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/MVRF %i\n",n);
      n = buffer_read_int(b);
      printf("%i formid?\n",n);
    } else if (strcmp(s,"CNDT") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/CNDT %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"CSTN") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/CSTN %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"CSHN") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/CSHN %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"LSHN") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/LSHN %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"TGTN") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/TGTN %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"WNAM") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/WNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"MPCD") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/MPCD %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"MPNT") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/MPNT %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"XNAM") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/XNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"YNAM") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CELL/YNAM %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else {
      printf("Unknown chunk name\n");
      printhexdump(b,-4,120);
      exit(-1);
    }
    free(s);
  }

  printf("End of CELL\n");

  return -1;
}
