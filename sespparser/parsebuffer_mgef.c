
int parsebuffer_mgef(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int size;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("MGEF/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("MGEF/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DESC") == 0) {
      n = buffer_read_short(b);
      printf("MGEF/DESC %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Description \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("MGEF/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Effect Icon \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("MGEF/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Visual Effects Effects NIF \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("MGEF/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("MGEF/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"ESCE") == 0) {
      n = buffer_read_short(b);
      printf("MGEF/ESCE %i\n",n);
      s2 = buffer_read_nstring(b,n); // Array of 4 byte names.
      printf("Counter Effects \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("MGEF/DATA %i\n",n);
      size = n;
      if (size >= 36) {
	flags = buffer_read_uint(b);
	printflags(flags);
	//      0000,0000,0000,0000,0000,0000,0000,0000
	printf("                                      ^3 Hostile\n");
	printf("                                     ^5 Recover\n");
	printf("                                    ^4 Detrimental\n");
	printf("                                   ^6 Magnitude %%\n");
	printf("                                 ^8 Self\n");
	printf("                                ^9 Touch\n");
	printf("                               ^10 Target\n");
	printf("                              ^11 No Duration\n");
	printf("                            ^12 No Magnitude\n");
	printf("                          ^7 FX Persist\n");
	printf("                         ^1 Spellmaking\n");
	printf("                       ^2 Enchanting\n");
	printf("                      ^14 No Ingredient\n");
	printf("                  ^15 Use Weapon\n");
	printf("                 ^16 Use Armor\n");
	printf("                ^17 Use Creature\n");
	printf("               ^18 Use Skill\n");
	printf("             ^19 Use Attribute\n");
	printf("      ^^Projectile Type 00 Ball 01 Spray 10 Bolt 11 Fog\n");
	printf("     ^21 No Hit Effect\n");
	f = buffer_read_float(b);
	printf("Base Cost %f\n",f);
	n = buffer_read_int(b);
	printf("Assoc. Item FormID %i\n",n);
	n = buffer_read_int(b);
	printf("School %i %% 0 Alteration 1 Conjuration 2 Destruction 3 Illusion 4 Mysticism 5 Restoration\n",n);
	n = buffer_read_int(b);
	printf("Resist Value %i %% -1 NONE 61 Resist Fire 62 Resist Frost 63 Resist Disease 64 Resist Magic 65 Resist Normal Weapons 66 Resist Paralysis 67 Resist Poison 68 Resist Shock\n",n);
	n = buffer_read_ubyte(b);
	printf("Number of Counter Effects %i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i (unused)\n",n);
	n = buffer_read_ubyte(b);
	printf("%i (unused)\n",n);
	n = buffer_read_int(b);
	printf("Visual Effects Light FormID %i\n",n);
	f = buffer_read_float(b);
	printf("Visual Effects Projectile Speed %f\n",f);
	n = buffer_read_int(b);
	printf("Visual Effects Effect Shader FormID %i\n",n);
      }
      if (size >= 64) {
	n = buffer_read_int(b);
	printf("Visual Effects Enchant Effect FormID %i\n",n);
	n = buffer_read_int(b);
	printf("Casting Sound FormID %i\n",n);
	n = buffer_read_int(b);
	printf("Bolt Sound FormID %i\n",n);
	n = buffer_read_int(b);
	printf("Hit Sound FormID %i\n",n);
	n = buffer_read_int(b);
	printf("Area Sound FormID %i\n",n);
	f = buffer_read_float(b);
	printf("Constant Effect Enchantment Factor %f\n",f);
	f = buffer_read_float(b);
	printf("Constant Effect Barter Factor %f\n",f);
      }
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of MGEF\n");

  return -1;
}
