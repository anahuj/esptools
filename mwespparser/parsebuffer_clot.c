
char clot_boname[100];

int parsebuffer_clot(void *b)
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
      printf("CLOT/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      clot_boname[0] = '\0';
      strcpy(clot_boname,s2);
      free(s2);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_int(b);
      printf("CLOT/FNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_int(b);
      printf("CLOT/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"CTDT") == 0) {
      n = buffer_read_int(b);
      printf("CLOT/CTDT %i\n",n);
      n = buffer_read_int(b);
      printf("Type %i %% 0 Pants 1 Shoes 2 Shirt 3 Belt 4 Robe 5 Right Glove 6 Left Glove 7 Skirt 8 Ring 9 Amulet\n",n);
      f = buffer_read_float(b);
      printf("Weight %f\n",f);
      n = buffer_read_ushort(b);
      printf("Value %i\n",n);
      n = buffer_read_ushort(b);
      printf("Enchantment %i\n",n);
    } else if (strcmp(s,"ITEX") == 0) {
      n = buffer_read_int(b);
      printf("CLOT/ITEX %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Inventory Image \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"INDX") == 0) {
      n = buffer_read_int(b);
      printf("CLOT/INDX %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Biped Object %i %% See list in NOTES_MWESPTEST.\n",n);
      boindex++;
      printf("xxxxclotbipedobject %i : %s / %i\n",n,clot_boname,boindex);
    } else if (strcmp(s,"BNAM") == 0) {
      n = buffer_read_int(b);
      printf("CLOT/BNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Male Clothing \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"CNAM") == 0) {
      n = buffer_read_int(b);
      printf("CLOT/CNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Female Clothing \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ENAM") == 0) {
      n = buffer_read_int(b);
      printf("CLOT/ENAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Enchanting \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_int(b);
      printf("CLOT/SCRI %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Script \"%s\"\n",s2);
      free(s2);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of CLOT\n");

  return -1;
}
