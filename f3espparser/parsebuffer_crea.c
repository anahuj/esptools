
int parsebuffer_crea(void *b)
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
  buffer2file(buffer_getbuf(b),buffer_getlen(b),"last_crea");
#endif

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("CREA/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("CREA/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("CREA/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Skeleton \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("CREA/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("CREA/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"NIFZ") == 0) {
      n = buffer_read_short(b);
      printf("CREA/NIFZ %i\n",n);
      s2 = buffer_read_nstring(b,n);
      for (i = 0; i < n-1; i++) { // Excluding the last 0.
	if (s2[i] == '\0') s2[i] = '\n';
      }
      printf("ModelList NIF files:\n");
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"ACBS") == 0) { // F
      n = buffer_read_short(b);
      printf("CREA/ACBS %i\n",n);
      flags = buffer_read_uint(b);
      printflags(flags);
      //      0000,0000,0000,0000,0000,0000,0000,0000
      printf("                                      ^Biped\n");
      printf("                                     ^Essential\n");
      printf("                                   ^Respawn\n");
      printf("                                 ^Swims\n");
      printf("                                ^Flies\n");
      printf("                               ^Walks\n");
      printf("                              ^PC Level Mult\n");
      printf("                            ^Inherits Sound From == NONE\n");
      printf("                           ^No low level processing\n");
      printf("                         ^~Blood Spray\n");
      printf("                       ^~Blood Decal\n");
      printf("                    ^No Head\n");
      printf("                  ^No Right Arm\n");
      printf("                 ^No Left Arm\n");
      printf("                ^No Combat in Water\n");
      printf("               ^No Shadow\n");
      printf("             ^No VATS Melee\n");
      printf("            ^Allow PC Dialogue\n");
      printf("           ^Can't Open Doors\n");
      printf("          ^AI Data Autocalc Services and Immobile (both tested ok, strange)\n");
      printf("        ^Tilt Front/Back\n");
      printf("       ^Tilt Left/Right\n");
      printf("      ^No Knockdowns\n");
      printf("     ^Not Pushable\n");
      printf("   ^Allow Pickpocket\n");
      printf("  ^Is Ghost\n");
      printf(" ^No Rotating to Head-track\n");
      printf("^Invulnerable\n");
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
      printf("CREA/SNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Faction FormID %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Rank %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"INAM") == 0) {
      n = buffer_read_short(b);
      printf("CREA/INAM %i\n",n);
      n = buffer_read_int(b);
      printf("Death Item FormID %i\n",n);
    } else if (strcmp(s,"SPLO") == 0) {
      n = buffer_read_short(b);
      printf("CREA/SPLO %i\n",n);
      n = buffer_read_int(b);
      printf("Actor Effect FormID %i\n",n);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_short(b);
      printf("CREA/SCRI %i\n",n);
      n = buffer_read_int(b);
      printf("Script FormID %i\n",n);
    } else if (strcmp(s,"CNTO") == 0) {
      n = buffer_read_short(b);
      printf("CREA/CNTO %i\n",n);
      n = buffer_read_int(b);
      printf("Item FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Count %i\n",n);
    } else if (strcmp(s,"AIDT") == 0) { // F
      n = buffer_read_short(b);
      printf("CREA/AIDT %i\n",n);
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
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"PKID") == 0) {
      n = buffer_read_short(b);
      printf("CREA/PKID %i\n",n);
      n = buffer_read_int(b);
      printf("AI Package FormID %i\n",n);
    } else if (strcmp(s,"DATA") == 0) { // F
      n = buffer_read_short(b);
      printf("CREA/DATA %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Traits Creature Type %i %% 0 Animal 1 Mutated Animal 2 Mutated Insect 3 Abomination 4 Super-Mutant 5 Feral Ghoul 6 Robot 7 Giant\n",n);
      n = buffer_read_ubyte(b);
      printf("Stats Combat Skill %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i unknown\n",n);
      n = buffer_read_ubyte(b);
      printf("%i unknown\n",n);
      n = buffer_read_ubyte(b);
      printf("Health %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i unknown\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("Attack Damage %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i unknown\n",n);
      n = buffer_read_ubyte(b);
      printf("Strength %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Perception %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Endurance %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Charisma %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Intelligence %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Agility %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Luck %i\n",n);
    } else if (strcmp(s,"ZNAM") == 0) {
      n = buffer_read_short(b);
      printf("CREA/ZNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Combat Style FormID %i\n",n);
    } else if (strcmp(s,"CSCR") == 0) {
      n = buffer_read_short(b);
      printf("CREA/CSCR %i\n",n);
      n = buffer_read_int(b);
      printf("Inherits Sounds From FormID %i\n",n);
    } else if (strcmp(s,"CSDT") == 0) {
      n = buffer_read_short(b);
      printf("CREA/CSDT %i\n",n);
      n = buffer_read_int(b);
      printf("Sound Type %i %% 0 Left Foot 1 Right Foot 2 Left Back Foot 3 Right Back Foot 4 Idle 5 Aware 6 Attack 7 Hit 8 Death 9 Weapon 10 Movement Loop 11 Conscious Loop\n",n);
    } else if (strcmp(s,"CSDI") == 0) {
      n = buffer_read_short(b);
      printf("CREA/CSDI %i\n",n);
      n = buffer_read_int(b);
      printf("Sound FormID %i\n",n);
    } else if (strcmp(s,"CSDC") == 0) {
      n = buffer_read_short(b);
      printf("CREA/CSDC %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Chance %i\n",n);
    } else if (strcmp(s,"RNAM") == 0) {
      n = buffer_read_short(b);
      printf("CREA/RNAM %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Attack Reach %i\n",n);
    } else if (strcmp(s,"TNAM") == 0) {
      n = buffer_read_short(b);
      printf("CREA/TNAM %i\n",n);
      f = buffer_read_float(b);
      printf("Turning Speed %f\n",f);
    } else if (strcmp(s,"BNAM") == 0) {
      n = buffer_read_short(b);
      printf("CREA/BNAM %i\n",n);
      f = buffer_read_float(b);
      printf("Base Scale %f\n",f);
    } else if (strcmp(s,"WNAM") == 0) {
      n = buffer_read_short(b);
      printf("CREA/WNAM %i\n",n);
      f = buffer_read_float(b);
      printf("Foot Weight %f\n",f);
    } else if (strcmp(s,"NAM0") == 0) {
      n = buffer_read_short(b);
      printf("CREA/NAM0 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Blood Spray Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"NAM1") == 0) {
      n = buffer_read_short(b);
      printf("CREA/NAM1 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Blood Decal Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"KFFZ") == 0) {
      n = buffer_read_short(b);
      printf("CREA/KFFZ %i\n",n);
      s2 = buffer_read_nstring(b,n);
      for (i = 0; i < n-1; i++) { // Excluding the last 0.
	if (s2[i] == '\0') s2[i] = '\n';
      }
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"OBND") == 0) { // F
      n = buffer_read_short(b);
      printf("CREA/OBND %i\n",n);
      parse_obnd(b);
    } else if (strcmp(s,"VTCK") == 0) { // F
      n = buffer_read_short(b);
      printf("CREA/VTCK %i\n",n);
      n = buffer_read_int(b);
      printf("Voice Type FormID %i\n",n);
    } else if (strcmp(s,"TPLT") == 0) { // F
      n = buffer_read_short(b);
      printf("CREA/TPLT %i\n",n);
      n = buffer_read_int(b);
      printf("Template Data ActorBase FormID %i\n",n);
    } else if (strcmp(s,"EAMT") == 0) { // F
      n = buffer_read_short(b);
      printf("CREA/EAMT %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Use Animation %i %% 255 ANY  Refer to NOTES_FESPTEST for the list\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"CNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("CREA/CNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Impact Data Set FormID %i\n",n);
    } else if (strcmp(s,"LNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("CREA/LNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Weapon List FormID %i\n",n);
    } else if (strcmp(s,"PNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("CREA/PNAM %i\n",n);
      n = buffer_read_int(b);
      printf("ModelList Body Part Data FormID %i\n",n);
    } else if (strcmp(s,"NAM4") == 0) { // F
      n = buffer_read_short(b);
      printf("CREA/NAM4 %i\n",n);
      n = buffer_read_int(b);
      printf("Impact Material Type %i %% 0 Stone 1 Dirt 2 Grass 3 Glass 4 Metal 5 Wood 6 Organic 7 Cloth 8 Water 9 Hollow Metal 10 Organic Bug 11 Organic Glow\n",n);
    } else if (strcmp(s,"NAM5") == 0) { // F
      n = buffer_read_short(b);
      printf("CREA/NAM5 %i\n",n);
      n = buffer_read_int(b);
      printf("Sound Level %i %% 0 Loud 1 Normal 2 Silent\n",n);
#if 0
      // NPC has Traits Height, not CREA.
    } else if (strcmp(s,"NAM6") == 0) { // F
      n = buffer_read_short(b);
      printf("CREA/NAM6 %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
#endif
#if 0
      // NPC has Traits Weight, not CREA.
    } else if (strcmp(s,"NAM7") == 0) { // F
      n = buffer_read_short(b);
      printf("CREA/NAM7 %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
#endif
    } else if (strcmp(s,"COED") == 0) { // F
      n = buffer_read_short(b);
      printf("CREA/COED %i\n",n);
      parse_coed(b);
    } else if (strcmp(s,"NIFT") == 0) { // F
      n = buffer_read_short(b);
      printf("CREA/NIFT %i\n",n);
      size = n;
      parse_nift(b,size);
    } else if (strcmp(s,"EITM") == 0) { // F
      n = buffer_read_short(b);
      printf("CREA/EITM %i\n",n);
      n = buffer_read_int(b);
      printf("Unarmed Attack Effect FormID %i\n",n);
    } else if (strcmp(s,"DEST") == 0) { // F
      n = buffer_read_short(b);
      printf("CREA/DEST %i\n",n);
      parse_dest(b);
    } else if (strcmp(s,"DSTD") == 0) { // F
      n = buffer_read_short(b);
      printf("CREA/DSTD %i\n",n);
      parse_dstd(b);
    } else if (strcmp(s,"DSTF") == 0) { // F
      n = buffer_read_short(b);
      printf("CREA/DSTF %i\n",n);
      // Empty.
    } else if (strcmp(s,"DMDL") == 0) { // F
      n = buffer_read_short(b);
      printf("CREA/DMDL %i\n",n);
      parse_dmdl(b,n);
    } else if (strcmp(s,"DMDT") == 0) { // F
      n = buffer_read_short(b);
      printf("CREA/DMDT %i\n",n);
      parse_dmdt(b,n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of CREA\n");

  return -1;
}
