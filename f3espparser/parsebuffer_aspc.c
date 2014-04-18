
int parsebuffer_aspc(void *b)
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
      printf("ASPC/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"OBND") == 0) { // F
      n = buffer_read_short(b);
      printf("ASPC/OBND %i\n",n);
      parse_obnd(b);
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_short(b);
      printf("ASPC/SNAM %i\n",n);
      n = buffer_read_int(b);
      printf("Looping Sound FormID %i\n",n);
    } else if (strcmp(s,"ANAM") == 0) {
      n = buffer_read_short(b);
      printf("ASPC/ANAM %i\n",n);
      n = buffer_read_int(b);
      printf("Environment Type %i %% 0 None 1 Default 2 Generic 3 Paddedcell 4 Room 5 Bathroom 6 Livingroom 7 Stoneroom 8 Auditorium 9 Concerthall 10 Cave 11 Arena 12 Hangar 13 Carpetedhallway 14 Hallway 15 Stonecorridor 16 Alley 17 Forest 18 City 19 Mountains 20 Quarry 21 Plain 22 Parkinglot 23 Sewerpipe 24 Underwater 25 Smallroom 26 Mediumroom 27 Largeroom 28 Mediumhall 29 Largehall 30 Plate\n",n);
    } else if (strcmp(s,"RDAT") == 0) {
      n = buffer_read_short(b);
      printf("ASPC/RDAT %i\n",n);
      n = buffer_read_int(b);
      printf("Use Audio From Region (Interiors Only) FormID %i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of ASPC\n");

  return -1;
}
