
int parsebuffer_weap(void *b)
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
      printf("WEAP/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("WEAP/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("WEAP/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MOD2") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/MOD2 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Shell Casing \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MOD3") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/MOD3 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Scope Target NIF \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MOD4") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/MOD4 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("World Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("WEAP/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("WEAP/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"MO2T") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/MO2T %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"MO3T") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/MO3T %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("WEAP/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Inventory image \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/DNAM %i\n",n);
      size = n;
      n = buffer_read_int(b); // i
      printf("Animation Type %i %% 0 HandToHandMelee 1 OneHandMelee 2 TwoHandMelee 3 OneHandPistol 4 OneHandPistolEnergy 5 TwoHandRifle 6 TwoHandAutomatic 7 TwoHandRifleEnergy 8 TwoHandHandle 9 TwoHandLauncher 10 OneHandGrenade 11 OneHandMine 12 OneHandLunchboxMine\n",n);
      f = buffer_read_float(b); // f
      printf("Animation Multiplier %f\n",f);
      f = buffer_read_float(b); // f
      printf("Reach %f\n",f);
#if 0
      n = buffer_read_short(b); // ?? -88 -86 -192  byte byte??
      printf("%i\n",n);
#else
      // Two bytes is the final decision prior having the editor.
      n = buffer_read_byte(b); // ??
      printflags8(n);
      //      0000,0000
      printf("        ^Ignores Normal Weapon Resistance\n");
      printf("       ^Automatic\n");
      printf("      ^Has Scope\n");
      printf("     ^Can't Drop\n");
      printf("   ^Hide Backpack\n");
      printf("  ^Embedded Weapon\n");
      printf(" ^Don't Use 1st Person IS Animations\n");
      printf("^~Playable\n");
#if 0
      n = buffer_read_byte(b); // ??
      printflags8(n);
      //      0000,0000
      printf("   ^^^Hand Grip somewhere here\n");
#else
      n = buffer_read_ubyte(b);
      printf("Hand Grip %i %% 255 DEFAULT 171 HandGrip1 172 HandGrip2 173 HandGrip3\n",n);
#endif
#endif
      n = buffer_read_byte(b); // b
      printf("Ammo Use %i\n",n);
      n = buffer_read_byte(b); // b
      printf("Reload Anim %i %% 0-10 == ReloadA-ReloadK\n",n);
      f = buffer_read_float(b); // f
      printf("Min Spread %f\n",f);
      f = buffer_read_float(b); // f
      printf("Spread %f\n",f);
      f = buffer_read_float(b); // f
      printf("%f\n",f);
      f = buffer_read_float(b); // f
      printf("Sight FOV %f\n",f);
      n = buffer_read_int(b); // ??  == 0 in Fallout3.esm
      printf("%i\n",n);
      n = buffer_read_int(b); // i
      printf("Projectile FormID %i\n",n);
#if 0
      n = buffer_read_int(b); // ?? i  large 33640453 but also 76845
      printf("%i -- %x\n",n,n);
#else
      // Four bytes is the final decision prior having the editor.
      n = buffer_read_byte(b); // b
      printf("Base VATS To-Hit Chance %i\n",n);
#if 0
      n = buffer_read_byte(b); // b
      printflags8(n);
      //      0000,0000
      printf("   ^^^Attack Anim somewhere here\n");
#else
      n = buffer_read_ubyte(b);
      printf("Attack Anim %i %% 255 DEFAULT (See list in NOTES_FESPTEST)\n",n);
#endif
      n = buffer_read_byte(b); // b
      printf("#Projectiles %i\n",n);
      n = buffer_read_byte(b); // b
      printf("Embedded Weapon Actor Value %i %% ?? NONE 0 PerceptionCondition 1 EnduranceCondition 2 LeftAttackCondition 3 RightAttackCondition 4 LeftMobilityCondition 5 RightMobilityCondition 6 BrainCondition\n",n);
#endif
      f = buffer_read_float(b); // f
      printf("Range Min %f\n",f);
      f = buffer_read_float(b); // f
      printf("Range Max %f\n",f);
      n = buffer_read_int(b); // i
      printf("On Hit %i %% 0 Normal formula behavior 1 Dismember only 2 Explode only 3 No dismember/explode\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Player Only\n");
      printf("       ^NPCs Use Ammo\n");
      printf("      ^No Jam After Reload\n");
      printf("     ^Override Action Points\n");
      printf("   ^Minor Crime\n");
      printf("  ^Range Fixed\n");
      printf(" ^Not Used in Normal Combat\n");
      printf("^Override Damage to Weapon Mult\n");
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Don't Use 3rd Person IS Animations\n");
      printf("       ^Burst Shot\n");
      printf("     ^Long Bursts\n");
      n = buffer_read_ubyte(b);
      printf("%i (unused?)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused?)\n",n);
      f = buffer_read_float(b); // f
      printf("Animation Attack Multiplier %f\n",f);
      f = buffer_read_float(b); // f
      printf("Fire Rate %f\n",f);
      f = buffer_read_float(b); // f
      printf("Override Action Points %f\n",f);
      f = buffer_read_float(b); // f
      printf("Firing Rumble Left motor strength %f\n",f);
      f = buffer_read_float(b); // f
      printf("Firing Rumble Right motor strength %f\n",f);
      f = buffer_read_float(b); // f
      printf("Firing Rumble Duration %f\n",f);
      f = buffer_read_float(b); // f
      printf("Override Damage to Weapon Mult %f\n",f);
      f = buffer_read_float(b); // f
      printf("Animation Attack Shots per Sec %f\n",f);
      f = buffer_read_float(b); // f
      printf("Animation Reload Time %f\n",f);
      f = buffer_read_float(b); // f
      printf("Animation Jam Time %f\n",f);
      f = buffer_read_float(b); // f
      printf("Aim Arc %f\n",f);
      n = buffer_read_int(b); // i
      printf("Skill %i %% 34 Energy Weapons 37 Medicine 38 Melee Weapons 41 Small Guns 45 Unarmed\n",n);
      n = buffer_read_int(b); // i
      printf("Firing Rumble Pattern %i %% 0 Constant 1 Square 2 Triangle 3 Sawtooth\n",n);
      f = buffer_read_float(b); // f
      printf("Firing Rumble Wavelength %f\n",f);
      f = buffer_read_float(b); // f
      printf("Limb Dmg Mult %f\n",f);
      if (size >= 124) {
	n = buffer_read_int(b);
	printf("Resist %i %% -1 NONE 18 DamageResist 19 PoisonResist 20 RadResist 52 FireResist 58 ElectricResist 59 FrostResist 60 EnergyResist 61 EmpResist\n",n);
      }
      if (size >= 136) {
	f = buffer_read_float(b); // f
	printf("Sight Usage %f\n",f);
	f = buffer_read_float(b); // f
	printf("Semi-Automatic Fire Delay Min %f\n",f);
	f = buffer_read_float(b); // f
	printf("Semi-Automatic Fire Delay Max %f\n",f);
      }
    } else if (strcmp(s,"CRDT") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/CRDT %i\n",n);
      n = buffer_read_short(b);
      printf("Crit Dmg %i\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      f = buffer_read_float(b);
      printf("Crit %% Mult %f\n",f);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Crit Effect On Death\n");
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_int(b);
      printf("Crit Effect FormID %i\n",n);
    } else if (strcmp(s,"DATA") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/DATA %i\n",n);
      n = buffer_read_int(b);
      printf("Value %i\n",n);
      n = buffer_read_int(b);
      printf("Health %i\n",n);
      f = buffer_read_float(b);
      printf("Weight %f\n",f);
      n = buffer_read_short(b);
      printf("Damage %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Clip Rounds %i\n",n);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_short(b);
      printf("WEAP/SCRI %i\n",n);
      n = buffer_read_int(b);
      printf("Script FormID %i\n",n);
    } else if (strcmp(s,"OBND") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/OBND %i\n",n);
      parse_obnd(b);
    } else if (strcmp(s,"NAM0") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/NAM0 %i\n",n);
      n = buffer_read_int(b);
      printf("Ammunition FormID %i\n",n);
    } else if (strcmp(s,"ETYP") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/ETYP %i\n",n);
      n = buffer_read_int(b);
      printf("Equip Type %i %% 0 BigGuns 1 EnergyWeapons 2 SmallGuns 3 MeleeWeapons 4 UnarmedWeapons 5 ThrowWeapons 6 Mine 7 BodyWear 8 HeadWear 9 HandWear 10 Chems 11 Stimpack 12 Food 13 Alcohol\n",n);
    } else if (strcmp(s,"NNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/NNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Embedded Weapon Node \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"INAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/INAM %i\n",n);
      n = buffer_read_int(b);
      printf("Impact Data Set FormID %i\n",n);
    } else if (strcmp(s,"SNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/SNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Attack Sound FormID %i\n",n);
    } else if (strcmp(s,"VNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/VNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Detection Sound Level %i %% 0 Loud 1 Normal 2 Silent\n",n);
    } else if (strcmp(s,"WNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/WNAM %i\n",n);
      n = buffer_read_int(b);
      printf("1st Person Model Object FormID %i\n",n);
    } else if (strcmp(s,"XNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/XNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Attack Sound (2D) FormID %i\n",n);
    } else if (strcmp(s,"TNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/TNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Attack Fail (No Ammo/Melee Miss) FormID %i\n",n);
    } else if (strcmp(s,"UNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/UNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Idle Sound FormID %i\n",n);
    } else if (strcmp(s,"NAM9") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/NAM9 %i\n",n);
      n = buffer_read_int(b);
      printf("Equip Sound FormID %i\n",n);
    } else if (strcmp(s,"NAM8") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/NAM8 %i\n",n);
      n = buffer_read_int(b);
      printf("UnEquip Sound FormID %i\n",n);
    } else if (strcmp(s,"NAM7") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/NAM7 %i\n",n);
      n = buffer_read_int(b);
      printf("Attack Loop FormID %i\n",n);
    } else if (strcmp(s,"NAM6") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/NAM6 %i\n",n);
      n = buffer_read_int(b);
      printf("Melee Block FormID %i\n",n);
    } else if (strcmp(s,"EITM") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/EITM %i\n",n);
      n = buffer_read_int(b);
      printf("Object Effect FormID %i\n",n);
    } else if (strcmp(s,"MICO") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/MICO %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Message Icon \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"REPL") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/REPL %i\n",n);
      n = buffer_read_int(b);
      printf("Repair Item List FormID %i\n",n);
    } else if (strcmp(s,"EFSD") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/EFSD %i\n",n);
      n = buffer_read_int(b);
      printf("Scope Effect FormID %i\n",n);
    } else if (strcmp(s,"YNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/YNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Pickup Sound FormID %i\n",n);
    } else if (strcmp(s,"ZNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/ZNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Putdown Sound FormID %i\n",n);
    } else if (strcmp(s,"BIPL") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/BIPL %i\n",n);
      n = buffer_read_int(b);
      printf("Armor List FormID %i\n",n);
    } else if (strcmp(s,"MODD") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/MODD %i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"EAMT") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/EAMT %i\n",n);
      n = buffer_read_short(b);
      printf("%i\n",n);
    } else if (strcmp(s,"DEST") == 0) {
      n = buffer_read_short(b);
      printf("WEAP/DEST %i\n",n);
      parse_dest(b);
    } else if (strcmp(s,"DSTD") == 0) {
      n = buffer_read_short(b);
      printf("WEAP/DSTD %i\n",n);
      parse_dstd(b);
    } else if (strcmp(s,"DSTF") == 0) {
      n = buffer_read_short(b);
      printf("WEAP/DSTF %i\n",n);
      // Empty.
    } else if (strcmp(s,"DMDL") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/DMDL %i\n",n);
      parse_dmdl(b,n);
    } else if (strcmp(s,"DMDT") == 0) { // F
      n = buffer_read_short(b);
      printf("WEAP/DMDT %i\n",n);
      parse_dmdt(b,n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of WEAP\n");

  return -1;
}
