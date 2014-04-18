
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
    if (strcmp(s,"NAME") == 0) {
      n = buffer_read_int(b);
      printf("BOOK/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_int(b);
      printf("BOOK/FNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_int(b);
      printf("BOOK/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"BKDT") == 0) {
      n = buffer_read_int(b);
      printf("BOOK/BKDT %i\n",n);
      f = buffer_read_float(b);
      printf("Weight %f\n",f);
      n = buffer_read_int(b);
      printf("Value %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Scroll\n");
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_int(b);
      printf("Teaches %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_int(b);
      printf("Enchantment %i\n",n);
    } else if (strcmp(s,"ITEX") == 0) {
      n = buffer_read_int(b);
      printf("BOOK/ITEX %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Icon \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"TEXT") == 0) {
      n = buffer_read_int(b);
      printf("BOOK/TEXT %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Book Text \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_int(b);
      printf("BOOK/SCRI %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Script \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ENAM") == 0) {
      n = buffer_read_int(b);
      printf("BOOK/ENAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Enchanting \"%s\"\n",s2);
      free(s2);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of BOOK\n");

  return -1;
}
