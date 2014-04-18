
int parsebuffer_ipds(void *b)
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
      printf("IPDS/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("IPDS/DATA %i\n",n);
      size = n;
      if (size >= 36) {
	n = buffer_read_int(b);
	printf("Stone FormID %i\n",n);
	n = buffer_read_int(b);
	printf("Dirt FormID %i\n",n);
	n = buffer_read_int(b);
	printf("Grass FormID %i\n",n);
	n = buffer_read_int(b);
	printf("Glass FormID %i\n",n);
	n = buffer_read_int(b);
	printf("Metal FormID %i\n",n);
	n = buffer_read_int(b);
	printf("Wood FormID %i\n",n);
	n = buffer_read_int(b);
	printf("Organic FormID %i\n",n);
	n = buffer_read_int(b);
	printf("Cloth FormID %i\n",n);
	n = buffer_read_int(b);
	printf("Water FormID %i\n",n);
      }
      if (size >= 40) {
	n = buffer_read_int(b);
	printf("Hollow Metal FormID %i\n",n);
      }
      if (size >= 48) {
	n = buffer_read_int(b);
	printf("Organic Bug FormID %i\n",n);
	n = buffer_read_int(b);
	printf("Organic Glow FormID %i\n",n);
      }
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of IPDS\n");

  return -1;
}
