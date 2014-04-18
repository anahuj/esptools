
int parsebuffer_scol(void *b)
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
      printf("SCOL/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"OBND") == 0) {
      n = buffer_read_short(b);
      printf("SCOL/OBND %i\n",n);
      parse_obnd(b);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("SCOL/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("SCOL/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"ONAM") == 0) {
      n = buffer_read_short(b);
      printf("SCOL/ONAM %i\n",n);
      n = buffer_read_int(b);
      printf("Object Data FormID %i\n",n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("SCOL/DATA %i\n",n);
      size = n;
      num = size/4/7; // pos xyz, rot xyz, scale
      for (i = 0; i < num; i++) {
	f = buffer_read_float(b);
	printf("PosX %f\n",f);
	f = buffer_read_float(b);
	printf("PosY %f\n",f);
	f = buffer_read_float(b);
	printf("PosZ %f\n",f);
	f = buffer_read_float(b);
	printf("RotX %f\n",f);
	f = buffer_read_float(b);
	printf("RotY %f\n",f);
	f = buffer_read_float(b);
	printf("RotZ %f\n",f);
	f = buffer_read_float(b);
	printf("Scale %f\n",f);
      }
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of SCOL\n");

  return -1;
}
