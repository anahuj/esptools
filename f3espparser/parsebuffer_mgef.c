
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
      n = buffer_read_int(b);
      printf("Counter Effect FormID %i\n",n);
#if 0
      s2 = buffer_read_nstring(b,n); // Array of 4 byte names.
      printf("Counter Effects \"%s\"\n",s2);
      free(s2);
#endif
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("MGEF/DATA %i\n",n);
      size = n;
      if (size >= 36) {
	flags = buffer_read_uint(b);
	printflags(flags);
	//      0000,0000,0000,0000,0000,0000,0000,0000
	printf("                                      ^Hostile\n");
	printf("                                     ^Recover\n");
	printf("                                    ^Detrimental\n");
	printf("                                 ^Self\n");
	printf("                                ^Touch\n");
	printf("                               ^Target\n");
	printf("                              ^No Duration\n");
	printf("                            ^No Magnitude\n");
	printf("                           ^No Area\n");
	printf("                          ^FX Persist\n");
	printf("                       ^Gory Visuals\n");
	printf("                      ^Display Name Only\n");
	printf("                    ^Unnamed flag\n");
	printf("               ^Use Skill\n");
	printf("             ^Use Attribute\n");
	printf("        ^Painless\n");
	printf("      ^^00 Ball 01 Spray 10 Bolt 11 Fog\n");
	printf("     ^No Hit Effect\n");
	printf("   ^No Death Dispel\n");
#if 0
	f = buffer_read_float(b);
	// printf("Base Cost %f\n",f);
	printf("%f\n",f);
#else
	n = buffer_read_int(b);
	printf("%i unknown (Base Cost in Oblivion)\n",n);
#endif
	n = buffer_read_int(b);
	printf("Assoc. Item FormID %i\n",n);
	n = buffer_read_int(b);
	// printf("School %i\n",n);
	printf("%i unknown (School in Oblivion)\n",n);
	n = buffer_read_int(b);
	printf("Resist Value %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Number of Counter Effects %i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i unknown (unused?)\n",n);
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
	printf("Visual Effects Object Display Effect FormID %i\n",n);
	n = buffer_read_int(b);
	printf("Sounds Effect Sound FormID %i\n",n);
	n = buffer_read_int(b);
	printf("Sounds Bolt Sound FormID %i\n",n);
	n = buffer_read_int(b);
	printf("Sounds Hit Sound FormID %i\n",n);
	n = buffer_read_int(b);
	printf("Sounds Area Sound FormID %i\n",n);
#if 0
	f = buffer_read_float(b);
	// printf("Constant Effect Enchantment Factor %f\n",f);
	printf("%f\n",f);
#else
	n = buffer_read_int(b);
	printf("%i\n",n);
#endif
#if 0
	f = buffer_read_float(b);
	// printf("Constant Effect Barter Factor %f\n",f);
	printf("%f\n",f);
#else
	n = buffer_read_int(b);
	printf("%i\n",n);
#endif
      }
      if (size >= 72) { // F
	n = buffer_read_int(b);
	printf("Effect Archetype %i\n",n);
	n = buffer_read_int(b);
	printf("Actor Value %i %% For Value Modifier. See NOTES_FESPTEST for list of values.\n",n);
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
