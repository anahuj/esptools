
int parsebuffer_skil(void *b)
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
      printf("SKIL/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"INDX") == 0) {
      n = buffer_read_short(b);
      printf("SKIL/INDX %i\n",n);
      n = buffer_read_int(b);
      printf("Skill Index %i\n",n);
    } else if (strcmp(s,"DESC") == 0) {
      n = buffer_read_short(b);
      printf("SKIL/DESC %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Skill Description \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("SKIL/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Skill Image \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("SKIL/DATA %i\n",n);
      n = buffer_read_int(b);
      printf("Skill Index %i\n",n);
      n = buffer_read_int(b);
      printf("Governing Attribute %i %% 0 Strength 1 Intelligence 2 Willpower 3 Agility 4 Speed 5 Endurance 6 Personality 7 Luck\n",n);
      n = buffer_read_int(b);
      printf("Specialization %i %% 0 Combat 1 Magic 2 Stealth\n",n);
      f = buffer_read_float(b);
      printf("Action 1 Use Value %f\n",f);
      f = buffer_read_float(b);
      printf("Action 2 Use Value %f\n",f);
    } else if (strcmp(s,"ANAM") == 0) {
      n = buffer_read_short(b);
      printf("SKIL/ANAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Apprentice Perk Text \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"JNAM") == 0) {
      n = buffer_read_short(b);
      printf("SKIL/JNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Journeyman Perk Text \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ENAM") == 0) {
      n = buffer_read_short(b);
      printf("SKIL/ENAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Expert Perk Text \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MNAM") == 0) {
      n = buffer_read_short(b);
      printf("SKIL/MNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Master Perk Text \"%s\"\n",s2);
      free(s2);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of SKIL\n");

  return -1;
}
