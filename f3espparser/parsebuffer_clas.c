
int parsebuffer_clas(void *b)
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
      printf("CLAS/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("CLAS/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Full Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DESC") == 0) {
      n = buffer_read_short(b);
      printf("CLAS/DESC %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Description \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("CLAS/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Menu Image \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) { // F
      n = buffer_read_short(b);
      printf("CLAS/DATA %i\n",n);
      n = buffer_read_int(b);
      printf("Tag Skill 1 %i %% -1 NONE 32 Barter 33 Big Guns 34 Energy Weapons 35 Explosives 36 Lockpick 37 Medicine 38 Melee Weapons 39 Repair 40 Science 41 Small Guns 42 Sneak 43 Speech 45 Unarmed\n",n);
      n = buffer_read_int(b);
      printf("Tag Skill 2 %i %% -1 NONE 32 Barter 33 Big Guns 34 Energy Weapons 35 Explosives 36 Lockpick 37 Medicine 38 Melee Weapons 39 Repair 40 Science 41 Small Guns 42 Sneak 43 Speech 45 Unarmed\n",n);
      n = buffer_read_int(b);
      printf("Tag Skill 3 %i %% -1 NONE 32 Barter 33 Big Guns 34 Energy Weapons 35 Explosives 36 Lockpick 37 Medicine 38 Melee Weapons 39 Repair 40 Science 41 Small Guns 42 Sneak 43 Speech 45 Unarmed\n",n);
      n = buffer_read_int(b);
      printf("%i (unused, tag skill 4? ignored by engine?)\n",n);
      n = buffer_read_int(b);
      printf("%i %% 2 Guard 29 ??\n",n);
      n = buffer_read_int(b);
      printflags(n);
      //      0000,0000,0000,0000,0000,0000,0000,0000
      printf("                                      ^Weapons\n");
      printf("                                     ^Armor\n");
      printf("                                    ^Alcohol\n");
      printf("                                   ^Books\n");
      printf("                                 ^Food\n");
      printf("                                ^Chems\n");
      printf("                               ^Stimpacks\n");
      printf("                          ^Miscellaneous\n");
      printf("                     ^Training\n");
      printf("                  ^Recharge\n");
      printf("                 ^Repair\n");
      n = buffer_read_ubyte(b);
      printf("Training skill %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Training value %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"ATTR") == 0) { // F
      n = buffer_read_short(b);
      printf("CLAS/ATTR %i\n",n);
      n = buffer_read_byte(b);
      printf("Base Attributes Str %i\n",n);
      n = buffer_read_byte(b);
      printf("Base Attributes Per %i\n",n);
      n = buffer_read_byte(b);
      printf("Base Attributes End %i\n",n);
      n = buffer_read_byte(b);
      printf("Base Attributes Cha %i\n",n);
      n = buffer_read_byte(b);
      printf("Base Attributes Int %i\n",n);
      n = buffer_read_byte(b);
      printf("Base Attributes Agi %i\n",n);
      n = buffer_read_byte(b);
      printf("Base Attributes Luc %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of CLAS\n");

  return -1;
}
