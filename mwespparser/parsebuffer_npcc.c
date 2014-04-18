
int parsebuffer_npcc(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int size;
  int numslcs1;
  int numslcs2;
  int numslcs3;

  numslcs1 = 0;
  numslcs2 = 0;
  numslcs3 = 0;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"NAME") == 0) {
      n = buffer_read_int(b);
      printf("NPCC/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"NPDT") == 0) {
      n = buffer_read_int(b);
      printf("NPCC/NPDT %i\n",n);
      size = n;
      // XXXX Copied from NPC_. Meaning may differ. Check.
      if (size == 8) {
	n = buffer_read_ushort(b);
	printf("Level %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Disp %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Rep %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Rank %i %% See FACT record. RNAM indexing starts from 0\n",n);
	n = buffer_read_ubyte(b);
	printf("%i (unused)\n",n);
	n = buffer_read_ubyte(b);
	printf("%i (unused)\n",n);
	n = buffer_read_ubyte(b);
	printf("%i (unused)\n",n);
      } else {
	printf("unknown NPCC/NPDT size %i\n",size);
	exit(-1);
      }
    } else if (strcmp(s,"NPCO") == 0) {
      n = buffer_read_int(b);
      printf("NPCC/NPCO %i\n",n);
      n = buffer_read_int(b);
      printf("Item Count %i\n",n);
      s2 = buffer_read_nstring(b,32);
      printf("Item Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"XIDX") == 0) { // Savefile only, not NPC_.
      n = buffer_read_int(b);
      printf("NPCC/XIDX %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"XHLT") == 0) { // Savefile only, not NPC_.
      n = buffer_read_int(b);
      printf("NPCC/XHLT %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_int(b);
      printf("NPCC/SCRI %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Script \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SLCS") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("NPCC/SLCS %i\n",n);
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
      printf("NPCC/SLSD %i\n",n);
      printf("data given by numslcs1:\n");
      for (i = 0; i < numslcs1; i++) {
	n = buffer_read_short(b);
	printf("%i\n",n);
      }
    } else if (strcmp(s,"SLLD") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("NPCC/SLLD %i\n",n);
      printf("data given by numslcs2:\n");
      for (i = 0; i < numslcs2; i++) {
	n = buffer_read_int(b);
	printf("%i\n",n);
      }
    } else if (strcmp(s,"SLFD") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("NPCC/SLFD %i\n",n);
      printf("data given by numslcs3:\n");
      for (i = 0; i < numslcs3; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"XCHG") == 0) { // Savefile only, not NPC_.
      n = buffer_read_int(b);
      printf("NPCC/XCHG %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"WIDX") == 0) { // Savefile only, not NPC_.
      n = buffer_read_int(b);
      printf("NPCC/WIDX %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"AI_T") == 0) {
      n = buffer_read_int(b);
      printf("NPCC/AI_T %i\n",n);
      f = buffer_read_float(b);
      printf("Location X %f\n",f);
      f = buffer_read_float(b);
      printf("Location Y %f\n",f);
      f = buffer_read_float(b);
      printf("Location Z %f\n",f);
      n = buffer_read_int(b);
      printf("%i (ai_tunknown)\n",n);
    } else if (strcmp(s,"AI_E") == 0) {
      n = buffer_read_int(b);
      printf("CREA/AI_E %i\n",n);
      f = buffer_read_float(b);
      printf("Specific Point X %f\n",f);
      f = buffer_read_float(b);
      printf("Specific Point Y %f\n",f);
      f = buffer_read_float(b);
      printf("Specific Point Z %f\n",f);

      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);

      s2 = buffer_read_nstring(b,7);
      printf("%s\n",s2);
      free(s2);

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

      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);

      n = buffer_read_ushort(b);
      printf("%i\n",n);
      n = buffer_read_ushort(b);
      printf("%i\n",n);
    } else if (strcmp(s,"AI_W") == 0) {
      n = buffer_read_int(b);
      printf("NPCC/AI_W %i\n",n);
      n = buffer_read_ushort(b);
      printf("Distance %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Duration (in hours) %i %% 0-24\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unknown)\n",n);
      n = buffer_read_ubyte(b);
      printf("Time of Day (??:00) %i %% 0-23\n",n);
      n = buffer_read_ubyte(b);
      printf("Idle Chances Idle 2 %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Idle Chances Idle 3 %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Idle Chances Idle 4 %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Idle Chances Idle 5 %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Idle Chances Idle 6 %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Idle Chances Idle 7 %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Idle Chances Idle 8 %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Idle Chances Idle 9 %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unknown)\n",n);
    } else if (strcmp(s,"AI_F") == 0) {
      n = buffer_read_int(b);
      printf("NPCC/AI_F %i\n",n);
      f = buffer_read_float(b);
      printf("Specific Point X %f\n",f);
      f = buffer_read_float(b);
      printf("Specific Point Y %f\n",f);
      f = buffer_read_float(b);
      printf("Specific Point Z %f\n",f);

      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);

      s2 = buffer_read_nstring(b,16);
      printf("Target \"%s\"\n",s2);
      free(s2);

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

      n = buffer_read_ushort(b);
      printf("%i\n",n);
      n = buffer_read_ushort(b);
      printf("%i\n",n);
    } else if (strcmp(s,"XSOL") == 0) {
      n = buffer_read_int(b);
      printf("NPCC/XSOL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"CNDT") == 0) {
      n = buffer_read_int(b);
      printf("NPCC/CNDT %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else {
      printf("Unknown chunk name\n");
      printhexdump(b,-4,120);
      exit(-1);
    }
    free(s);
  }

  printf("End of NPCC\n");

  return -1;
}
