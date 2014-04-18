
int parsebuffer_txst(void *b)
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
      printf("TXST/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"OBND") == 0) {
      n = buffer_read_short(b);
      printf("TXST/OBND %i\n",n);
      parse_obnd(b);
    } else if (strcmp(s,"TX00") == 0) {
      n = buffer_read_short(b);
      printf("TXST/TX00 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Diffuse \"%s\"\n",s2);
      printf("txst %i tx00 \"%s\"\n",global_formid,s2);
      free(s2);
    } else if (strcmp(s,"TX01") == 0) {
      n = buffer_read_short(b);
      printf("TXST/TX01 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Normal/Gloss \"%s\"\n",s2);
      printf("txst %i tx01 \"%s\"\n",global_formid,s2);
      free(s2);
    } else if (strcmp(s,"TX02") == 0) {
      n = buffer_read_short(b);
      printf("TXST/TX02 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Environment Mask Map \"%s\"\n",s2);
      printf("txst %i tx02 \"%s\"\n",global_formid,s2);
      free(s2);
    } else if (strcmp(s,"TX03") == 0) {
      n = buffer_read_short(b);
      printf("TXST/TX03 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Glow/Skin/Hair \"%s\"\n",s2);
      printf("txst %i tx03 \"%s\"\n",global_formid,s2);
      free(s2);
    } else if (strcmp(s,"TX04") == 0) {
      n = buffer_read_short(b);
      printf("TXST/TX04 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Height \"%s\"\n",s2);
      printf("txst %i tx04 \"%s\"\n",global_formid,s2);
      free(s2);
    } else if (strcmp(s,"TX05") == 0) {
      n = buffer_read_short(b);
      printf("TXST/TX05 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Environment \"%s\"\n",s2);
      printf("txst %i tx05 \"%s\"\n",global_formid,s2);
      free(s2);
    } else if (strcmp(s,"DNAM") == 0) {
      n = buffer_read_short(b);
      printf("TXST/DNAM %i\n",n);
      n = buffer_read_short(b);
      printf("%i\n",n);
    } else if (strcmp(s,"DODT") == 0) {
      n = buffer_read_short(b);
      printf("TXST/DODT %i\n",n);
      f = buffer_read_float(b);
      printf("Min Width %f\n",f);
      f = buffer_read_float(b);
      printf("Max Width %f\n",f);
      f = buffer_read_float(b);
      printf("Min Height %f\n",f);
      f = buffer_read_float(b);
      printf("Max Height %f\n",f);
      f = buffer_read_float(b);
      printf("Depth %f\n",f);
      f = buffer_read_float(b);
      printf("Shininess %f\n",f);
      f = buffer_read_float(b);
      printf("Parallax Scale %f\n",f);
      n = buffer_read_byte(b);
      printf("Parallax Passes %i\n",n);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Parallax\n");
      printf("       ^Alpha Blending\n");
      printf("      ^Alpha Testing\n");
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of TXST\n");

  return -1;
}

