
int parsebuffer_body(void *b)
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
    if (strcmp(s,"NAME") == 0) {
      n = buffer_read_int(b);
      printf("BODY/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_int(b);
      printf("BODY/FNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Skin Info Race \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_int(b);
      printf("BODY/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"BYDT") == 0) {
      n = buffer_read_int(b);
      printf("BODY/BYDT %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Part %i %% 0 Head 1 Hair 2 Neck 3 Chest 4 Groin 5 Hand 6 Wrist 7 Forearm 8 Upper Arm 9 Foot 10 Ankle 11 Knee 12 Upper Leg 13 Clavicle 14 Tail\n",n);
      n = buffer_read_ubyte(b);
      printf("Skin Info Type %i %% 0 Normal 1 Vampire\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Female\n");
      printf("       ^~Playable\n");
      n = buffer_read_ubyte(b);
      printf("Part Type %i %% 0 Skin 1 Clothing 2 Armor\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of BODY\n");

  return -1;
}
