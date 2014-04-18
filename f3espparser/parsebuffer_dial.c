
int parsebuffer_dial(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int num_qsti;
  char *dial_edid;
  int size;

  num_qsti = 0;
  dial_edid = NULL;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("DIAL/EDID %i\n",n);
      dial_edid = buffer_read_nstring(b,n);
      printf("%s\n",dial_edid);
      // free(dial_edid);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("DIAL/FULL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Topic Text \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"QSTI") == 0) {
      n = buffer_read_short(b);
      printf("DIAL/QSTI %i\n",n);
      n = buffer_read_int(b);
      printf("Quest FormID %i\n",n);
      num_qsti++;
    } else if (strcmp(s,"DATA") == 0) { // F
      n = buffer_read_short(b);
      printf("DIAL/DATA %i\n",n);
      size = n;
      n = buffer_read_ubyte(b);
      printf("Dialogue Type %i %% 0 Topics 1 Conversation 2 Combat 3 Persuasion 4 Detection 5 Service 6 Misc 7 Radio\n",n);
      if (size >= 2) {
	n = buffer_read_byte(b); // F
	printflags8(n);
	//      0000,0000
	printf("        ^Rumors\n");
	printf("       ^Top-level\n");
      }
    } else if (strcmp(s,"PNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("DIAL/PNAM %i\n",n);
      f = buffer_read_float(b);
      printf("Priority %f\n",f);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of DIAL\n");
  printf("dialqsti: %i / %i / \"%s\"\n",num_qsti,global_formid,dial_edid);
  free(dial_edid);

  return -1;
}
