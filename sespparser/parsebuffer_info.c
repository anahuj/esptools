
int parsebuffer_info(void *b)
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
    if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("INFO/DATA %i\n",n);
      size = n;
      n = buffer_read_ubyte(b);
      printf("Dialogue Type %i %% 0 Topics 1 Conversation 2 Combat 3 Persuasion 4 Detection 5 Service 6 Misc\n",n);
      if (size == 2) {
	n = buffer_read_ubyte(b);
	printf("%i\n",n); // Flags?
      }
      if (size == 3) {
	n = buffer_read_ubyte(b);
	printf("Next Speaker %i %% 0 Target 1 Self 2 Either\n",n);
	n = buffer_read_ubyte(b);
	printflags8(n);
	//      0000,0000
	printf("        ^Goodbye\n");
	printf("       ^Random\n");
	printf("  ^----^Random End\n");
	printf("      ^Say Once\n");
	printf("     ^Run Immediately\n");
	printf("   ^Info Refusal\n");
	printf(" ^Run For Rumors ??\n");
      }
#if 0
      // 3
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      flags = buffer_read_ushort(b);
      printflags(flags);
#endif
    } else if (strcmp(s,"QSTI") == 0) {
      n = buffer_read_short(b);
      printf("INFO/QSTI %i\n",n);
      n = buffer_read_int(b);
      printf("Quest FormID %i\n",n);
    } else if (strcmp(s,"PNAM") == 0) {
      // Not in Oblivion.esm. But is in esp which modified INFO. 
      n = buffer_read_short(b);
      printf("INFO/PNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Previous INFO FormID %i ????\n",n);
    } else if (strcmp(s,"TRDT") == 0) {
      n = buffer_read_short(b);
      printf("INFO/TRDT %i\n",n);
      n = buffer_read_int(b);
      printf("Emotion Type %i %% 0 Neutral 1 Anger 2 Disgust 3 ?? 4 Sad 5 Happy 6 Surprise\n",n);
      n = buffer_read_int(b);
      printf("Emotion Value %i\n",n);
      n = buffer_read_int(b);
      printf("%i unknown\n",n);
      n = buffer_read_ubyte(b);
      printf("Response Choice Number %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"NAM1") == 0) {
      n = buffer_read_short(b);
      printf("INFO/NAM1 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Response Text \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"NAM2") == 0) {
      n = buffer_read_short(b);
      printf("INFO/NAM2 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Script Notes \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"CTDA") == 0) {
      n = buffer_read_short(b);
      printf("INFO/CTDA %i\n",n);
      parse_ctda(b);
    } else if (strcmp(s,"TCLT") == 0) {
      n = buffer_read_short(b);
      printf("INFO/TCLT %i\n",n);
      n = buffer_read_int(b);
      printf("Choices/Link To FormID %i\n",n);
    } else if (strcmp(s,"TCLF") == 0) {
      n = buffer_read_short(b);
      printf("INFO/TCLF %i\n",n);
      n = buffer_read_int(b);
      printf("Link From FormID %i\n",n);
    } else if (strcmp(s,"NAME") == 0) {
      n = buffer_read_short(b);
      printf("INFO/NAME %i\n",n);
      n = buffer_read_int(b);
      printf("Add Topics FormID %i\n",n);
    } else if (strcmp(s,"SCHR") == 0) {
      n = buffer_read_short(b);
      printf("INFO/SCHR %i\n",n);
      parse_schr(b);
#if 0
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("SCDA size %i ??\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
#endif
    } else if (strcmp(s,"SCDA") == 0) {
      n = buffer_read_short(b);
      printf("INFO/SCDA %i\n",n);
      parse_scda(b,n);
    } else if (strcmp(s,"SCTX") == 0) {
      n = buffer_read_short(b);
      printf("INFO/SCTX %i\n",n);
      parse_sctx(b,n);
    } else if (strcmp(s,"SCRO") == 0) {
      n = buffer_read_short(b);
      printf("INFO/SCRO %i\n",n);
      parse_scro(b);
    } else if (strcmp(s,"CTDT") == 0) {
      n = buffer_read_short(b);
      printf("INFO/CTDT %i\n",n);
      parse_ctdt(b);
    } else if (strcmp(s,"SCHD") == 0) {
      n = buffer_read_short(b);
      printf("INFO/SCHD %i\n",n);
      buffer_skip_bytes(b,n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of INFO\n");

  return -1;
}
