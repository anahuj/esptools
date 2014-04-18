
int parsebuffer_gmst(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int gmstformat;

  gmstformat = -1;
  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("GMST/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      if (s2[0] == 's') {
	gmstformat = 1;
      } else if (s2[0] == 'i') {
	gmstformat = 2;
      } else if (s2[0] == 'f') {
	gmstformat = 3;
      } else {
	printf("Unknown gmst format\n");
	gmstformat = 4;
      }
      free(s2);
    } else if (strcmp(s,"NAME") == 0) {
      n = buffer_read_int(b);
      printf("GMST/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      if (s2[0] == 's') {
	gmstformat = 1;
      } else if (s2[0] == 'i') {
	gmstformat = 2;
      } else if (s2[0] == 'f') {
	gmstformat = 3;
      } else {
	printf("Unknown gmst format\n");
	gmstformat = 4;
      }
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("GMST/DATA %i\n",n);
      switch (gmstformat) {
      case -1:
	printf("gmst format not known yet\n");
	break;
      case 1:
	s2 = buffer_read_nstring(b,n);
	printf("%s\n",s2);
	free(s2);
	break;
      case 2:
	m = buffer_read_int(b);
	printf("%i\n",m);
	break;
      case 3:
	f = buffer_read_float(b);
	printf("%f\n",f);
	break;
      case 4:
	printf("Cannot print gmst data because of the unknown gmst format\n");
	buffer_skip_bytes(b,n);
	break;
      }
    } else if (strcmp(s,"STRV") == 0) {
      n = buffer_read_int(b);
      printf("GMST/STRV %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
    } else if (strcmp(s,"FLTV") == 0) {
      n = buffer_read_int(b);
      printf("GMST/FLTV %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"INTV") == 0) {
      n = buffer_read_int(b);
      printf("GMST/INTV %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of GMST\n");

  return -1;
}
