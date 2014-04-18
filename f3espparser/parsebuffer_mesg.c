
int parsebuffer_mesg(void *b)
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
      printf("MESG/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("MESG/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Title \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DESC") == 0) {
      n = buffer_read_short(b);
      printf("MESG/DESC %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Message Text \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"INAM") == 0) {
      n = buffer_read_short(b);
      printf("MESG/INAM %i\n",n);
      n = buffer_read_int(b);
      printf("Icon FormID %i\n",n);
    } else if (strcmp(s,"NAM0") == 0) {
      n = buffer_read_short(b);
      printf("MESG/NAM0 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"NAM1") == 0) {
      n = buffer_read_short(b);
      printf("MESG/NAM1 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"NAM2") == 0) {
      n = buffer_read_short(b);
      printf("MESG/NAM2 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"NAM3") == 0) {
      n = buffer_read_short(b);
      printf("MESG/NAM3 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"NAM4") == 0) {
      n = buffer_read_short(b);
      printf("MESG/NAM4 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"NAM5") == 0) {
      n = buffer_read_short(b);
      printf("MESG/NAM5 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"NAM6") == 0) {
      n = buffer_read_short(b);
      printf("MESG/NAM6 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"NAM7") == 0) {
      n = buffer_read_short(b);
      printf("MESG/NAM7 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"NAM8") == 0) {
      n = buffer_read_short(b);
      printf("MESG/NAM8 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"NAM9") == 0) {
      n = buffer_read_short(b);
      printf("MESG/NAM9 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"DNAM") == 0) {
      n = buffer_read_short(b);
      printf("MESG/DNAM %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Message Box\n");
      printf("       ^Auto-display\n");
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"ITXT") == 0) {
      n = buffer_read_short(b);
      printf("MESG/ITXT %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Item Text \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"TNAM") == 0) {
      n = buffer_read_short(b);
      printf("MESG/TNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Display Time %i\n",n);
    } else if (strcmp(s,"CTDA") == 0) {
      n = buffer_read_short(b);
      printf("MESG/CTDA %i\n",n);
      parse_ctda(b,n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of MESG\n");

  return -1;
}
