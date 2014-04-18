
int parsebuffer_ltex(void *b)
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
      printf("LTEX/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("LTEX/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"HNAM") == 0) {
      n = buffer_read_short(b);
      printf("LTEX/HNAM %i\n",n);
      n = buffer_read_byte(b);
      printf("Material Type %i\n",n);
      n = buffer_read_byte(b);
      printf("Friction %i\n",n);
      n = buffer_read_byte(b);
      printf("Restitution %i\n",n);
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_short(b);
      printf("LTEX/SNAM %i\n",n);
      n = buffer_read_byte(b);
      printf("Texture Specular Exponent %i\n",n);
    } else if (strcmp(s,"GNAM") == 0) {
      n = buffer_read_short(b);
      printf("LTEX/GNAM %i\n",n);
      n = buffer_read_uint(b);
      printf("Potential Grass FormID %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of LTEX\n");

  return -1;
}
