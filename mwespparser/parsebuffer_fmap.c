
int parsebuffer_fmap(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int size;
  unsigned char *buf;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"NAME") == 0) {
      n = buffer_read_int(b);
      printf("FMAP/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"MAPH") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("FMAP/MAPH %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n); // x/ysize of the map image; == 512 so far
      n = buffer_read_int(b);
      printf("%i\n",n); // Image type?? 9 == RGB
    } else if (strcmp(s,"MAPD") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("FMAP/MAPD %i\n",n);
      buf = buffer_getbuf_atloc(b);
      printf("Raw 512x512 map saved to fmapmapd.rgb\n");
      buffer2file(buf,n,"fmapmapd.rgb");
      buffer_skip_bytes(b,n);
    } else {
      printf("Unknown chunk name\n");
      printhexdump(b,-4,120);
      exit(-1);
    }
    free(s);
  }

  printf("End of FMAP\n");

  return -1;
}
