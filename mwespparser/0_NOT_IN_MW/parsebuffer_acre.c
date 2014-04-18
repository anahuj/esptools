
int parsebuffer_acre(void *b)
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
      printf("ACRE/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"NAME") == 0) {
      n = buffer_read_short(b);
      printf("ACRE/NAME %i\n",n);
      n = buffer_read_int(b);
      printf("Base Object FormID %i\n",n);
    } else if (strcmp(s,"XRGD") == 0) {
      n = buffer_read_short(b);
      printf("ACRE/XRGD %i\n",n);
      m = n/28;
      for (i = 0; i < m; i++) {
	n = buffer_read_byte(b);
	printf("%i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
	f = buffer_read_float(b);
	printf("%f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("ACRE/DATA %i\n",n);
      f = buffer_read_float(b);
      printf("Position X %f\n",f);
      f = buffer_read_float(b);
      printf("Position Y %f\n",f);
      f = buffer_read_float(b);
      printf("Position Z %f\n",f);
      f = buffer_read_float(b);
      printf("Rotation X %f\n",f);
      f = buffer_read_float(b);
      printf("Rotation Y %f\n",f);
      f = buffer_read_float(b);
      printf("Rotation Z %f\n",f);
    } else if (strcmp(s,"XSCL") == 0) {
      n = buffer_read_short(b);
      printf("ACRE/XSCL %i\n",n);
      f = buffer_read_float(b);
      printf("Scale %f\n",f);
    } else if (strcmp(s,"XOWN") == 0) {
      n = buffer_read_short(b);
      printf("ACRE/XOWN %i\n",n);
      n = buffer_read_int(b);
      printf("Owner FormID %i\n",n);
    } else if (strcmp(s,"XESP") == 0) {
      n = buffer_read_short(b);
      printf("ACRE/XESP %i\n",n);
      // buffer_skip_bytes(b,n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of ACRE\n");

  return -1;
}
