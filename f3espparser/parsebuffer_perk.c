
int parsebuffer_perk(void *b)
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
  int numdata;

  numdata = 0;
  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("PERK/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("PERK/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("PERK/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Perk icon \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DESC") == 0) {
      n = buffer_read_short(b);
      printf("PERK/DESC %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Perk Description \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SCHR") == 0) {
      n = buffer_read_short(b);
      printf("PERK/SCHR %i\n",n);
      parse_schr(b);
    } else if (strcmp(s,"SCDA") == 0) {
      n = buffer_read_short(b);
      printf("PERK/SCDA %i\n",n);
      parse_scda(b,n);
    } else if (strcmp(s,"SCTX") == 0) {
      n = buffer_read_short(b);
      printf("PERK/SCTX %i\n",n);
      parse_sctx(b,n);
    } else if (strcmp(s,"EPF2") == 0) {
      n = buffer_read_short(b);
      printf("PERK/EPF2 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"CTDA") == 0) {
      n = buffer_read_short(b);
      printf("PERK/CTDA %i\n",n);
      parse_ctda(b,n);
    } else if (strcmp(s,"SCRO") == 0) {
      n = buffer_read_short(b);
      printf("PERK/SCRO %i\n",n);
      parse_scro(b);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("PERK/DATA %i\n",n);
      size = n;
      if (numdata == 0) {
	if (size == 4) {
	  n = buffer_read_byte(b);
	  printf("Trait %i %% 0 Off 1 On\n",n);
	  n = buffer_read_byte(b);
	  printf("Level %i\n",n);
	  n = buffer_read_byte(b);
	  printf("Num Ranks %i\n",n);
	  n = buffer_read_byte(b);
	  printf("Playable %i %% 0 Off 1 On\n",n);
	} else if (size == 5) {
	  n = buffer_read_byte(b);
	  printf("Trait %i %% 0 Off 1 On\n",n);
	  n = buffer_read_byte(b);
	  printf("Level %i\n",n);
	  n = buffer_read_byte(b);
	  printf("Num Ranks %i\n",n);
	  n = buffer_read_byte(b);
	  printf("Playable %i %% 0 Off 1 On\n",n);
	  n = buffer_read_byte(b);
	  printf("Hidden %i %% 0 Off 1 On\n",n);
	} else {
	  fprintf(stderr,"unknown first PERK DATA size %i\n",size);
	  exit(-1);
	}
      } else {
	if (size == 3) {
	  n = buffer_read_byte(b);
	  printf("Entry Point type %i %% see NOTES_FESPTEST for the list\n",n);
	  n = buffer_read_byte(b);
	  printf("Function %i %% 1 Set Value 2 Add Value 3 Multiply Value 8 Add Leveled List 9 Add Activate Choice\n",n);
	  n = buffer_read_byte(b);
	  printf("Number of tabs %i\n",n);
	} else if (size == 4) {
	  n = buffer_read_uint(b);
	  printf("Data1 FormID %i\n",n);
	} else if (size == 8) {
	  n = buffer_read_uint(b);
	  printf("Data1 FormID %i\n",n);
	  n = buffer_read_byte(b);
	  printf("Data2 %i\n",n);
	  n = buffer_read_byte(b);
	  printf("%i\n",n);
	  n = buffer_read_byte(b);
	  printf("%i\n",n);
	  n = buffer_read_byte(b);
	  printf("%i\n",n);
	} else {
	  fprintf(stderr,"unknown Perk Entry DATA size %i\n",size);
	  exit(-1);
	}
      }
      numdata++;
    } else if (strcmp(s,"PRKC") == 0) {
      n = buffer_read_short(b);
      printf("PERK/PRKC %i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"PRKE") == 0) {
      n = buffer_read_short(b);
      printf("PERK/PRKE %i\n",n);
      n = buffer_read_byte(b);
      printf("Type %i %% 0 Quest 1 Ability 2 Entry Point\n",n);
      n = buffer_read_byte(b);
      printf("Rank %i %% Editor displays Rank + 1\n",n);
      n = buffer_read_byte(b);
      printf("Priority %i\n",n);
    } else if (strcmp(s,"PRKF") == 0) {
      n = buffer_read_short(b);
      printf("PERK/PRKF %i\n",n);
      // Empty.
    } else if (strcmp(s,"EPFT") == 0) {
      n = buffer_read_short(b);
      printf("PERK/EPFT %i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"EPFD") == 0) {
      n = buffer_read_short(b);
      printf("PERK/EPFD %i\n",n);
      // Depends on the Operation and Function.
      f = buffer_read_float(b);
      printf("Function FloatData %f\n",f);
    } else if (strcmp(s,"EPF3") == 0) {
      n = buffer_read_short(b);
      printf("PERK/EPF3 %i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of PERK\n");

  return -1;
}
