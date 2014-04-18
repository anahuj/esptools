
int parsebuffer_keym(void *b)
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
      printf("KEYM/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("KEYM/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("KEYM/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Inventory image \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("KEYM/DATA %i\n",n);
      n = buffer_read_int(b);
      printf("Value %i\n",n);
      f = buffer_read_float(b);
      printf("Weight %f\n",f);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_short(b);
      printf("KEYM/SCRI %i\n",n);
      n = buffer_read_int(b);
      printf("Script FormID %i\n",n);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("KEYM/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("KEYM/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("KEYM/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"OBND") == 0) { // F
      n = buffer_read_short(b);
      printf("KEYM/OBND %i\n",n);
      parse_obnd(b);
    } else if (strcmp(s,"MICO") == 0) { // F
      n = buffer_read_short(b);
      printf("KEYM/MICO %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Message Icon \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"YNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("KEYM/YNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Pickup Sound FormID %i\n",n);
    } else if (strcmp(s,"ZNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("KEYM/ZNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Putdown Sound FormID %i\n",n);
    } else if (strcmp(s,"DEST") == 0) { // F
      n = buffer_read_short(b);
      printf("KEYM/DEST %i\n",n);
      parse_dest(b);
    } else if (strcmp(s,"DSTD") == 0) { // F
      n = buffer_read_short(b);
      printf("KEYM/DSTD %i\n",n);
      parse_dstd(b);
    } else if (strcmp(s,"DSTF") == 0) { // F
      n = buffer_read_short(b);
      printf("KEYM/DSTF %i\n",n);
      // Empty.
    } else if (strcmp(s,"DMDL") == 0) { // F
      n = buffer_read_short(b);
      printf("KEYM/DMDL %i\n",n);
      parse_dmdl(b,n);
    } else if (strcmp(s,"DMDT") == 0) { // F
      n = buffer_read_short(b);
      printf("KEYM/DMDT %i\n",n);
      parse_dmdt(b,n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of KEYM\n");

  return -1;
}
