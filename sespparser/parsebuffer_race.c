
int parsebuffer_race(void *b)
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
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("RACE/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("RACE/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DESC") == 0) {
      n = buffer_read_short(b);
      printf("RACE/DESC %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Description \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SPLO") == 0) {
      n = buffer_read_short(b);
      printf("RACE/SPLO %i\n",n);
      n = buffer_read_int(b);
      printf("Spell FormID %i\n",n);
    } else if (strcmp(s,"XNAM") == 0) {
      n = buffer_read_short(b);
      printf("RACE/XNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Reactions Race FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Reactions Disposition Modifier %i\n",n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("RACE/DATA %i\n",n);
      n = buffer_read_byte(b);
      printf("Skill Bonus Skill %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Bonus Value %i\n",n);
      n = buffer_read_byte(b);
      printf("Skill Bonus Skill %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Bonus Value %i\n",n);
      n = buffer_read_byte(b);
      printf("Skill Bonus Skill %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Bonus Value %i\n",n);
      n = buffer_read_byte(b);
      printf("Skill Bonus Skill %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Bonus Value %i\n",n);
      n = buffer_read_byte(b);
      printf("Skill Bonus Skill %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Bonus Value %i\n",n);
      n = buffer_read_byte(b);
      printf("Skill Bonus Skill %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Bonus Value %i\n",n);
      n = buffer_read_byte(b);
      printf("Skill Bonus Skill %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Skill Bonus Value %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      f = buffer_read_float(b);
      printf("Male Bodies Height %f\n",f);
      f = buffer_read_float(b);
      printf("Female Bodies Height %f\n",f);
      f = buffer_read_float(b);
      printf("Male Bodies Weight %f\n",f);
      f = buffer_read_float(b);
      printf("Female Bodies Weight %f\n",f);
      n = buffer_read_int(b);
      printflags(n);
      //      0000,0000,0000,0000,0000,0000,0000,0000
      printf("                                      ^Playable\n");
    } else if (strcmp(s,"DNAM") == 0) {
      n = buffer_read_short(b);
      printf("RACE/DNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Default Hair Male FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Default Hair Female FormID %i\n",n);
    } else if (strcmp(s,"CNAM") == 0) {
      n = buffer_read_short(b);
      printf("RACE/CNAM %i\n",n);
      n = buffer_read_byte(b);
      printf("Default Hair Color ID %i (GMST sHairColor%i)\n",n,n);
    } else if (strcmp(s,"PNAM") == 0) {
      n = buffer_read_short(b);
      printf("RACE/PNAM %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"UNAM") == 0) {
      n = buffer_read_short(b);
      printf("RACE/UNAM %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"ATTR") == 0) {
      n = buffer_read_short(b);
      printf("RACE/ATTR %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Male Str %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Male Int %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Male Wil %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Male Agi %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Male Spd %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Male End %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Male Pers %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Male Luc %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Female Str %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Female Int %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Female Wil %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Female Agi %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Female Spd %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Female End %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Female Pers %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Female Luc %i\n",n);
    } else if (strcmp(s,"NAM0") == 0) {
      n = buffer_read_short(b);
      printf("RACE/NAM0 %i\n",n);
    } else if (strcmp(s,"NAM1") == 0) {
      n = buffer_read_short(b);
      printf("RACE/NAM1 %i\n",n);
    } else if (strcmp(s,"MNAM") == 0) {
      n = buffer_read_short(b);
      printf("RACE/MNAM %i\n",n);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_short(b);
      printf("RACE/FNAM %i\n",n);
    } else if (strcmp(s,"INDX") == 0) {
      n = buffer_read_short(b);
      printf("RACE/INDX %i\n",n);
      n = buffer_read_int(b);
      printf("Index %i\n",n);
#if 0
      index = n;
#endif
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("RACE/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
#if 1
      free(s2);
#else
      if (index < 0) {
	printf("no valid index in race\n");
      } else {
	race_models[index].modl = s2;
      }
#endif
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("RACE/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
#if 0
      if (index < 0) {
	printf("no valid index in race\n");
      } else {
	race_models[index].modb = f;
      }
#endif
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("RACE/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
#if 1
      free(s2);
#else
      if (index < 0) {
	printf("no valid index in race\n");
      } else {
	race_models[index].icon = s2;
      }
#endif
    } else if (strcmp(s,"HNAM") == 0) {
      n = buffer_read_short(b);
      printf("RACE/HNAM %i\n",n);
      m = n/4;
      for (i = 0; i < m; i++) {
	n = buffer_read_int(b);
	printf("Hair FormID %i\n",n);
      }
    } else if (strcmp(s,"ENAM") == 0) {
      n = buffer_read_short(b);
      printf("RACE/ENAM %i\n",n);
      m = n/4;
      for (i = 0; i < m; i++) {
	n = buffer_read_int(b);
	printf("Eye FormID %i\n",n);
      }
    } else if (strcmp(s,"FGGS") == 0) {
      n = buffer_read_short(b);
      printf("RACE/FGGS %i\n",n);
      for (i = 0; i < 50; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"FGGA") == 0) {
      n = buffer_read_short(b);
      printf("RACE/FGGA %i\n",n);
      for (i = 0; i < 30; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"FGTS") == 0) {
      n = buffer_read_short(b);
      printf("RACE/FGTS %i\n",n);
      for (i = 0; i < 50; i++) {
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_short(b);
      printf("RACE/SNAM %i\n",n);
      n = buffer_read_short(b);
      printf("%i\n",n);
    } else if (strcmp(s,"VNAM") == 0) {
      n = buffer_read_short(b);
      printf("RACE/VNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Male Voice Race %i\n",n);
      n = buffer_read_int(b);
      printf("Female Voice Race %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

#if 0
  if (index > 0) {
    for (i = 0; i <= index; i++) {
      switch (i) {
      case 0:
	printf("Head:\n");
	break;
      case 1:
	printf(":\n");
	break;
      case 2:
	printf(":\n");
	break;
      case 3:
	printf(":\n");
	break;
      case 4:
	printf(":\n");
	break;
      case 5:
	printf(":\n");
	break;
      case 6:
	printf(":\n");
	break;
      case 7:
	printf(":\n");
	break;
      default:
	printf("unknown index in race\n");
	break;
      }
    }
  }
#endif

  printf("End of RACE\n");

  return -1;
}
