
int parsebuffer_npc(void *b)
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
    if (strcmp(s,"NAME") == 0) {
      n = buffer_read_int(b);
      printf("NPC_/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_int(b);
      printf("NPC_/FNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_int(b);
      printf("NPC_/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"RNAM") == 0) {
      n = buffer_read_int(b);
      printf("NPC_/RNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Race \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"CNAM") == 0) {
      n = buffer_read_int(b);
      printf("NPC_/CNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Class \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ANAM") == 0) {
      n = buffer_read_int(b);
      printf("NPC_/ANAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Faction \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"BNAM") == 0) {
      n = buffer_read_int(b);
      printf("NPC_/BNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Head \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"KNAM") == 0) {
      n = buffer_read_int(b);
      printf("NPC_/KNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Hair \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"NPDT") == 0) {
      n = buffer_read_int(b);
      printf("NPC_/NPDT %i\n",n);
      size = n;
      if (size == 12) {
      n = buffer_read_ushort(b);
      printf("Level %i\n",n);

      n = buffer_read_ubyte(b);
      printf("Disp %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Rep %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Rank %i %% See FACT record. RNAM indexing starts from 0\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);

      n = buffer_read_int(b);
      printf("AI Services Barter Gold %i\n",n);

      } else if (size == 52) {

      n = buffer_read_ushort(b);
      printf("Level %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Attributes Str %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Attributes Int %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Attributes Wil %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Attributes Agi %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Attributes Spd %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Attributes End %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Attributes Per %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Attributes Luc %i\n",n);

      n = buffer_read_ubyte(b);
      printf("Skill Block %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Armorer %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Medium Armor %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Heavy Armor %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Blunt Weapon %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Long Blade %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Axe %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Spear %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Athletics %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Enchant %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Destruction %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Alteration %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Illusion %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Conjuration %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Mysticism %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Restoration %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Alchemy %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Unarmored %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Security %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Sneak %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Acrobatics %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Light Armor %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Short Blade %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Marksman %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Mercantile %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Speechcraft %i\n",n);
      n = buffer_read_ushort(b);
      printf("Skill Hand-to-hand %i\n",n);
      n = buffer_read_ushort(b);
      printf("Health %i\n",n);
      n = buffer_read_ushort(b);
      printf("Magicka %i\n",n);
      n = buffer_read_ushort(b);
      printf("Fatigue %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Disp %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Rep %i\n",n);
      n = buffer_read_ushort(b);
      printf("Rank %i %% See FACT record. RNAM indexing starts from 0\n",n);
      n = buffer_read_int(b);
      printf("AI Services Barter Gold %i\n",n);

      } else {
	printf("unknown NPC_/NPDT size %i\n",size);
	exit(-1);
      }

    } else if (strcmp(s,"FLAG") == 0) {
      n = buffer_read_int(b);
      printf("NPC_/FLAG %i\n",n);
      n = buffer_read_ushort(b);
      printflags16(n);
      //      0000,0000,0000,0000
      printf("                  ^Female\n");
      printf("                 ^Essential\n");
      printf("                ^Respawn\n");
      printf("               ^(unknown)\n");
      printf("             ^Auto Calculate Stats\n");
      printf("     ^^Blood Texture: 00 Default (Red) 01 Skeleton (White) 10 Metal Sparks (Gold)\n");
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"NPCO") == 0) {
      n = buffer_read_int(b);
      printf("NPC_/NPCO %i\n",n);
      n = buffer_read_int(b);
      printf("Item Count %i\n",n);
      s2 = buffer_read_nstring(b,32);
      printf("Item Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"AIDT") == 0) {
      n = buffer_read_int(b);
      printf("NPC_/AIDT %i\n",n);
      n = buffer_read_ushort(b);
      printf("Hello %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Fight %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Flee %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Alarm %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      printf("AI Services:\n");
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
#if 0
      n = buffer_read_ushort(b);
      printflags16(n);
      //      0000,0000,0000,0000
      printf("                  ^Weapons\n");
      printf("                 ^Armor\n");
      printf("                ^Clothing\n");
      printf("               ^Books\n");
      printf("             ^Ingredients\n");
      printf("            ^Picks\n");
      printf("           ^Probes\n");
      printf("          ^Lights\n");
      printf("        ^Apparatus\n");
      printf("       ^Repair Items\n");
      printf("      ^Miscellaneous\n");
      printf("     ^Spells\n");
      printf("   ^Magic Items\n");
      printf("  ^Potions\n");
      printf(" ^Training\n");
      printf("^Spellmaking\n");
      n = buffer_read_ushort(b);
      printflags16(n);
      //      0000,0000,0000,0000
      printf("                  ^Enchanting\n");
      printf("                 ^Repair\n");
#endif
    } else if (strcmp(s,"AI_W") == 0) {
      n = buffer_read_int(b);
      printf("NPC_/AI_W %i\n",n);
      n = buffer_read_ushort(b);
      printf("Distance %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Duration (in hours) %i %% 0-24\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unknown)\n",n);
      n = buffer_read_ubyte(b);
      printf("Time of Day (??:00) %i %% 0-23\n",n);
      n = buffer_read_ubyte(b);
      printf("Idle Chances Idle 2 %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Idle Chances Idle 3 %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Idle Chances Idle 4 %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Idle Chances Idle 5 %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Idle Chances Idle 6 %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Idle Chances Idle 7 %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Idle Chances Idle 8 %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Idle Chances Idle 9 %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unknown)\n",n);
    } else if (strcmp(s,"AI_E") == 0) {
      n = buffer_read_int(b);
      printf("CREA/AI_E %i\n",n);
      f = buffer_read_float(b);
      printf("Specific Point X %f\n",f);
      f = buffer_read_float(b);
      printf("Specific Point Y %f\n",f);
      f = buffer_read_float(b);
      printf("Specific Point Z %f\n",f);

      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);

      s2 = buffer_read_nstring(b,7);
      printf("%s\n",s2);
      free(s2);

      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);

      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);

      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);

      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);

      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);

      n = buffer_read_ushort(b);
      printf("%i\n",n);
      n = buffer_read_ushort(b);
      printf("%i\n",n);

    } else if (strcmp(s,"AI_F") == 0) {
      n = buffer_read_int(b);
      printf("NPC_/AI_F %i\n",n);
      f = buffer_read_float(b);
      printf("Specific Point X %f\n",f);
      f = buffer_read_float(b);
      printf("Specific Point Y %f\n",f);
      f = buffer_read_float(b);
      printf("Specific Point Z %f\n",f);

      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);

      s2 = buffer_read_nstring(b,16);
      printf("Target \"%s\"\n",s2);
      free(s2);

      n = buffer_read_ubyte(b);
      printf("%i\n",n);

      n = buffer_read_ubyte(b);
      printf("%i\n",n);

      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);

      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);

      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);

      n = buffer_read_ubyte(b);
      printf("%i\n",n);

      n = buffer_read_ubyte(b);
      printf("%i\n",n);
