
int parsebuffer_pack(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int size;
  int num;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("PACK/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"PKDT") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/PKDT %i\n",n);
      size = n;
      if (size >= 4) {
	n = buffer_read_uint(b);
	printflags(n);
	//      0000,0000,0000,0000,0000,0000,0000,0000
	printf("                                      ^Offers Services\n");
	printf("                                     ^Must Reach Location\n");
	printf("                                    ^Must Complete\n");
	printf("                                   ^Start/Lock Doors\n");
	printf("                                 ^End/Lock Doors\n");
	printf("                                ^AtLoc/Lock Doors\n");
	printf("                               ^Start/Unlock Doors\n");
	printf("                              ^End/Unlock Doors\n");
	printf("                            ^AtLoc/Unlock Doors\n");
	printf("                           ^Continue if PC near\n");
	printf("                          ^Once Per Day\n");
	printf("                       ^~Enable Fallout Behavior\n");
	printf("                      ^Always Run\n");
	printf("                 ^Always Sneak\n");
	printf("                ^Allow Swimming\n");
	printf("               ^Allow Falls\n");
	printf("             ^HeadTracking Off\n");
	printf("            ^Weapons Unequipped\n");
	printf("           ^XXXX ????\n");
	printf("          ^Weapon Drawn\n");
	printf("        ^No Idle Anims\n");
	printf("       ^Pretend In Combat\n");
	printf("      ^Continue During Combat\n");
	printf("     ^No Combat Alert\n");
	printf("   ^XXXX ????\n");
      }
      if (size >= 8) {
	n = buffer_read_byte(b);
	printf("Package Type %i %% 0 Find 1 Follow 2 Escort 3 Eat 4 Sleep 5 Wander 6 Travel 7 Accompany 8 Use Item At 9 Ambush 10 Flee not Combat 12 SandBox 13 Patrol 14 Guard 15 Dialogue 16 Use Weapon\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
	n = buffer_read_ushort(b);
	printflags16(n);
	//      0000,0000,0000,0000
	printf("                  ^Hellos to player\n");
	printf("                 ^Random conversations\n");
	printf("                ^Observe combat behavior\n");
	printf("             ^Reaction to player actions\n");
	printf("            ^Friendly fire comments\n");
	printf("           ^Aggro Radius Behavior\n");
	printf("          ^Allow Idle Chatter\n");
	printf("        ^Avoid Radiation\n");
      }
      // F
      if (size >= 12) {
	n = buffer_read_byte(b);
	printflags8(n);
	//      0000,0000
	printf("        ^Ambush: Hide while ambushing + Sandbox: ~Eating\n");
	printf("       ^^Patrol: Repeatable (but which one?)\n");
	printf("       ^Sandbox: ~Sleeping\n");
	printf("      ^Sandbox: ~Conversation\n");
	printf("     ^Sandbox: ~Idle Markers\n");
	printf("   ^Sandbox: ~Furniture (other than beds)\n");
	printf("  ^Sandbox: ~Wandering\n");
	n = buffer_read_byte(b);
	printflags8(n);
	//      0000,0000
	printf("        ^Allow Buying\n");
	printf("       ^Allow Killing\n");
	printf("      ^Allow Stealing\n");
	n = buffer_read_byte(b);
	printf("%i (unused)\n",n);
	n = buffer_read_byte(b);
	printf("%i (unused)\n",n);
      }
    } else if (strcmp(s,"PLDT") == 0) {
      n = buffer_read_short(b);
      printf("PACK/PLDT %i\n",n);
      n = buffer_read_int(b);
      printf("Type %i %% 0 Specific reference 2 Near current location 3 Near editor location 6 Near linked reference\n",n);
      n = buffer_read_int(b);
      printf("Location FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Radius %i\n",n);
    } else if (strcmp(s,"PLD2") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/PLD2 %i\n",n);
      n = buffer_read_int(b);
      printf("Type %i %% 0 Specific reference 2 Near current location 3 Near editor location 6 Near linked reference 7 At package location\n",n);
      n = buffer_read_int(b);
      printf("Location FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Radius %i\n",n);
    } else if (strcmp(s,"PSDT") == 0) {
      n = buffer_read_short(b);
      printf("PACK/PSDT %i\n",n);
      n = buffer_read_byte(b);
      printf("Month %i %% -1 Any 0 January 1 February 2 March 3 April 4 May 5 June 6 July 7 August 8 September 9 October 10 November 11 December 12 Spring (MAM) 13 Summer (JJA) 14 Autumn (SON) 15 Winter (DJF)\n",n);
      n = buffer_read_byte(b);
      printf("Day of week %i %% -1 Any 0 Sunday 1 Monday 2 Tuesday 3 Wednesday 4 Thursday 5 Friday 6 Saturday 7 Weekdays (MTWTF) 8 Weekends (SS) 9 Monday, Wednesday, Friday 10 Tuesday, Thursday\n",n);
      n = buffer_read_ubyte(b);
      printf("Date %i %% 0 Any\n",n);
      n = buffer_read_byte(b);
      printf("Time %i %% -1 Any\n",n);
      n = buffer_read_int(b);
      printf("Duration %i\n",n);
    } else if (strcmp(s,"PTDT") == 0) {
      n = buffer_read_short(b);
      printf("PACK/PTDT %i\n",n);
      size = n;
      n = buffer_read_int(b);
      printf("Type %i %% 0 Specific Reference 1 Any Object 2 Object Type 3 Linked Ref\n",n);
      n = buffer_read_int(b);
      printf("Target FormID/Object Type %i %% 0 NONE 1 Activators 2 Armor 3 Books 4 Clothing 5 Containers 6 Doors 7 Ingredients 8 Lights 9 Miscellaneous 10 Flora 11 Furniture 12 Weapons: Any 13 Ammo 14 NPCs 15 Creatures 16 Keys 17 Alchemy 18 Food 19 All: Combat Wearable 20 All: Wearable 21 Weapons: NONE 22 Weapons: Melee 23 Weapons: Ranged 24 Actor Effects: Any 25 Actor Effects: Range Target 26 Actor Effects: Range Touch 27 Actor Effects: Range Self 28 Actors: Any\n",n);
      n = buffer_read_int(b);
      printf("Distance/Count %i\n",n);
      if (size >= 16) {
	n = buffer_read_int(b);
	printf("%i\n",n);
      }
    } else if (strcmp(s,"CTDA") == 0) {
      n = buffer_read_short(b);
      printf("PACK/CTDA %i\n",n);
      parse_ctda(b,n);
    } else if (strcmp(s,"CTDT") == 0) {
      n = buffer_read_short(b);
      printf("PACK/CTDT %i\n",n);
      parse_ctdt(b);
    } else if (strcmp(s,"POBA") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/POBA %i\n",n);
      // Empty.
    } else if (strcmp(s,"POEA") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/POEA %i\n",n);
      // Empty.
    } else if (strcmp(s,"POCA") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/POCA %i\n",n);
      // Empty.
    } else if (strcmp(s,"INAM") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/INAM %i\n",n);
      n = buffer_read_int(b);
      printf("Idle FormID %i\n",n);
    } else if (strcmp(s,"SCHR") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/SCHR %i\n",n);
      parse_schr(b);
    } else if (strcmp(s,"TNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/TNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Topic FormID %i\n",n);
    } else if (strcmp(s,"PKDD") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/PKDD %i\n",n);
      size = n;
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("FOV Value %i %% FOV = %i/2 = %i for large FOVs (FOV >= 80)\n",n,n,n/2);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("Dialogue Topic FormID %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^No Headtracking\n");
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Don't Control Target Movement\n");
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      if (size >= 16) {
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
      }
      if (size >= 20) {
	n = buffer_read_ubyte(b);
	printf("Dialogue Type %i %% 0 Conversation 1 Say To\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
      }
      if (size >= 24) {
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
      }
    } else if (strcmp(s,"PKE2") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/PKE2 %i\n",n);
      n = buffer_read_int(b);
      printf("Distance %i %% in Escort Target\n",n);
    } else if (strcmp(s,"SCDA") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/SCDA %i\n",n);
      parse_scda(b,n);
    } else if (strcmp(s,"SCTX") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/SCTX %i\n",n);
      parse_sctx(b,n);
    } else if (strcmp(s,"SCRO") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/SCRO %i\n",n);
      parse_scro(b);
    } else if (strcmp(s,"PKPT") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/PKPT %i\n",n);
      n = buffer_read_ushort(b);
      printflags16(n);
      //      0000,0000,0000,0000
      printf("                  ^Repeatable\n");
    } else if (strcmp(s,"PKFD") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/PKFD %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"CNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/CNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Combat Style FormID %i\n",n);
    } else if (strcmp(s,"PKW3") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/PKW3 %i\n",n);
      // XXXX Printout as bytes.
      n = buffer_read_int(b);
      printflags(n);
      //      0000,0000,0000,0000,0000,0000,0000,0000
      printf("                                      ^Always Hit\n");
      printf("                            ^Do No Damage\n");
      printf("                  ^Crouch to reload\n");
      printf("        ^Hold fire when blocked\n");
      n = buffer_read_short(b);
      printflags16(n);
      //      0000,0000,0000,0000
      printf("                  ^0 Fire Rate Auto fire 1 Fire Rate Volley fire\n");
      printf("        ^0 Fire Count Number of bursts 1 Fire Count Repeat fire\n");
      n = buffer_read_short(b);
      printf("Fire Count Number of bursts %i\n",n);
      n = buffer_read_short(b);
      printf("Fire Rate Shots per volley min %i\n",n);
      n = buffer_read_short(b);
      printf("Fire Rate Shots per volley max %i\n",n);
      f = buffer_read_float(b);
      printf("Fire Rate Pause between volleys min %f\n",f);
      f = buffer_read_float(b);
      printf("Fire Rate Pause between volleys max %f\n",f);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"PTD2") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/PTD2 %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("Target Ref FormID %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"IDLF") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/IDLF %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^0 Random 1 Run In Sequence\n");
      printf("      ^Do Once\n");
    } else if (strcmp(s,"IDLC") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/IDLC %i\n",n);
      size = n;
      if (size == 1) {
	n = buffer_read_ubyte(b);
	printf("Number of Idles %i\n",n);
      }
      if (size == 4) {
	n = buffer_read_int(b);
	printf("Number of Idles %i\n",n);
      }
    } else if (strcmp(s,"IDLT") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/IDLT %i\n",n);
      f = buffer_read_float(b);
      printf("Idle Timer Setting %f\n",f);
    } else if (strcmp(s,"IDLA") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/IDLA %i\n",n);
      // num = value of IDLC
      num = n/4;
      for (i = 0; i < num; i++) {
	n = buffer_read_int(b);
	printf("Idle FormID %i\n",n);
      }
    } else if (strcmp(s,"IDLB") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/IDLB %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
#if 0
      // num = value of IDLC  XXXX verify
      num = n/4;
      for (i = 0; i < num; i++) {
	n = buffer_read_int(b);
	printf("%i\n",n);
      }
#endif
    } else if (strcmp(s,"PUID") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/PUID %i\n",n);
      // Empty.
    } else if (strcmp(s,"PKED") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/PKED %i\n",n);
      // Empty.
    } else if (strcmp(s,"PKAM") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/PKAM %i\n",n);
      // Empty.
    } else if (strcmp(s,"SLSD") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/SLSD %i\n",n);
      parse_slsd(b);
    } else if (strcmp(s,"SCVR") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/SCVR %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"SCRV") == 0) { // F
      n = buffer_read_short(b);
      printf("PACK/SCRV %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of PACK\n");

  return -1;
}
