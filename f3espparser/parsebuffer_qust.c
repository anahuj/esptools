
int parsebuffer_qust(void *b)
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
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("QUST/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("QUST/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Quest Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ICON") == 0) { // Not used in F3 but field exists.
      n = buffer_read_short(b);
      printf("QUST/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Quest Icon \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"CNAM") == 0) {
      n = buffer_read_short(b);
      printf("QUST/CNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Log Entry \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("QUST/DATA %i\n",n);
      size = n;
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Start Game Enabled\n");
      printf("      ^Script Processing Delay Default\n");
      printf("     ^Allow repeated stages\n");
      printf("   ^Allow repeated conversation topics\n");
      n = buffer_read_ubyte(b);
      printf("Priority %i\n",n);
      if (size >= 8) {
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
#if 1
	f = buffer_read_float(b);
	printf("Script Processing Delay %f\n",f);
#else
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
#endif
      }
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_short(b);
      printf("QUST/SCRI %i\n",n);
      n = buffer_read_int(b);
      printf("Script FormID %i\n",n);
    } else if (strcmp(s,"CTDA") == 0) {
      n = buffer_read_short(b);
      printf("QUST/CTDA %i\n",n);
      parse_ctda(b,n);
    } else if (strcmp(s,"INDX") == 0) {
      n = buffer_read_short(b);
      printf("QUST/INDX %i\n",n);
      n = buffer_read_short(b);
      printf("Quest Stage Index %i\n",n);
    } else if (strcmp(s,"QSDT") == 0) {
      n = buffer_read_short(b);
      printf("QUST/QSDT %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Complete Quest\n");
      printf("       ^Fail Quest\n");
    } else if (strcmp(s,"SCHR") == 0) {
      n = buffer_read_short(b);
      printf("QUST/SCHR %i\n",n);
      parse_schr(b);
    } else if (strcmp(s,"SCDA") == 0) {
      n = buffer_read_short(b);
      printf("QUST/SCDA %i\n",n);
      parse_scda(b,n);
    } else if (strcmp(s,"SCTX") == 0) {
      n = buffer_read_short(b);
      printf("QUST/SCTX %i\n",n);
      parse_sctx(b,n);
    } else if (strcmp(s,"SCRO") == 0) {
      n = buffer_read_short(b);
      printf("QUST/SCRO %i\n",n);
      parse_scro(b);
    } else if (strcmp(s,"QSTA") == 0) {
      n = buffer_read_short(b);
      printf("QUST/QSTA %i\n",n);
      n = buffer_read_int(b);
      printf("Target Ref FormID %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Compass Markers Ignore Locks\n");
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"QOBJ") == 0) { // F
      n = buffer_read_short(b);
      printf("QUST/QOBJ %i\n",n);
      n = buffer_read_int(b);
      printf("Index %i\n",n);
    } else if (strcmp(s,"NNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("QUST/NNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Display Text \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"NAM0") == 0) { // F
      n = buffer_read_short(b);
      printf("QUST/NAM0 %i\n",n);
      n = buffer_read_int(b);
      printf("Next quest FormID %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of QUST\n");

  return -1;
}
