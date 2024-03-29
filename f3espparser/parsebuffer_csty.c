
int parsebuffer_csty(void *b)
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
      printf("CSTY/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"CSTD") == 0) {
      n = buffer_read_short(b);
      printf("CSTY/CSTD %i\n",n);
      size = n;
      // size = 92 in Fallout3.esm
      n = buffer_read_byte(b);
      printf("Dodge %% Chance %i\n",n);
      n = buffer_read_byte(b);
      printf("Left/Right %% Chance %i\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      f = buffer_read_float(b);
      printf("Dodge L/R Timer Min %f\n",f);
      f = buffer_read_float(b);
      printf("Dodge L/R Timer Max %f\n",f);
      f = buffer_read_float(b);
      printf("Dodge Forward Timer Min %f\n",f);
      f = buffer_read_float(b);
      printf("Dodge Forward Timer Max %f\n",f);
      f = buffer_read_float(b);
      printf("Dodge Back Timer Min %f\n",f);
      f = buffer_read_float(b);
      printf("Dodge Back Timer Max %f\n",f);
      f = buffer_read_float(b);
      printf("Idle Timer Min %f\n",f);
      f = buffer_read_float(b);
      printf("Idle Timer Max %f\n",f);
      n = buffer_read_byte(b);
      printf("Block %% Chance %i\n",n);
      n = buffer_read_byte(b);
      printf("Attack %% Chance %i\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      f = buffer_read_float(b);
      printf("Recoil/Stagger Bonus to Attack %f\n",f);
      f = buffer_read_float(b);
      printf("Unconscious Bonus to Attack %f\n",f);
      f = buffer_read_float(b);
      printf("Hand-To-Hand Bonus to Attack %f\n",f);
      n = buffer_read_byte(b);
      printf("Power Attack %% Chance %i\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      f = buffer_read_float(b);
      printf("Recoil/Stagger Bonus to Power Attack %f\n",f);
      f = buffer_read_float(b);
      printf("Unconscious Bonus to Power Attack %f\n",f);
      n = buffer_read_byte(b);
      printf("Normal %i\n",n);
      n = buffer_read_byte(b);
      printf("Forward %i\n",n);
      n = buffer_read_byte(b);
      printf("Back %i\n",n);
      n = buffer_read_byte(b);
      printf("Left %i\n",n);
      n = buffer_read_byte(b);
      printf("Right %i\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      f = buffer_read_float(b);
      printf("Hold Timer Min %f\n",f);
      f = buffer_read_float(b);
      printf("Hold Timer Max %f\n",f);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^0 Movement 1 %%Chance\n");
      printf("       ^Melee Alert OK\n");
      printf("      ^Flee Based On Personal Survival\n");
      printf("   ^Ignore Threats\n");
      printf("  ^Ignore Damaging Self\n");
      printf(" ^Ignore Damaging Group\n");
      printf("^Ignore Damaging Spectators\n");
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Cannot Use Stealthboy\n");
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("Acrobatic Dodge %% Chance %i\n",n);
      n = buffer_read_byte(b);
      printf("Rushing Attack %% Chance %i\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      f = buffer_read_float(b);
      printf("Rushing Attack Distance Mult %f\n",f);
    } else if (strcmp(s,"CSAD") == 0) {
      n = buffer_read_short(b);
      printf("CSTY/CSAD %i\n",n);
      f = buffer_read_float(b);
      printf("Dodge Fatigue Mod Mult %f\n",f);
      f = buffer_read_float(b);
      printf("Dodge Fatigue Mod Base %f\n",f);
      f = buffer_read_float(b);
      printf("Encumb. Speed Mod Base %f\n",f);
      f = buffer_read_float(b);
      printf("Encumb. Speed Mod Mult %f\n",f);
      f = buffer_read_float(b);
      printf("Dodge While Under Attack Mult %f\n",f);
      f = buffer_read_float(b);
      printf("Dodge Not Under Attack Mult %f\n",f);
      f = buffer_read_float(b);
      printf("Dodge Back While Under Attack Mult %f\n",f);
      f = buffer_read_float(b);
      printf("Dodge Back Not Under Attack Mult %f\n",f);
      f = buffer_read_float(b);
      printf("Dodge Forward While Attacking Mult %f\n",f);
      f = buffer_read_float(b);
      printf("Dodge Forward Not Attacking Mult %f\n",f);
      f = buffer_read_float(b);
      printf("Block Skill Modifier Mult %f\n",f);
      f = buffer_read_float(b);
      printf("Block Skill Modifier Base %f\n",f);
      f = buffer_read_float(b);
      printf("Block While Under Attack Mult %f\n",f);
      f = buffer_read_float(b);
      printf("Block Not Under Attack Mult %f\n",f);
      f = buffer_read_float(b);
      printf("Attack Skill Modifier Mult %f\n",f);
      f = buffer_read_float(b);
      printf("Attack Skill Modifier Base %f\n",f);
      f = buffer_read_float(b);
      printf("Attack While Under Attack Mult %f\n",f);
      f = buffer_read_float(b);
      printf("Attack Not Under Attack Mult %f\n",f);
      f = buffer_read_float(b);
      printf("Attack During Block Mult %f\n",f);
      f = buffer_read_float(b);
      printf("Power Att. Fatigue Mod Base %f\n",f);
      f = buffer_read_float(b);
      printf("Power Att. Fatigue Mod Mult %f\n",f);
    } else if (strcmp(s,"CSSD") == 0) { // F
      n = buffer_read_short(b);
      printf("CSTY/CSSD %i\n",n);
      f = buffer_read_float(b);
      printf("Cover Behavior Cover Search Radius %f\n",f);
      f = buffer_read_float(b);
      printf("Cover Behavior Take Cover Chance %f\n",f);
      f = buffer_read_float(b);
      printf("Cover Behavior Wait Timer Min %f\n",f);
      f = buffer_read_float(b);
      printf("Cover Behavior Wait Timer Max %f\n",f);
      f = buffer_read_float(b);
      printf("Cover Behavior Wait to Fire Timer Min %f\n",f);
      f = buffer_read_float(b);
      printf("Cover Behavior Wait to Fire Timer Max %f\n",f);
      f = buffer_read_float(b);
      printf("Cover Behavior Fire Timer Min %f\n",f);
      f = buffer_read_float(b);
      printf("Cover Behavior Fire Timer Max %f\n",f);
      f = buffer_read_float(b);
      printf("Weapons Ranged Weapon Range Mult Min %f\n",f);
#if 0
      f = buffer_read_float(b);
      printf("%f\n",f);
#else
      n = buffer_read_int(b);
      printf("%i unknown\n",n);
#endif
      n = buffer_read_int(b);
      printf("Weapon Restrictions %i %% 0 None 1 Melee Only 2 Ranged Only\n",n);
      f = buffer_read_float(b);
      printf("Weapons Ranged Weapon Range Mult Max %f\n",f);
      f = buffer_read_float(b);
      printf("Misc Max Targeting FOV %f\n",f);
      f = buffer_read_float(b);
      printf("Misc Combat Radius %f\n",f);
      f = buffer_read_float(b);
      printf("Weapons Semi-Auto Firing Delay Mult Min %f\n",f);
      f = buffer_read_float(b);
      printf("Weapons Semi-Auto Firing Delay Mult Max %f\n",f);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of CSTY\n");

  return -1;
}