#if 0
      printflags8(n);
      //      0000,0000
      printf("      ^Follow To ???? NO\n");
      printf("     ^Specific Point ???? NO\n");
#endif
      n = buffer_read_ubyte(b);
      printf("%i\n",n);

      n = buffer_read_ushort(b);
      printf("%i\n",n);

    } else if (strcmp(s,"AI_T") == 0) {
      n = buffer_read_int(b);
      printf("NPC_/AI_T %i\n",n);
      f = buffer_read_float(b);
      printf("Location X %f\n",f);
      f = buffer_read_float(b);
      printf("Location Y %f\n",f);
      f = buffer_read_float(b);
      printf("Location Z %f\n",f);
      n = buffer_read_int(b);
      printf("%i (ai_tunknown)\n",n);
    } else if (strcmp(s,"DODT") == 0) {
      n = buffer_read_int(b);
      printf("NPC_/DODT %i\n",n);
      printf("AI Services Travel Services:\n");
      f = buffer_read_float(b);
      printf("Location X %f\n",f);
      f = buffer_read_float(b);
      printf("Location Y %f\n",f);
      f = buffer_read_float(b);
      printf("Location Z %f\n",f);
      f = buffer_read_float(b);
      printf("Rotation X %f\n",f);
      f = buffer_read_float(b);
      printf("Rotation Y %f\n",f);
      f = buffer_read_float(b);
      printf("Rotation Z %f\n",f);
    } else if (strcmp(s,"DNAM") == 0) {
      n = buffer_read_int(b);
      printf("NPC_/DNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("AI Services Travel Services Cell %s\n",s2);
      free(s2);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_int(b);
      printf("NPC_/SCRI %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Script \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"NPCS") == 0) {
      n = buffer_read_int(b);
      printf("NPC_/NPCS %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Spell \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"CNDT") == 0) {
      n = buffer_read_int(b);
      printf("NPC_/CNDT %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("AI Package Follow To \"%s\"\n",s2);
      free(s2);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of NPC\n");

  return -1;
}
