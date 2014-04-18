
int parsebuffer_term(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int size;
  int num;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("TERM/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("TERM/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DESC") == 0) {
      n = buffer_read_short(b);
      printf("TERM/DESC %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Welcome Text \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("TERM/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("TERM/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_short(b);
      printf("TERM/SNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Looping Sound FormID %i\n",n);
    } else if (strcmp(s,"PNAM") == 0) {
      n = buffer_read_short(b);
      printf("TERM/PNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Password FormID %i\n",n);
    } else if (strcmp(s,"DNAM") == 0) {
      n = buffer_read_short(b);
      printf("TERM/DNAM %i\n",n);
      size = n;
      n = buffer_read_ubyte(b);
      printf("Base Hack Difficulty %i %% 0 Very Easy / Unlocked 1 Easy 2 Average 3 Hard 4 Very Hard 5 Requires Key\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Leveled\n");
      printf("       ^Unlocked (see Base Hack Difficulty)\n");
      printf("      ^Alternate Colors\n");
      printf("     ^Hide when displaying image\n");
      n = buffer_read_ubyte(b);
      printf("Server Type %i %% Server number is Value + 1\n",n);
      if (size == 4) {
	n = buffer_read_ubyte(b);
	printf("%i unknown, 0 in Fallout3.esm\n",n);
      }
    } else if (strcmp(s,"ITXT") == 0) {
      n = buffer_read_short(b);
      printf("TERM/ITXT %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Item Text \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"RNAM") == 0) {
      n = buffer_read_short(b);
      printf("TERM/RNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Result Text \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ANAM") == 0) {
      n = buffer_read_short(b);
      printf("TERM/ANAM %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Display Note Add\n");
      printf("       ^Force Redraw\n");
    } else if (strcmp(s,"SCHR") == 0) {
      n = buffer_read_short(b);
      printf("TERM/SCHR %i\n",n);
      parse_schr(b);
    } else if (strcmp(s,"SCDA") == 0) {
      n = buffer_read_short(b);
      printf("TERM/SCDA %i\n",n);
      parse_scda(b,n);
    } else if (strcmp(s,"SCTX") == 0) {
      n = buffer_read_short(b);
      printf("TERM/SCTX %i\n",n);
      parse_sctx(b,n);
    } else if (strcmp(s,"SLSD") == 0) {
      n = buffer_read_short(b);
      printf("TERM/SLSD %i\n",n);
      parse_slsd(b);
    } else if (strcmp(s,"SCVR") == 0) {
      n = buffer_read_short(b);
      printf("TERM/SCVR %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"SCRV") == 0) {
      n = buffer_read_short(b);
      printf("TERM/SCRV %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"OBND") == 0) {
      n = buffer_read_short(b);
      printf("TERM/OBND %i\n",n);
      parse_obnd(b);
    } else if (strcmp(s,"CTDA") == 0) {
      n = buffer_read_short(b);
      printf("TERM/CTDA %i\n",n);
      parse_ctda(b,n);
    } else if (strcmp(s,"INAM") == 0) {
      n = buffer_read_short(b);
      printf("TERM/INAM %i\n",n);
      n = buffer_read_int(b);
      printf("Display Note FormID %i\n",n);
    } else if (strcmp(s,"SCRO") == 0) {
      n = buffer_read_short(b);
      printf("TERM/SCRO %i\n",n);
      parse_scro(b);
    } else if (strcmp(s,"TNAM") == 0) {
      n = buffer_read_short(b);
      printf("TERM/TNAM %i\n",n);
      n = buffer_read_int(b);
      printf("SubMenu FormID %i\n",n);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_short(b);
      printf("TERM/SCRI %i\n",n);
      n = buffer_read_int(b);
      printf("Script FormID %i\n",n);
    } else if (strcmp(s,"DEST") == 0) { // F
      n = buffer_read_short(b);
      printf("TERM/DEST %i\n",n);
      parse_dest(b);
    } else if (strcmp(s,"DSTD") == 0) { // F
      n = buffer_read_short(b);
      printf("TERM/DSTD %i\n",n);
      parse_dstd(b);
    } else if (strcmp(s,"DSTF") == 0) { // F
      n = buffer_read_short(b);
      printf("TERM/DSTF %i\n",n);
      // Empty.
    } else if (strcmp(s,"DMDL") == 0) { // F
      n = buffer_read_short(b);
      printf("TERM/DMDL %i\n",n);
      parse_dmdl(b,n);
    } else if (strcmp(s,"DMDT") == 0) { // F
      n = buffer_read_short(b);
      printf("TERM/DMDT %i\n",n);
      parse_dmdt(b,n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of TERM\n");

  return -1;
}
