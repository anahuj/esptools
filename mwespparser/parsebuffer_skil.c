
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
    if (strcmp(s,"NAME") == 0) {
      n = buffer_read_int(b);
      printf("SKIL/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"INDX") == 0) {
      n = buffer_read_int(b);
      printf("SKIL/INDX %i\n",n);
      n = buffer_read_int(b);
      printf("Skill Index %i\n",n);
    } else if (strcmp(s,"DESC") == 0) {
      n = buffer_read_int(b);
      printf("SKIL/DESC %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Skill Description \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SKDT") == 0) {
      n = buffer_read_int(b);
      printf("SKIL/SKDT %i\n",n);
      n = buffer_read_int(b);
      printf("Governing Attribute %i %% 0 Strength 1 Intelligence 2 Willpower 3 Agility 4 Speed 5 Endurance 6 Personality 7 Luck\n",n);
      n = buffer_read_int(b);
      printf("Specialization %i %% 0 Combat 1 Magic 2 Stealth\n",n);
      f = buffer_read_float(b);
      printf("Action 1 Use Value %f\n",f);
      f = buffer_read_float(b);
      printf("Action 2 Use Value %f\n",f);
      f = buffer_read_float(b);
      printf("Action 3 Use Value %f\n",f);
      f = buffer_read_float(b);
      printf("Action 4 Use Value %f\n",f);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of SKIL\n");

  return -1;
}
