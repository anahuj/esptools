
int parsebuffer_race(void *b)
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
      printf("RACE/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_int(b);
      printf("RACE/FNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"RADT") == 0) {
      n = buffer_read_int(b);
      printf("RACE/RADT %i\n",n);
      n = buffer_read_int(b);
      printf("Skill Bonus 1 Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_int(b);
      printf("Skill Bonus 1 Value %i\n",n);
      n = buffer_read_int(b);
      printf("Skill Bonus 2 Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_int(b);
      printf("Skill Bonus 2 Value %i\n",n);
      n = buffer_read_int(b);
      printf("Skill Bonus 3 Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_int(b);
      printf("Skill Bonus 3 Value %i\n",n);
      n = buffer_read_int(b);
      printf("Skill Bonus 4 Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_int(b);
      printf("Skill Bonus 4 Value %i\n",n);
      n = buffer_read_int(b);
      printf("Skill Bonus 5 Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_int(b);
      printf("Skill Bonus 5 Value %i\n",n);
      n = buffer_read_int(b);
      printf("Skill Bonus 6 Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_int(b);
      printf("Skill Bonus 6 Value %i\n",n);
      n = buffer_read_int(b);
      printf("Skill Bonus 7 Skill %i %% -1 NONE 0 Block 1 Armorer 2 Medium Armor 3 Heavy Armor 4 Blunt Weapon 5 Long Blade 6 Axe 7 Spear 8 Athletics 9 Enchant 10 Destruction 11 Alteration 12 Illusion 13 Conjuration 14 Mysticism 15 Restoration 16 Alchemy 17 Unarmored 18 Security 19 Sneak 20 Acrobatics 21 Light Armor 22 Short Blade 23 Marksman 24 Mercantile 25 Speechcraft 26 Hand-to-hand\n",n);
      n = buffer_read_int(b);
      printf("Skill Bonus 7 Value %i\n",n);
      n = buffer_read_int(b);
      printf("Base Attributes Str Male %i\n",n);
      n = buffer_read_int(b);
      printf("Base Attributes Str Female %i\n",n);
      n = buffer_read_int(b);
      printf("Base Attributes Int Male %i\n",n);
      n = buffer_read_int(b);
      printf("Base Attributes Int Female %i\n",n);
      n = buffer_read_int(b);
      printf("Base Attributes Wil Male %i\n",n);
      n = buffer_read_int(b);
      printf("Base Attributes Wil Female %i\n",n);
      n = buffer_read_int(b);
      printf("Base Attributes Agi Male %i\n",n);
      n = buffer_read_int(b);
      printf("Base Attributes Agi Female %i\n",n);
      n = buffer_read_int(b);
      printf("Base Attributes Spd Male %i\n",n);
      n = buffer_read_int(b);
      printf("Base Attributes Spd Female %i\n",n);
      n = buffer_read_int(b);
      printf("Base Attributes End Male %i\n",n);
      n = buffer_read_int(b);
      printf("Base Attributes End Female %i\n",n);
      n = buffer_read_int(b);
      printf("Base Attributes Per Male %i\n",n);
      n = buffer_read_int(b);
      printf("Base Attributes Per Female %i\n",n);
      n = buffer_read_int(b);
      printf("Base Attributes Luc Male %i\n",n);
      n = buffer_read_int(b);
      printf("Base Attributes Luc Female %i\n",n);

      f = buffer_read_float(b);
      printf("Male Height %f\n",f);
      f = buffer_read_float(b);
      printf("Female Height %f\n",f);
      f = buffer_read_float(b);
      printf("Male Weight %f\n",f);
      f = buffer_read_float(b);
      printf("Female Weight %f\n",f);

      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Playable\n");
      printf("       ^Beast Race\n");
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"NPCS") == 0) {
      n = buffer_read_int(b);
      printf("RACE/NPCS %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Spell \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DESC") == 0) {
      n = buffer_read_int(b);
      printf("RACE/DESC %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Description \"%s\"\n",s2);
      free(s2);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of RACE\n");

  return -1;
}
