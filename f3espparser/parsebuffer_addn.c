
int parsebuffer_addn(void *b)
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
      printf("ADDN/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("ADDN/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("ADDN/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"OBND") == 0) {
      n = buffer_read_short(b);
      printf("ADDN/OBND %i\n",n);
      parse_obnd(b);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("ADDN/DATA %i\n",n);
      n = buffer_read_int(b);
      printf("Addon Node Index %i\n",n);
    } else if (strcmp(s,"DNAM") == 0) {
      n = buffer_read_short(b);
      printf("ADDN/DNAM %i\n",n);
      n = buffer_read_short(b);
      printf("Master Particle System Cap %i\n",n);
      n = buffer_read_short(b);
      printf("Has Master Particle System %i %% Has BSMasterParticleSystem in NIF\n",n);
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_short(b);
      printf("ADDN/SNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Sound FormID %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of ADDN\n");

  return -1;
}
