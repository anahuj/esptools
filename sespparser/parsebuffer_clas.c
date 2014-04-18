
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
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("CLAS/DATA %i\n",n);
      n = buffer_read_int(b);
      printf("Primary Attribute 1 %i %% 0 Strength 1 Intelligence 2 Willpower 3 Agility 4 Speed 5 Endurance 6 Personality 7 Luck\n",n);
      n = buffer_read_int(b);
      printf("Primary Attribute 2 %i %% 0 Strength 1 Intelligence 2 Willpower 3 Agility 4 Speed 5 Endurance 6 Personality 7 Luck\n",n);
      n = buffer_read_int(b);
      printf("Specialization %i %% 0 Combat 1 Magic 2 Stealth\n",n);
      n = buffer_read_int(b);
      printf("Major Skill 1 %i %% 12 Armorer 13 Athletics 14 Blade 15 Block 16 Blunt 17 Hand To Hand 18 Heavy Armor 19 Alchemy 20 Alteration 21 Conjuration 22 Destruction 23 Illusion 24 Mysticism 25 Restoration 26 Acrobatics 27 Light Armor 28 Marksman 29 Mercantile 30 Security 31 Sneak 32 Speechcraft\n",n);
      n = buffer_read_int(b);
      printf("Major Skill 2 %i %% 12 Armorer 13 Athletics 14 Blade 15 Block 16 Blunt 17 Hand To Hand 18 Heavy Armor 19 Alchemy 20 Alteration 21 Conjuration 22 Destruction 23 Illusion 24 Mysticism 25 Restoration 26 Acrobatics 27 Light Armor 28 Marksman 29 Mercantile 30 Security 31 Sneak 32 Speechcraft\n",n);
      n = buffer_read_int(b);
      printf("Major Skill 3 %i %% 12 Armorer 13 Athletics 14 Blade 15 Block 16 Blunt 17 Hand To Hand 18 Heavy Armor 19 Alchemy 20 Alteration 21 Conjuration 22 Destruction 23 Illusion 24 Mysticism 25 Restoration 26 Acrobatics 27 Light Armor 28 Marksman 29 Mercantile 30 Security 31 Sneak 32 Speechcraft\n",n);
      n = buffer_read_int(b);
      printf("Major Skill 4 %i %% 12 Armorer 13 Athletics 14 Blade 15 Block 16 Blunt 17 Hand To Hand 18 Heavy Armor 19 Alchemy 20 Alteration 21 Conjuration 22 Destruction 23 Illusion 24 Mysticism 25 Restoration 26 Acrobatics 27 Light Armor 28 Marksman 29 Mercantile 30 Security 31 Sneak 32 Speechcraft\n",n);
      n = buffer_read_int(b);
      printf("Major Skill 5 %i %% 12 Armorer 13 Athletics 14 Blade 15 Block 16 Blunt 17 Hand To Hand 18 Heavy Armor 19 Alchemy 20 Alteration 21 Conjuration 22 Destruction 23 Illusion 24 Mysticism 25 Restoration 26 Acrobatics 27 Light Armor 28 Marksman 29 Mercantile 30 Security 31 Sneak 32 Speechcraft\n",n);
      n = buffer_read_int(b);
      printf("Major Skill 6 %i %% 12 Armorer 13 Athletics 14 Blade 15 Block 16 Blunt 17 Hand To Hand 18 Heavy Armor 19 Alchemy 20 Alteration 21 Conjuration 22 Destruction 23 Illusion 24 Mysticism 25 Restoration 26 Acrobatics 27 Light Armor 28 Marksman 29 Mercantile 30 Security 31 Sneak 32 Speechcraft\n",n);
      n = buffer_read_int(b);
      printf("Major Skill 7 %i %% 12 Armorer 13 Athletics 14 Blade 15 Block 16 Blunt 17 Hand To Hand 18 Heavy Armor 19 Alchemy 20 Alteration 21 Conjuration 22 Destruction 23 Illusion 24 Mysticism 25 Restoration 26 Acrobatics 27 Light Armor 28 Marksman 29 Mercantile 30 Security 31 Sneak 32 Speechcraft\n",n);
      flags = buffer_read_uint(b);
      printflags(flags);
      //      0000,0000,0000,0000,0000,0000,0000,0000
      printf("                                      ^Playable\n");
      printf("                                     ^Guard\n");
      flags = buffer_read_uint(b);
      printflags(flags);
      //      0000,0000,0000,0000,0000,0000,0000,0000
      printf("                                      ^Weapons\n");
      printf("                                     ^Armor\n");
      printf("                                    ^Clothing\n");
      printf("                                   ^Books\n");
      printf("                                 ^Ingredients\n");
      printf("                              ^Lights\n");
      printf("                            ^Apparatus\n");
      printf("                          ^Miscellaneous\n");
      printf("                         ^Spells\n");
      printf("                       ^Magic Items\n");
      printf("                      ^Potions\n");
      printf("                     ^Training\n");
      printf("                  ^Recharge\n");
      printf("                 ^Repair\n");
      n = buffer_read_ubyte(b);
      printf("Training Type %i %% 0 Armorer 1 Athletics 2 Blade 3 Block 4 Blunt 5 Hand To Hand 6 Heavy Armor 7 Alchemy 8 Alteration 9 Conjuration 10 Destruction 11 Illusion 12 Mysticism 13 Restoration 14 Acrobatics 15 Light Armor 16 Marksman 17 Mercantile 18 Security 19 Sneak 20 Speechcraft\n",n);
      n = buffer_read_ubyte(b);
      printf("Training Value %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of CLAS\n");

  return -1;
}
