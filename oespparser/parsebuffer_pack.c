
// Modified after F3

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
    } else if (strcmp(s,"PKDT") == 0) {
      n = buffer_read_short(b);
      printf("PACK/PKDT %i\n",n);
      size = n;
      n = buffer_read_uint(b);
      printflags(n);
      //      0000,0000,0000,0000,0000,0000,0000,0000
      printf("                                      ^Offers Services\n");
      printf("                                     ^Must Reach Location\n");
      printf("                                    ^Must Complete\n");
      printf("                                   ^Start/Lock Doors\n");
      printf("                                 ^End/Lock Doors\n");
      printf("                                ^Loc/Lock Doors\n");
      printf("                               ^Start/Unlock Doors\n");
      printf("                              ^End/Unlock Doors\n");
      printf("                            ^Loc/Unlock Doors\n");
      printf("                           ^Continue if PC near\n");
      printf("                          ^Once Per Day\n");
      printf("                       ^Skip Fallout Behavior\n");
      printf("                      ^Always Run\n");
      printf("                 ^Always Sneak\n");
      printf("                ^Allow Swimming\n");
      printf("               ^Allow Falls\n");
      printf("             ^Armor Unequipped\n");
      printf("            ^Weapons Unequipped\n");
      printf("           ^Defensive Combat\n");
      printf("          ^Use Horse\n");
      printf("        ^No Idle Anims\n");
      if (size >= 8) {
	n = buffer_read_byte(b);
	printf("Package Type %i %% 0 Find 1 Follow 2 Escort 3 Eat 4 Sleep 5 Wander 6 Travel 7 Accompany 8 Use Item At 9 Ambush 10 Flee not Combat 11 Cast Magic\n",n);
	n = buffer_read_byte(b);
	printf("%i (unused)\n",n);
	n = buffer_read_byte(b);
	printf("%i (unused)\n",n);
	n = buffer_read_byte(b);
	printf("%i (unused)\n",n);
      }
    } else if (strcmp(s,"PLDT") == 0) {
      n = buffer_read_short(b);
      printf("PACK/PLDT %i\n",n);
      n = buffer_read_int(b);
      printf("Type %i %% 0 Near Reference 1 In Cell 2 Near Current Location 3 Near Editor Location\n",n);
      n = buffer_read_int(b);
      printf("Reference FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Radius %i (for types 0 2 3)\n",n);
    } else if (strcmp(s,"PSDT") == 0) {
      n = buffer_read_short(b);
      printf("PACK/PSDT %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Month %i %% 1 February 255 Any\n",n);
      n = buffer_read_ubyte(b);
      printf("Day of week %i %% 0 Sunday 255 Any\n",n);
      n = buffer_read_ubyte(b);
      printf("Date %i %% 0 Any\n",n);
      n = buffer_read_ubyte(b);
      printf("Time %i %% 255 Any\n",n);
      n = buffer_read_int(b);
      printf("Duration %i %% 0 None\n",n);
    } else if (strcmp(s,"PTDT") == 0) {
      n = buffer_read_short(b);
      printf("PACK/PTDT %i\n",n);
      n = buffer_read_int(b);
      printf("Type %i %% 0 Specific Reference 1 Any Object (ID) 2 Any Object (Type)\n",n);
      n = buffer_read_int(b);
      printf("Ref/Object FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Distance (for type 0)/Count (for types 1 2) %i\n",n);
    } else if (strcmp(s,"CTDA") == 0) {
      n = buffer_read_short(b);
      printf("PACK/CTDA %i\n",n);
      parse_ctda(b);
    } else if (strcmp(s,"CTDT") == 0) {
      n = buffer_read_short(b);
      printf("PACK/CTDT %i\n",n);
      parse_ctdt(b);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of PACK\n");

  return -1;
}
