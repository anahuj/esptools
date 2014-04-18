
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
    if (strcmp(s,"NAME") == 0) {
      n = buffer_read_int(b);
      printf("CLAS/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_int(b);
      printf("CLAS/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DESC") == 0) {
      n = buffer_read_int(b);
      printf("CLAS/DESC %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Description \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"CLDT") == 0) {
      n = buffer_read_int(b);
      printf("CLAS/CLDT %i\n",n);
      n = buffer_read_int(b);
      printf("Primary Attribute 1 %i %% 0 Strength 1 Intelligence 2 Willpower 3 Agility 4 Speed 5 Endurance 6 Personality 7 Luck\n",n);
      n = buffer_read_int(b);
      printf("Primary Attribute 2 %i %% 0 Strength 1 Intelligence 2 Willpower 3 Agility 4 Speed 5 Endurance 6 Personality 7 Luck\n",n);
      n = buffer_read_int(b);
      printf("Specialization %i %% 0 Combat 1 Magic 2 Stealth\n",n);
      n = buffer_read_int(b);
      printf("Minor Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_int(b);
      printf("Major Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_int(b);
      printf("Minor Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_int(b);
      printf("Major Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_int(b);
      printf("Minor Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_int(b);
      printf("Major Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_int(b);
      printf("Minor Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_int(b);
      printf("Major Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_int(b);
      printf("Minor Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_int(b);
      printf("Major Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Playable\n");
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      printf("Auto-Calc:\n");
      n = buffer_read_uint(b);
      printflags(n);
      //      0000,0000,0000,0000,0000,0000,0000,0000
      printf("                                      ^Weapons\n");
      printf("                                     ^Armor\n");
      printf("                                    ^Clothing\n");
      printf("                                   ^Books\n");
      printf("                                 ^Ingredients\n");
      printf("                                ^Picks\n");
      printf("                               ^Probes\n");
      printf("                              ^Lights\n");
      printf("                            ^Apparatus\n");
      printf("                           ^Repair Items\n");
      printf("                          ^Miscellaneous\n");
      printf("                         ^Spells\n");
      printf("                       ^Magic Items\n");
      printf("                      ^Potions\n");
      printf("                     ^Training\n");
      printf("                    ^Spellmaking\n");
      printf("                  ^Enchanting\n");
      printf("                 ^Repair\n");
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of CLAS\n");

  return -1;
}
