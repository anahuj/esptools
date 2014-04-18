
#define PRINT_CREA_MODT_TO_FILE 0

#if PRINT_CREA_MODT_TO_FILE
int global_crea_modt_file_number = 1;
#endif

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

#if PRINT_CREA_MODT_TO_FILE
  char fname[20];
  FILE *fp;
#endif

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"NAME") == 0) {
      n = buffer_read_int(b);
      printf("CREA/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_int(b);
      printf("CREA/FNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_int(b);
      printf("CREA/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Model \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"NPDT") == 0) {
      n = buffer_read_int(b);
      printf("CREA/NPDT %i\n",n);
      n = buffer_read_int(b);
      printf("Type %i %% 0 Creature 1 Daedra 2 Undead 3 Humanoid\n",n);
      n = buffer_read_int(b);
      printf("Level %i\n",n);
      n = buffer_read_int(b);
      printf("Attributes Str %i\n",n);
      n = buffer_read_int(b);
      printf("Attributes Int %i\n",n);
      n = buffer_read_int(b);
      printf("Attributes Wil %i\n",n);
      n = buffer_read_int(b);
      printf("Attributes Agi %i\n",n);
      n = buffer_read_int(b);
      printf("Attributes Spd %i\n",n);
      n = buffer_read_int(b);
      printf("Attributes End %i\n",n);
      n = buffer_read_int(b);
      printf("Attributes Per %i\n",n);
      n = buffer_read_int(b);
      printf("Attributes Luc %i\n",n);
      n = buffer_read_int(b);
      printf("Health %i\n",n);
      n = buffer_read_int(b);
      printf("Spell Pts %i\n",n);
      n = buffer_read_int(b);
      printf("Fatigue %i\n",n);
      n = buffer_read_int(b);
      printf("Soul %i\n",n);
      n = buffer_read_int(b);
      printf("Combat %i\n",n);
      n = buffer_read_int(b);
      printf("Magic %i\n",n);
      n = buffer_read_int(b);
      printf("Stealth %i\n",n);
      n = buffer_read_int(b);
      printf("Attack 1 Min %i\n",n);
      n = buffer_read_int(b);
      printf("Attack 1 Max %i\n",n);
      n = buffer_read_int(b);
      printf("Attack 2 Min %i\n",n);
      n = buffer_read_int(b);
      printf("Attack 2 Max %i\n",n);
      n = buffer_read_int(b);
      printf("Attack 3 Min %i\n",n);
      n = buffer_read_int(b);
      printf("Attack 3 Max %i\n",n);
      n = buffer_read_int(b);
      printf("AI Services Barter Gold %i\n",n);
    } else if (strcmp(s,"FLAG") == 0) {
      n = buffer_read_int(b);
      printf("CREA/FLAG %i\n",n);
      n = buffer_read_ushort(b);
      printflags16(n);
      //      0000,0000,0000,0000
      printf("                  ^Biped\n");
      printf("                 ^Respawns\n");
      printf("                ^WeaponShield\n");
      printf("               ^(unknown)\n");
      printf("             ^Swims\n");
      printf("            ^Flies\n");
      printf("           ^Walks\n");
      printf("          ^Essential\n");
      printf("     ^^Blood Texture: 00 Default (Red) 01 Skeleton (White) 10 Metal Sparks (Gold)\n");
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"NPCO") == 0) {
      n = buffer_read_int(b);
      printf("CREA/NPCO %i\n",n);
      n = buffer_read_int(b);
      printf("Item Count %i\n",n);
      s2 = buffer_read_nstring(b,32);
      printf("Item Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"AIDT") == 0) {
      n = buffer_read_int(b);
      printf("CREA/AIDT %i\n",n);
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
    } else if (strcmp(s,"AI_W") == 0) {
      n = buffer_read_int(b);
      printf("CREA/AI_W %i\n",n);
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
      printf("CREA/AI_F %i\n",n);
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

      n = buffer_read_ushort(b);
      printf("%i\n",n);
      n = buffer_read_ushort(b);
      printf("%i\n",n);

    } else if (strcmp(s,"AI_T") == 0) {
      n = buffer_read_int(b);
      printf("CREA/AI_T %i\n",n);
      f = buffer_read_float(b);
      printf("Location X %f\n",f);
      f = buffer_read_float(b);
      printf("Location Y %f\n",f);
      f = buffer_read_float(b);
      printf("Location Z %f\n",f);
      n = buffer_read_int(b);
      printf("%i (ai_tunknown)\n",n);
    } else if (strcmp(s,"SCRI") == 0) {
      n = buffer_read_int(b);
      printf("CREA/SCRI %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Script \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"NPCS") == 0) {
      n = buffer_read_int(b);
      printf("CREA/NPCS %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Spell \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"CNAM") == 0) {
      n = buffer_read_int(b);
      printf("CREA/CNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Sound Gen Creature \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"XSCL") == 0) {
      n = buffer_read_int(b);
      printf("CREA/XSCL %i\n",n);
      f = buffer_read_float(b);
      printf("Scale %f\n",f);
    } else if (strcmp(s,"INDX") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("CREA/INDX %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else {
      printf("Unknown chunk name\n");
      printhexdump(b,-4,120);
      exit(-1);
    }
    free(s);
  }

  printf("End of CREA\n");

  return -1;
}
