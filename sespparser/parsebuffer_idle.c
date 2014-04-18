
int parsebuffer_idle(void *b)
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
      printf("IDLE/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"ANAM") == 0) {
      n = buffer_read_short(b);
      printf("IDLE/ANAM %i\n",n);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      // printf("      ^^^ 100 Special Idle 101 Whole Body\n");
      printf("      ^^^Animation Group Section %i %% 0 Lower Body 1 Left Arm 2 Left Hand 3 Right Arm 4 Special Idle 5 Whole Body 6 Upper Body\n",0x7f & n); // XXXX 0x07?
      printf("^~Must return a file\n");
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("IDLE/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("IDLE/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"CTDA") == 0) {
      n = buffer_read_short(b);
      printf("IDLE/CTDA %i\n",n);
      parse_ctda(b);
    } else if (strcmp(s,"CTDT") == 0) {
      n = buffer_read_short(b);
      printf("IDLE/CTDT %i\n",n);
      parse_ctdt(b);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("IDLE/DATA %i\n",n);
      n = buffer_read_int(b);
      printf("Hierarchy Parent IDLE FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Hierarchy Previous IDLE FormID %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of IDLE\n");

  return -1;
}
