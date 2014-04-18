
char armo_boname[100];

int parsebuffer_armo(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int boindex;

  boindex = 0;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"NAME") == 0) {
      n = buffer_read_int(b);
      printf("ARMO/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      armo_boname[0] = '\0';
      strcpy(armo_boname,s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_int(b);
      printf("ARMO/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_int(b);
      printf("ARMO/FNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"AODT") == 0) {
      n = buffer_read_int(b);
      printf("ARMO/AODT %i\n",n);
      n = buffer_read_int(b);
      printf("Type %i %% 0 Helmet 1 Cuirass 2 Left Pauldron 3 Right Pauldron 4 Greaves 5 Boots 6 Left Gauntlet 7 Right Gauntlet 8 Shield 9 Left Bracer 10 Right Bracer\n",n);
      f = buffer_read_float(b);
      printf("Weight %f\n",f);
      n = buffer_read_int(b);
      printf("Value %i\n",n);
      n = buffer_read_int(b);
      printf("Health %i\n",n);
      n = buffer_read_int(b);
      printf("Enchantment %i\n",n);
      n = buffer_read_int(b);
      printf("AR %i\n",n);
    } else if (strcmp(s,"ITEX") == 0) {
      n = buffer_read_int(b);
      printf("ARMO/ITEX %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Inventory Image \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"INDX") == 0) {
      n = buffer_read_int(b);
      printf("ARMO/INDX %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Biped Object %i %% See list in NOTES_MWESPTEST.\n",n);
      boindex++;
      printf("xxxxarmobipedobject %i : %s / %i\n",n,armo_boname,boindex);
    } else if (strcmp(s,"BNAM") == 0) {
      n = buffer_read_int(b);
      printf("ARMO/BNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Male Armor \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_int(b);
      printf("ARMO/SCRI %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Script \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ENAM") == 0) {
      n = buffer_read_int(b);
      printf("ARMO/ENAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Enchanting \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"CNAM") == 0) {
      n = buffer_read_int(b);
      printf("ARMO/CNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Female Armor \"%s\"\n",s2);
      free(s2);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of ARMO\n");

  return -1;
}
