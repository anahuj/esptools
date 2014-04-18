
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
      if (size >= 84) {
	n = buffer_read_byte(b);
	printf("Dodge %% Chance %i\n",n);
	n = buffer_read_byte(b);
	printf("Left/Right %% Chance %i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
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
	printf("%i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
	f = buffer_read_float(b);
	printf("Recoil/Stagger Bonus to Attack %f\n",f);
	f = buffer_read_float(b);
	printf("Unconscious Bonus to Attack %f\n",f);
	f = buffer_read_float(b);
	printf("Hand-To-Hand Bonus to Attack %f\n",f);
	n = buffer_read_byte(b);
	printf("Power Attack %% Chance %i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
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
	printf("%i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
	f = buffer_read_float(b);
	printf("Hold Timer Min %f\n",f);
	f = buffer_read_float(b);
	printf("Hold Timer Max %f\n",f);
	n = buffer_read_ubyte(b);
	printflags8(n);
	//      0000,0000
	printf("        ^Advanced exists\n");
	printf("       ^Movement (0) vs %% Chance (1)\n");
	printf("      ^Ignore Allies in Area\n");
	printf("     ^Will Yield\n");
	printf("   ^Rejects Yields\n");
	printf("  ^Fleeing Disabled\n");
	printf(" ^Prefers Ranged\n");
	printf("^Melee Alert OK\n");
	n = buffer_read_byte(b);
	printf("Acrobatic Dodge %% Chance %i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
      }
      if (size >= 92) {
	f = buffer_read_float(b);
	printf("Range Mult Optimal %f\n",f);
	f = buffer_read_float(b);
	printf("Range Mult Max %f\n",f);
      } else {
	printf("Range Mult Optimal 1.0 (default)\n");
	printf("Range Mult Max 1.0 (default)\n");
      }
      if (size >= 104) {
	f = buffer_read_float(b);
	printf("Switch Dist Melee %f\n",f);
	f = buffer_read_float(b);
	printf("Switch Dist Ranged %f\n",f);
	f = buffer_read_float(b);
	printf("Buff Standoff Distance %f\n",f);
      } else {
	printf("Switch Dist Melee 250.0 (default)\n");
	printf("Switch Dist Ranged 1000.0 (default)\n");
	printf("Buff Standoff Distance 325.0 (default)\n");
      }
      if (size >= 112) {
	f = buffer_read_float(b);
	printf("Ranged Standoff Distance %f\n",f);
	f = buffer_read_float(b);
	printf("Group Standoff Distance %f\n",f);
      } else {
	printf("Ranged Standoff Distance 500.0 (default)\n");
	printf("Group Standoff Distance 325.0 (default)\n");
      }
      if (size >= 120) {
	n = buffer_read_byte(b);
	printf("Rushing Attack %% Chance %i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
	f = buffer_read_float(b);
	printf("Rushing Attack Distance Mult %f\n",f);
      } else {
	printf("Rushing Attack %% Chance 25 (default)\n");
	printf("??\n");
	printf("??\n");
	printf("??\n");
	printf("Rushing Attack Distance Mult 1.0 (default)\n");
      }
      if (size >= 124) {
	n = buffer_read_int(b);
	printflags(n);
	//      0000,0000,0000,0000,0000,0000,0000,0000
	printf("                                      ^Do Not Acquire\n");
      }
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
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of CSTY\n");

  return -1;
}
