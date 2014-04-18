
int parsebuffer_fact(void *b)
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
      printf("FACT/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("FACT/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"XNAM") == 0) {
      n = buffer_read_short(b);
      printf("FACT/XNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Opposing/Affiliated Faction FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Disposition Modifier %i\n",n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("FACT/DATA %i\n",n);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Hidden from PC\n");
      printf("       ^Evil\n");
      printf("      ^Special Combat\n");
    } else if (strcmp(s,"CNAM") == 0) {
      n = buffer_read_short(b);
      printf("FACT/CNAM %i\n",n);
      f = buffer_read_float(b);
      printf("Crime Gold Multiplier %f\n",f);
    } else if (strcmp(s,"RNAM") == 0) {
      n = buffer_read_short(b);
      printf("FACT/RNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Rank Data Rank %i\n",n);
    } else if (strcmp(s,"MNAM") == 0) {
      n = buffer_read_short(b);
      printf("FACT/MNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Rank Data Male Title \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_short(b);
      printf("FACT/FNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Rank Data Female Title \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"INAM") == 0) {
      n = buffer_read_short(b);
      printf("FACT/INAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Rank Insignia image file \"%s\"\n",s2);
      free(s2);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of FACT\n");

  return -1;
}
