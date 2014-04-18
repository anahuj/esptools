
int parsebuffer_dobj(void *b)
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
      printf("DOBJ/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("DOBJ/DATA %i\n",n);
      size = n;
      n = buffer_read_int(b);
      printf("Stimpak FormID %i\n",n);
      n = buffer_read_int(b);
      printf("SuperStimpak FormID %i\n",n);
      n = buffer_read_int(b);
      printf("RadX FormID %i\n",n);
      n = buffer_read_int(b);
      printf("RadAway FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Morphine FormID %i\n",n);
      n = buffer_read_int(b);
      printf("PerkParalysis FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Player Faction FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Mysterious Stranger NPC FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Mysterious Stranger Faction FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Default Music FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Battle Music FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Death Music FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Success Music FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Level Up Music FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Player Voice (Male) FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Player Voice (Male Child) FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Player Voice (Female) FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Player Voice (Female Child) FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Eat Package Default Food FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Every Actor Ability FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Drug Wears Off Image Space FormID %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of DOBJ\n");

  return -1;
}
