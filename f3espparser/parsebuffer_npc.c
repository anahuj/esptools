
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

#if 1
  buffer2file(buffer_getbuf(b),buffer_getlen(b),"last_npc");
#endif

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
      printf("                                    ^Is CharGen Face Preset\n");
      printf("                                   ^Respawn\n");
      printf("                                 ^Auto Calc Stats\n");
      printf("                              ^PC Level Mult\n");
      printf("                           ^No low level processing\n");
      printf("                         ^~Blood Spray\n");
      printf("                       ^~Blood Decal\n");
      printf("             ^No VATS Melee\n");
      printf("           ^Can be all races\n");
      printf("          ^AI Data Autocalc Services\n");
      printf("      ^No Knockdowns\n");
      printf("     ^Not Pushable\n");
      printf(" ^No Rotating to Head-track\n");
      n = buffer_read_ushort(b);
      printf("Stats Fatigue %i\n",n);
      n = buffer_read_ushort(b);
      printf("Barter Gold %i ????\n",n);
      n = buffer_read_short(b);
      printf("Stats Level %i %% Level Mult if PC Level Mult = 1 (Val/1000 displayed)\n",n);
      n = buffer_read_ushort(b);
      printf("Stats Calc Min %i\n",n);
      n = buffer_read_ushort(b);
      printf("Stats Calc Max %i\n",n);
      n = buffer_read_ushort(b);
      printf("Stats Speed Mult %% %i\n",n);
      // F
      f = buffer_read_float(b);
      printf("Traits Alignment %f %% -900.0 VeryEvil -500.0 Evil 0.0 Neutral 500.0 Good 900.0 VeryGood\n",f);
      n = buffer_read_short(b);
      printf("Traits Disposition Base %i\n",n);
      n = buffer_read_short(b);
      printf("Template Data:\n");
      printflags16(n);
      //      0000,0000,0000,0000
      printf("                  ^Use Traits\n");
      printf("                 ^Use Stats\n");
      printf("                ^Use Factions\n");
      printf("               ^Use Actor Effect List\n");
      printf("             ^Use AI Data\n");
      printf("            ^Use AI Packages\n");
      printf("           ^Use Model/Animation\n");
      printf("          ^Use Base Data\n");
      printf("        ^Use Inventory\n");
      printf("       ^Use Script\n");
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
      printf("Actor Effect FormID %i\n",n);
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
      printf("AI Data Aggression %i %% 0 Unaggressive 1 Aggressive 2 Very Aggressive 3 Frenzied\n",n);
      n = buffer_read_ubyte(b);
      printf("AI Data Confidence %i %% 0 Cowardly 1 Cautious 2 Average 3 Brave 4 Foolhardy\n",n);
      n = buffer_read_ubyte(b);
      printf("AI Data Energy %i\n",n);
      n = buffer_read_ubyte(b);
      printf("AI Data Responsibility %i\n",n);
      n = buffer_read_ubyte(b);
      printf("AI Data Mood %i %% 0 Neutral 1 Afraid 2 Annoyed 3 Cocky 4 Drugged 5 Pleasant 6 Angry 7 Sad\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      flags = buffer_read_uint(b);
      printflags(flags);
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
      printf("Training Skill (Index) %i %% 0 Barter 1 Big Guns 2 Energy Weapons 3 Explosives 4 Lockpick 5 Medicine 6 Melee Weapons 7 Repair 8 Science 9 Small Guns 10 Sneak 11 Speech 13 Unarmed\n",n);
      n = buffer_read_ubyte(b);
      printf("Training Skill Value %i\n",n);
      n = buffer_read_ubyte(b);
      printf("AI Data Assistance %i %% 0 Helps Nobody 1 Helps Allies 2 Helps Friends and Allies\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Aggro Radius Behavior\n");
      n = buffer_read_ushort(b);
      printf("AI Data Aggro Radius %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
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
    } else if (strcmp(s,"DNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("NPC_/DNAM %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Barter %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Big Guns %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Energy Weapons %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Explosives %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Lockpick %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Medicine %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Melee Weapons %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Repair %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Science %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Small Guns %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Sneak %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Speech %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("Unarmed %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Barter Offset %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Big Guns Offset %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Energy Weapons Offset %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Explosives Offset %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Lockpick Offset %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Medicine Offset %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Melee Weapons Offset %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Repair Offset %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Science Offset %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Small Guns Offset %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Sneak Offset %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Speech Offset %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("Unarmed Offset %i\n",n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/DATA %i\n",n);
      size = n;
      n = buffer_read_ubyte(b);
      printf("Stats Base Health %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("Stats Attributes Str %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Stats Attributes Per %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Stats Attributes End %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Stats Attributes Cha %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Stats Attributes Int %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Stats Attributes Agi %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Stats Attributes Luc %i\n",n);
      if (size >= 25) {
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
      }
#if 0
      // O
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
#endif
    } else if (strcmp(s,"HNAM") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/HNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Head Parts Hair FormID %i\n",n);
    } else if (strcmp(s,"LNAM") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/LNAM %i\n",n);
      f = buffer_read_float(b);
      printf("Hair Length %f\n",f);
    } else if (strcmp(s,"ENAM") == 0) {
      n = buffer_read_short(b);
      printf("NPC_/ENAM %i\n",n);
      n = buffer_read_int(b);
      printf("Head Parts Eyes FormID %i\n",n);
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
    } else if (strcmp(s,"OBND") == 0) { // F
      n = buffer_read_short(b);
      printf("NPC_/OBND %i\n",n);
      parse_obnd(b);
    } else if (strcmp(s,"VTCK") == 0) { // F
      n = buffer_read_short(b);
      printf("NPC_/VTCK %i\n",n);
      n = buffer_read_int(b);
      printf("Voice Type FormID %i\n",n);
    } else if (strcmp(s,"TPLT") == 0) { // F
      n = buffer_read_short(b);
      printf("NPC_/TPLT %i\n",n);
      n = buffer_read_int(b);
      printf("Template Data ActorBase FormID %i\n",n);
    } else if (strcmp(s,"EAMT") == 0) { // F
      n = buffer_read_short(b);
      printf("NPC_/EAMT %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Use Animation %i %% 255 ANY  Refer to NOTES_FESPTEST for the list (in CREA section)\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"PNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("NPC_/PNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Head Parts Head Part FormID %i\n",n);
    } else if (strcmp(s,"NAM4") == 0) { // F
      n = buffer_read_short(b);
      printf("NPC_/NAM4 %i\n",n);
      n = buffer_read_int(b);
      printf("Impact Material Type %i %% 0 Stone 1 Dirt 2 Grass 3 Glass 4 Metal 5 Wood 6 Organic 7 Cloth 8 Water 9 Hollow Metal 10 Organic Bug 11 Organic Glow\n",n);
    } else if (strcmp(s,"NAM5") == 0) { // F
      n = buffer_read_short(b);
      printf("NPC_/NAM5 %i\n",n);
      n = buffer_read_short(b); // byte + byte?
      printf("%i\n",n);
    } else if (strcmp(s,"NAM6") == 0) { // F
      n = buffer_read_short(b);
      printf("NPC_/NAM6 %i\n",n);
      f = buffer_read_float(b);
      printf("Traits Height %f\n",f);
    } else if (strcmp(s,"NAM7") == 0) { // F
      n = buffer_read_short(b);
      printf("NPC_/NAM7 %i\n",n);
      f = buffer_read_float(b);
      printf("Traits Weight %f\n",f);
    } else if (strcmp(s,"COED") == 0) { // F
      n = buffer_read_short(b);
      printf("NPC_/COED %i\n",n);
      parse_coed(b);
    } else if (strcmp(s,"EITM") == 0) { // F
      n = buffer_read_short(b);
      printf("NPC_/EITM %i\n",n);
      n = buffer_read_int(b);
      printf("Unarmed Attack Effect FormID %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of NPC\n");

  return -1;
}
