
int parsebuffer_note(void *b)
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
  int datatype;

  datatype = -1;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("NOTE/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("NOTE/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("NOTE/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Icon \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("NOTE/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("NOTE/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_short(b);
      printf("NOTE/SNAM %i\n",n);
      if (datatype == 0) {
	n = buffer_read_int(b);
	printf("Note Data Note Sound FormID %i\n",n);
      } else if (datatype == 3) {
	n = buffer_read_int(b);
	printf("Note Data Speaker FormID %i\n",n);
      } else {
	fprintf(stderr,"Error: Unknown Note Type %i\n",datatype);
	exit(-1);
      }
    } else if (strcmp(s,"ONAM") == 0) {
      n = buffer_read_short(b);
      printf("NOTE/ONAM %i\n",n);
      n = buffer_read_int(b);
      printf("Owner Quest FormID %i\n",n);
    } else if (strcmp(s,"OBND") == 0) {
      n = buffer_read_short(b);
      printf("NOTE/OBND %i\n",n);
      parse_obnd(b);
    } else if (strcmp(s,"TNAM") == 0) {
      n = buffer_read_short(b);
      printf("NOTE/TNAM %i\n",n);
      if (datatype == 1) {
	s2 = buffer_read_nstring(b,n);
	printf("Note Data Text \"%s\"\n",s2);
	free(s2);
      } else if (datatype == 3) {
	n = buffer_read_int(b);
	printf("Note Data Topic FormID %i\n",n);
      } else {
	fprintf(stderr,"Error: Unknown Note Type %i\n",datatype);
	exit(-1);
      }
    } else if (strcmp(s,"XNAM") == 0) {
      n = buffer_read_short(b);
      printf("NOTE/XNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Note Data Note image \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("NOTE/DATA %i\n",n);
      n = buffer_read_byte(b);
      printf("Note Type %i %% 0 Sound 1 Text 2 Image 3 Voice\n",n);
      datatype = n;
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of NOTE\n");

  return -1;
}
