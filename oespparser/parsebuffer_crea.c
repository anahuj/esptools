
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
      printf("%s\n",s2);
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
#if 0
#if PRINT_CREA_MODT_TO_FILE
      printf("creamodt%.3i\n",global_crea_modt_file_number);
      s2 = buffer_read_bytes(b,n);
      // Output to file.
      fname[0] = '\0';
      sprintf(fname,"creamodt%.3i",global_crea_modt_file_number);
      fp = fopen(fname,"w");
      // fprintf(fp,"%s\n",s2);
      fwrite(s2,1,n,fp);
      fclose(fp);
      free(s2);
      global_crea_modt_file_number++;
#else
      buffer_skip_bytes(b,n);
#endif
#endif
    } else if (strcmp(s,"NIFZ") == 0) {
      n = buffer_read_short(b);
      printf("CREA/NIFZ %i\n",n);
      s2 = buffer_read_nstring(b,n);
      for (i = 0; i < n-1; i++) { // Excluding the last 0.
	if (s2[i] == '\0') s2[i] = '\n';
      }
      printf("%s\n",s2);
      free(s2);
#if 0
    } else if (strcmp(s,"NIFT") == 0) { // XXXX Not in Oblivion.esm
      n = buffer_read_short(b);
      printf("CREA/NIFT %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
#endif
    } else if (strcmp(s,"ACBS") == 0) {
      n = buffer_read_short(b);
      printf("CREA/ACBS %i\n",n);
      flags = buffer_read_uint(b);
      printflags(flags);
      //      0000,0000,0000,0000,0000,0000,0000,0000
      printf("                                      ^Biped\n");
      printf("                                     ^Essential\n");
      printf("                                    ^Weapon & Shield\n");
      printf("                                   ^Respawn\n");
      printf("                                 ^Swims\n");
      printf("                                ^Flies\n");
      printf("                               ^Walks\n");
      printf("                              ^PC Level Offset\n");
      printf("                            ^??\n");
      printf("                           ^No low level processing\n");
      printf("                          ^??\n");
      printf("                         ^~Blood Spray\n");
      printf("                       ^~Blood Decal\n");
      printf("                    ^No Head\n");
      printf("                  ^No Right Arm\n");
      printf("                 ^No Left Arm\n");
      printf("                ^No Combat in Water\n");
      printf("               ^No Shadow\n");
      printf("             ^~Can Corpse Check\n");
      n = buffer_read_ushort(b);
      printf("Spell Pts %i\n",n);
      n = buffer_read_ushort(b);
      printf("Fatigue %i\n",n);
      n = buffer_read_ushort(b);
      printf("Barter Gold %i\n",n);
      n = buffer_read_short(b);
      printf("Level %i\n",n);
      n = buffer_read_ushort(b);
      printf("Calc min %i\n",n);
      n = buffer_read_ushort(b);
      printf("Calc max %i\n",n);
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_short(b);
      printf("CREA/SNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Faction FormID %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Rank %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"INAM") == 0) {
      n = buffer_read_short(b);
      printf("CREA/INAM %i\n",n);
      n = buffer_read_int(b);
      printf("Death Item FormID %i\n",n);
    } else if (strcmp(s,"SPLO") == 0) {
      n = buffer_read_short(b);
      printf("CREA/SPLO %i\n",n);
      n = buffer_read_int(b);
      printf("Spell FormID %i\n",n);
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
    } else if (strcmp(s,"AIDT") == 0) {
      n = buffer_read_short(b);
      printf("CREA/AIDT %i\n",n);
      n = buffer_read_ubyte(b);
      printf("AIAttr/Aggression %i\n",n);
      n = buffer_read_ubyte(b);
      printf("AIAttr/Confidence %i\n",n);
      n = buffer_read_ubyte(b);
      printf("AIAttr/Energy level %i\n",n);
      n = buffer_read_ubyte(b);
      printf("AIAttr/Responsibility %i\n",n);
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
      printf("AIAttr/Training Skill (Index) %i\n",n);
      n = buffer_read_ubyte(b);
      printf("AIAttr/Training Skill Value %i\n",n);
      n = buffer_read_ushort(b);
      printf("%i\n",n);
    } else if (strcmp(s,"PKID") == 0) {
      n = buffer_read_short(b);
      printf("CREA/PKID %i\n",n);
      n = buffer_read_int(b);
      printf("AI Package FormID %i\n",n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("CREA/DATA %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Type %i %% 0 Creature 1 Daedra 2 Undead 3 Humanoid 4 Horse 5 Giant\n",n);
      n = buffer_read_ubyte(b);
      printf("Skills/Combat %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skills/Magic %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skills/Stealth %i\n",n);
      n = buffer_read_ushort(b);
      printf("Soul %i %% 0 None 1 Petty 2 Lesser 3 Common 4 Greater 5 Grand\n",n);
      n = buffer_read_ushort(b);
      printf("Health %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ushort(b);
      printf("Attack Damage %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Attr/Str %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Attr/Int %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Attr/Wil %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Attr/Agi %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Attr/Spd %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Attr/End %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Personality %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Attr/Luc %i\n",n);
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
      printf("Sound Type %i\n",n);
      printf(" %% 0 Left Foot\n");
      printf(" %% 1 Right Foot\n");
      printf(" %% 2 Left Back Foot\n");
      printf(" %% 3 Right Back Foot\n");
      printf(" %% 4 Idle\n");
      printf(" %% 5 Aware\n");
      printf(" %% 6 Attack\n");
      printf(" %% 7 Hit\n");
      printf(" %% 8 Death\n");
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
    } else if (strcmp(s,"NIFT") == 0) { // F
      n = buffer_read_short(b);
      printf("CREA/NIFT %i\n",n);
      size = n;
      parse_nift(b,size);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of CREA\n");

  return -1;
}
