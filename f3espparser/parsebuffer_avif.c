
int parsebuffer_avif(void *b)
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
      printf("AVIF/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("AVIF/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("In-Game Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DESC") == 0) {
      n = buffer_read_short(b);
      printf("AVIF/DESC %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Description \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ANAM") == 0) {
      n = buffer_read_short(b);
      printf("AVIF/ANAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Abbreviation \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("AVIF/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Image \"%s\"\n",s2);
      free(s2);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of AVIF\n");

  return -1;
}
