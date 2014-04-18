
int parsebuffer_sgst(void *b)
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
      printf("SGST/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("SGST/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("SGST/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("SGST/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("SGST/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("SGST/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Menu Image \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_short(b);
      printf("SGST/SCRI %i\n",n);
      n = buffer_read_int(b);
      printf("Script FormID %i\n",n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("SGST/DATA %i\n",n);
      n = buffer_read_byte(b);
      printf("Uses %i\n",n);
      n = buffer_read_int(b);
      printf("Value %i\n",n);
      f = buffer_read_float(b);
      printf("Weight %f\n",f);
    } else if (strcmp(s,"EFID") == 0) {
      n = buffer_read_short(b);
      printf("SGST/EFID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Effect ID \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"EFIT") == 0) {
      n = buffer_read_short(b);
      printf("SGST/EFIT %i\n",n);
      parse_efit(b);
    } else if (strcmp(s,"SCIT") == 0) { // Not in Oblivion.esm
      n = buffer_read_short(b);
      printf("SGST/SCIT %i\n",n);
      parse_scit(b,n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of SGST\n");

  return -1;
}
