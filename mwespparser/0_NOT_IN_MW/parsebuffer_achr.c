
int parsebuffer_achr(void *b)
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
      printf("ACHR/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"NAME") == 0) {
      n = buffer_read_short(b);
      printf("ACHR/NAME %i\n",n);
      n = buffer_read_int(b);
      printf("Base Object FormID %i\n",n);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("ACHR/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"XESP") == 0) {
      n = buffer_read_short(b);
      printf("ACHR/XESP %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"XLOD") == 0) {
      n = buffer_read_short(b);
      printf("ACHR/XLOD %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"XHRS") == 0) {
      n = buffer_read_short(b);
      printf("ACHR/XHRS %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"XMRC") == 0) {
      n = buffer_read_short(b);
      printf("ACHR/XMRC %i\n",n);
      n = buffer_read_int(b);
      printf("Merchant's Container FormID %i\n",n);
    } else if (strcmp(s,"XRGD") == 0) {
      n = buffer_read_short(b);
      printf("ACHR/XRGD %i\n",n);
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
    } else if (strcmp(s,"XSCL") == 0) {
      n = buffer_read_short(b);
      printf("ACHR/XSCL %i\n",n);
      f = buffer_read_float(b);
      printf("Scale %f\n",f);
    } else if (strcmp(s,"XPCI") == 0) {
      n = buffer_read_short(b);
      printf("ACHR/XPCI %i\n",n);
      n = buffer_read_int(b);
      printf("unknown Cell(?) FormID %i\n",n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("ACHR/DATA %i\n",n);
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
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of ACHR\n");

  return -1;
}
