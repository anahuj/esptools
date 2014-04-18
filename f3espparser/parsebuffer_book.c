
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
      printf("Inventory image \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_ushort(b);
      printf("BOOK/DATA %i\n",n);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("       ^Can't be Taken\n");
      n = buffer_read_byte(b);
      printf("Teaches %i %% -1 NONE 0 Barter 1 Big Guns 2 Energy Weapons 3 Explosives 4 Lockpick 5 Medicine 6 Melee Weapons 7 Repair 8 Science 9 Small Guns 10 Sneak 11 Speech 13 Unarmed\n",n);
      n = buffer_read_int(b);
      printf("Value %i\n",n);
      f = buffer_read_float(b);
      printf("Weight %f\n",f);
    } else if (strcmp(s,"OBND") == 0) { // F
      n = buffer_read_short(b);
      printf("BOOK/OBND %i\n",n);
      parse_obnd(b);
    } else if (strcmp(s,"YNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("BOOK/YNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Pickup Sound FormID %i\n",n);
    } else if (strcmp(s,"ZNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("BOOK/ZNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Putdown Sound FormID %i\n",n);
    } else if (strcmp(s,"MICO") == 0) { // F
      n = buffer_read_short(b);
      printf("BOOK/MICO %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Message Icon \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"EITM") == 0) { // F
      n = buffer_read_short(b);
      printf("BOOK/EITM %i\n",n);
      n = buffer_read_int(b);
      printf("Object Effect FormID %i\n",n);
    } else if (strcmp(s,"DEST") == 0) { // F
      n = buffer_read_short(b);
      printf("BOOK/DEST %i\n",n);
      parse_dest(b);
    } else if (strcmp(s,"DSTD") == 0) { // F
      n = buffer_read_short(b);
      printf("BOOK/DSTD %i\n",n);
      parse_dstd(b);
    } else if (strcmp(s,"DSTF") == 0) { // F
      n = buffer_read_short(b);
      printf("BOOK/DSTF %i\n",n);
      // Empty.
    } else if (strcmp(s,"DMDL") == 0) { // F
      n = buffer_read_short(b);
      printf("BOOK/DMDL %i\n",n);
      parse_dmdl(b,n);
    } else if (strcmp(s,"DMDT") == 0) { // F
      n = buffer_read_short(b);
      printf("BOOK/DMDT %i\n",n);
      parse_dmdt(b,n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of BOOK\n");

  return -1;
}
