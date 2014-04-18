
int parsebuffer_npc(void *b)
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
      printf("NPC_/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"ACBS") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/ACBS %i\n",n);
      flags = buffer_read_uint(b);
      printflags(flags);
      //      0000,0000,0000,0000,0000,0000,0000,0000
      printf("                                      ^Female\n");
      printf("                                     ^Essential\n");
      printf("                                   ^Respawn\n");
      printf("                                 ^Auto Calc Stats\n");
      printf("                              ^PC Level Offset\n");
      printf("                           ^No low level processing\n");
      printf("                      ^No Rumors\n");
      printf("                     ^Summonable\n");
      printf("                    ^No Persuasion\n");
      printf("             ^Can Corpse check\n");
      n = buffer_read_ushort(b);
      printf("Base Spell Pts %i\n",n);
      n = buffer_read_ushort(b);
      printf("Fatigue %i\n",n);
      n = buffer_read_ushort(b);
      printf("Barter Gold %i\n",n);
      n = buffer_read_short(b);
      printf("Level %i\n",n);
      n = buffer_read_ushort(b);
      printf("Calc Min %i\n",n);
      n = buffer_read_ushort(b);
      printf("Calc Max %i\n",n);
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/SNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Faction FormID %i\n",n);
      n = buffer_read_byte(b);
      printf("Rank %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"INAM") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/INAM %i\n",n);
      n = buffer_read_int(b);
      printf("Death Item FormID %i\n",n);
    } else if (strcmp(s,"RNAM") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/RNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Race FormID %i\n",n);
    } else if (strcmp(s,"SPLO") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/SPLO %i\n",n);
      n = buffer_read_int(b);
      printf("Spell FormID %i\n",n);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/SCRI %i\n",n);
      n = buffer_read_int(b);
      printf("Script FormID %i\n",n);
    } else if (strcmp(s,"CNTO") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/CNTO %i\n",n);
      n = buffer_read_int(b);
      printf("Item FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Count %i\n",n);
    } else if (strcmp(s,"AIDT") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/AIDT %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Aggression %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Confidence %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Energy Level %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Responsibility %i\n",n);
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
      printf("Training Skill (Index) %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Training Skill Value %i\n",n);
      n = buffer_read_ushort(b);
      printf("%i\n",n);
    } else if (strcmp(s,"PKID") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/PKID %i\n",n);
      n = buffer_read_int(b);
      printf("AI Package FormID %i\n",n);
    } else if (strcmp(s,"CNAM") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/CNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Class FormID %i\n",n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/DATA %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Armorer %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Athletics %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Blade %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Block %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Blunt %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Hand To Hand %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Heavy Armor %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Alchemy %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Alteration %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Conjuration %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Destruction %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Illusion %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Mysticism %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Restoration %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Acrobatics %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Light Armor %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Marksman %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Mercantile %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Security %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Sneak %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Speechcraft %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Health %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("Str %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Int %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Wil %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Agi %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Spd %i\n",n);
      n = buffer_read_ubyte(b);
      printf("End %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Personality %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Luc %i\n",n);
    } else if (strcmp(s,"HNAM") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/HNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Hair FormID %i\n",n);
    } else if (strcmp(s,"LNAM") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/LNAM %i\n",n);
      f = buffer_read_float(b);
      printf("Hair Length %f\n",f);
    } else if (strcmp(s,"ENAM") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/ENAM %i\n",n);
      n = buffer_read_int(b);
      printf("Eyes FormID %i\n",n);
    } else if (strcmp(s,"HCLR") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/HCLR %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Hair Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Hair Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Hair Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"ZNAM") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/ZNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Combat Style FormID %i\n",n);
    } else if (strcmp(s,"FGGS") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/FGGS %i\n",n);
      for (i = 0; i < 50; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"FGGA") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/FGGA %i\n",n);
      for (i = 0; i < 30; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"FGTS") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/FGTS %i\n",n);
      for (i = 0; i < 50; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/FNAM %i\n",n);
      n = buffer_read_ushort(b);
      printf("%i\n",n);
    } else if (strcmp(s,"KFFZ") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/KFFZ %i\n",n);
      s2 = buffer_read_nstring(b,n);
      for (i = 0; i < n-1; i++) { // Excluding the last 0.
	if (s2[i] == '\0') s2[i] = '\n';
      }
      printf("%s\n",s2);
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
