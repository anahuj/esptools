
int parsebuffer_door(void *b)
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
      printf("DOOR/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("DOOR/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("DOOR/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("DOOR/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("DOOR/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_short(b);
      printf("DOOR/SCRI %i\n",n);
      n = buffer_read_int(b);
      printf("Script FormID %i\n",n);
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_short(b);
      printf("DOOR/SNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Open Sound FormID %i\n",n);
    } else if (strcmp(s,"ANAM") == 0) {
      n = buffer_read_short(b);
      printf("DOOR/ANAM %i\n",n);
      n = buffer_read_int(b);
      printf("Close Sound FormID %i\n",n);
    } else if (strcmp(s,"BNAM") == 0) {
      n = buffer_read_short(b);
      printf("DOOR/BNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Loop Sound FormID %i\n",n);
    } else if (strcmp(s,"TNAM") == 0) {
      n = buffer_read_short(b);
      printf("DOOR/TNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Teleport FormID %i\n",n);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_short(b);
      printf("DOOR/FNAM %i\n",n);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("       ^Automatic Door\n");
      printf("      ^Hidden\n");
      printf("     ^Minimal Use\n");
      printf("   ^Sliding Door\n");
    } else if (strcmp(s,"OBND") == 0) { // F
      n = buffer_read_short(b);
      printf("DOOR/OBND %i\n",n);
      parse_obnd(b);
    } else if (strcmp(s,"MODS") == 0) { // F
      n = buffer_read_short(b);
      printf("DOOR/MODS %i\n",n);
      parse_mods(b);
#if 0
      n = buffer_read_int(b);
      printf("Number of New Textures %i\n",n);
      num = n;
      for (i = 0; i < num; i++) {
	s2 = buffer_read_intstring(b);
	printf("3D Name \"%s\" (in NIF)\n",s2);
	free(s2);
	n = buffer_read_int(b);
	printf("New Texture FormID %i\n",n);
	n = buffer_read_int(b);
	printf("3D Index %i\n",n);
      }
#endif
    } else if (strcmp(s,"DEST") == 0) {
      n = buffer_read_short(b);
      printf("DOOR/DEST %i\n",n);
      parse_dest(b);
    } else if (strcmp(s,"DSTD") == 0) {
      n = buffer_read_short(b);
      printf("DOOR/DSTD %i\n",n);
      parse_dstd(b);
    } else if (strcmp(s,"DSTF") == 0) {
      n = buffer_read_short(b);
      printf("DOOR/DSTF %i\n",n);
      // Empty.
    } else if (strcmp(s,"DMDL") == 0) { // F
      n = buffer_read_short(b);
      printf("DOOR/DMDL %i\n",n);
      parse_dmdl(b,n);
    } else if (strcmp(s,"DMDT") == 0) { // F
      n = buffer_read_short(b);
      printf("DOOR/DMDT %i\n",n);
      parse_dmdt(b,n);
#if 0
    } else if (strcmp(s,"DMDL") == 0) { // F
      n = buffer_read_short(b);
      printf("DOOR/DMDL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"DMDT") == 0) { // F
      n = buffer_read_short(b);
      printf("DOOR/DMDT %i\n",n);
      parse_modt(b,n); // XXXX we use parse_modt now
#endif
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of DOOR\n");

  return -1;
}
