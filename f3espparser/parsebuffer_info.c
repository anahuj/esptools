
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
      printf("Dialogue Type %i %% 0 Topics 1 Conversation 2 Combat 3 Persuasion 4 Detection 5 Service 6 Misc 7 Radio\n",n);
      if (size == 2) { // Not in Fallout3.esm.
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
	printf("      ^Say Once\n");
	printf("     ^Run Immediately\n");
	printf("   ^Info Refusal\n");
	printf("  ^Random End\n");
	printf(" ^Run For Rumors\n");
	printf("^Speech Challenge\n");
      }
      if (size == 4) {
	n = buffer_read_ubyte(b);
	printf("Next Speaker %i %% 0 Target 1 Self 2 Either\n",n);
	n = buffer_read_ubyte(b);
	printflags8(n);
	//      0000,0000
	printf("        ^Goodbye\n");
	printf("       ^Random\n");
	printf("      ^Say Once\n");
	printf("     ^Run Immediately\n");
	printf("   ^Info Refusal\n");
	printf("  ^Random End\n");
	printf(" ^Run For Rumors\n");
	printf("^Speech Challenge\n");
	n = buffer_read_ubyte(b);
	printflags8(n);
	//      0000,0000
	printf("        ^Say Once a Day\n");
	printf("       ^Always Darken\n");
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
    } else if (strcmp(s,"TRDT") == 0) { // F
      n = buffer_read_short(b);
      printf("INFO/TRDT %i\n",n);
      size = n;
      n = buffer_read_int(b);
      printf("Emotion Type %i %% 0 Neutral 1 Anger 2 Disgust 3 Fear 4 Sad 5 Happy 6 Surprise 7 Pained\n",n);
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
      // F
      if (size >= 20) {
	n = buffer_read_int(b);
	printf("Sound File FormID %i\n",n);
      }
      if (size >= 24) {
	n = buffer_read_ubyte(b);
	printf("Use Emotion Animation %i %% 0 Disabled 1 Enabled\n",n);
	n = buffer_read_ubyte(b);
	printf("%i (unused)\n",n);
	n = buffer_read_ubyte(b);
	printf("%i (unused)\n",n);
	n = buffer_read_ubyte(b);
	printf("%i (unused)\n",n);
      }
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
    } else if (strcmp(s,"NAM3") == 0) { // F
      n = buffer_read_short(b);
      printf("INFO/NAM3 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Edits \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"CTDA") == 0) {
      n = buffer_read_short(b);
      printf("INFO/CTDA %i\n",n);
      parse_ctda(b,n);
#if 0
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
#endif
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
    } else if (strcmp(s,"SCDA") == 0) {
      n = buffer_read_short(b);
      printf("INFO/SCDA %i\n",n);
      parse_scda(b,n);
    } else if (strcmp(s,"SCTX") == 0) {
      n = buffer_read_short(b);
      printf("INFO/SCTX %i\n",n);
      parse_sctx(b,n);
#if 0
      s2 = buffer_read_nstring(b,n);
      printf("Result Script \"%s\"\n",s2);
      free(s2);
#endif
    } else if (strcmp(s,"SCRO") == 0) {
      n = buffer_read_short(b);
      printf("INFO/SCRO %i\n",n);
      parse_scro(b);
#if 0
      n = buffer_read_int(b);
      printf("Script Object FormID %i\n",n);
#endif
    } else if (strcmp(s,"CTDT") == 0) {
      n = buffer_read_short(b);
      printf("INFO/CTDT %i\n",n);
      parse_ctdt(b);
#if 0
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
#endif
#if 0
      // Not in Fallout3.esm.
    } else if (strcmp(s,"SCHD") == 0) {
      n = buffer_read_short(b);
      printf("INFO/SCHD %i\n",n);
      buffer_skip_bytes(b,n);
      printf("skipping bytes\n");
#endif
    } else if (strcmp(s,"NEXT") == 0) { // F
      n = buffer_read_short(b);
      printf("INFO/NEXT %i\n",n);
      // Empty.
    } else if (strcmp(s,"SNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("INFO/SNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Idle Animations Speaker FormID %i\n",n);
    } else if (strcmp(s,"LNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("INFO/LNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Idle Animations Listener FormID %i\n",n);
    } else if (strcmp(s,"RNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("INFO/RNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Prompt \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("INFO/DNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Speech Challenge Difficulty %i %% 1 Very Easy(10) 2 Easy(40) 3 Average(55) 4 Hard(70) 5 Very Hard(80)\n",n);
    } else if (strcmp(s,"KNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("INFO/KNAM %i\n",n);
      n = buffer_read_int(b);
      printf("AV/Perk FormID %i\n",n);
    } else if (strcmp(s,"ANAM") == 0) { // F
      n = buffer_read_short(b);
      printf("INFO/ANAM %i\n",n);
      n = buffer_read_int(b);
      printf("Speaker FormID %i\n",n);
    } else if (strcmp(s,"SNDD") == 0) { // F
      n = buffer_read_short(b);
      printf("INFO/SNDD %i\n",n);
      n = buffer_read_int(b);
      printf("Sound File FormID %i\n",n);
    } else if (strcmp(s,"SLSD") == 0) {
      n = buffer_read_short(b);
      printf("INFO/SLSD %i\n",n);
      parse_slsd(b);
    } else if (strcmp(s,"SCVR") == 0) {
      n = buffer_read_short(b);
      printf("INFO/SCVR %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Variable name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SCRV") == 0) {
      n = buffer_read_short(b);
      printf("INFO/SCRV %i\n",n);
      n = buffer_read_int(b);
      printf("Ref variable index %i\n",n);
    } else if (strcmp(s,"TPIC") == 0) {
      n = buffer_read_short(b);
      printf("INFO/TPIC %i\n",n);
      n = buffer_read_int(b);
      printf("XXXX TPIC formid 0x%.8x (%i)\n",n,n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of INFO\n");

  return -1;
}
