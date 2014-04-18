
int parsebuffer_cpth(void *b)
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
      printf("CPTH/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_short(b);
      printf("CPTH/SNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Camera Shot FormID %i\n",n);
    } else if (strcmp(s,"CTDA") == 0) {
      n = buffer_read_short(b);
      printf("CPTH/CTDA %i\n",n);
      parse_ctda(b,n);
    } else if (strcmp(s,"ANAM") == 0) {
      n = buffer_read_short(b);
      printf("CPTH/ANAM %i\n",n);
      n = buffer_read_int(b);
      printf("Parent Camera Path FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Previous Camera Path FormID %i\n",n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("CPTH/DATA %i\n",n);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("       ^^Camera Zoom %i %% 0 Default 1 Disable 2 Shot List\n",0x03 & n);
      printf("^~Must have Camera Shots\n");
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of CPTH\n");

  return -1;
}
