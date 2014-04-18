
int parsebuffer_fact(void *b)
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
      printf("FACT/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_int(b);
      printf("FACT/FNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"RNAM") == 0) {
      n = buffer_read_int(b);
      printf("FACT/RNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Rank Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"FADT") == 0) {
      n = buffer_read_int(b);
      printf("FACT/FADT %i\n",n);
      n = buffer_read_int(b);
      printf("Attribute 1 %i %% 0 Strength 1 Intelligence 2 Willpower 3 Agility 4 Speed 5 Endurance 6 Personality 7 Luck\n",n);
      n = buffer_read_int(b);
      printf("Attribute 2 %i %% 0 Strength 1 Intelligence 2 Willpower 3 Agility 4 Speed 5 Endurance 6 Personality 7 Luck\n",n);
      m = n/4;
      for (i = 0; i < 10; i++) {
	printf("Rank %i:\n",i+1);
	n = buffer_read_int(b);
	printf("Attrib 1 %i\n",n);
	n = buffer_read_int(b);
	printf("Attrib 2 %i\n",n);
	n = buffer_read_int(b);
	printf("Pri Skill %i\n",n);
	n = buffer_read_int(b);
	printf("Fav Skill %i\n",n);
	n = buffer_read_int(b);
	printf("Fact Rep %i\n",n);
      }
      n = buffer_read_int(b);
      printf("Favored Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_int(b);
      printf("Favored Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_int(b);
      printf("Favored Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_int(b);
      printf("Favored Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_int(b);
      printf("Favored Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_int(b);
      printf("Favored Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_int(b);
      printf("Favored Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Hidden from PC\n");
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"ANAM") == 0) {
      n = buffer_read_int(b);
      printf("FACT/ANAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Reactions Faction \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"INTV") == 0) {
      n = buffer_read_int(b);
      printf("FACT/INTV %i\n",n);
      n = buffer_read_int(b);
      printf("Reactions Reaction %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of FACT\n");

  return -1;
}
