
int parsebuffer_book(void *b)
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
      n = buffer_read_ushort(b);
      printf("BOOK/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_ushort(b);
      printf("BOOK/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DESC") == 0) {
      n = buffer_read_ushort(b);
      printf("BOOK/DESC %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Book Text \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_ushort(b);
      printf("BOOK/SCRI %i\n",n);
      n = buffer_read_int(b);
      printf("Script FormID %i\n",n);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_ushort(b);
      printf("BOOK/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_ushort(b);
      printf("BOOK/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_ushort(b);
      printf("BOOK/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_ushort(b);
      printf("BOOK/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Icon \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ENAM") == 0) {
      n = buffer_read_ushort(b);
      printf("BOOK/ENAM %i\n",n);
      n = buffer_read_int(b);
      printf("Enchanting FormID %i\n",n);
    } else if (strcmp(s,"ANAM") == 0) {
      n = buffer_read_ushort(b);
      printf("BOOK/ANAM %i\n",n);
      n = buffer_read_ushort(b);
      printf("Enchantment %i\n",n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_ushort(b);
      printf("BOOK/DATA %i\n",n);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Scroll\n");
      n = buffer_read_byte(b);
      printf("Teaches %i\n",n);
      printf(" %% -1 NONE\n");
      printf(" %%  0 Armorer\n");
      printf(" %%  1 Athletics\n");
      printf(" %%  2 Blade\n");
      printf(" %%  3 Block\n");
      printf(" %%  4 Blunt\n");
      printf(" %%  5 Hand To Hand\n");
      printf(" %%  6 Heavy Armor\n");
      printf(" %%  7 Alchemy\n");
      printf(" %%  8 Alteration\n");
      printf(" %%  9 Conjuration\n");
      printf(" %% 10 Destruction\n");
      printf(" %% 11 Illusion\n");
      printf(" %% 12 Mysticism\n");
      printf(" %% 13 Restoration\n");
      printf(" %% 14 Acrobatics\n");
      printf(" %% 15 Light Armor\n");
      printf(" %% 16 Marksman\n");
      printf(" %% 17 Mercantile\n");
      printf(" %% 18 Security\n");
      printf(" %% 19 Sneak\n");
      printf(" %% 20 Speechcraft\n");
      n = buffer_read_int(b);
      printf("Value %i\n",n);
      f = buffer_read_float(b);
      printf("Weight %f\n",f);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of BOOK\n");

  return -1;
}
