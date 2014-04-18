
int parsebuffer_door(void *b)
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
      printf("%s\n",s2);
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
      printf("        ^Oblivion Gate\n");
      printf("       ^Automatic Door\n");
      printf("      ^Hidden\n");
      printf("     ^Minimal Use\n");
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of DOOR\n");

  return -1;
}
