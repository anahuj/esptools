
int parsebuffer_info(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int size;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"DATA") == 0) {
      n = buffer_read_int(b);
      printf("INFO/DATA %i\n",n);
      n = buffer_read_int(b);
      printf("Dialogue Type %i %% 0 Topic 1 Voice 2 Greeting 3 Persuasion 4 Journal\n",n);
      n = buffer_read_int(b);
      printf("Disp/Index %i\n",n);
      n = buffer_read_byte(b);
      printf("Rank %i\n",n);
      n = buffer_read_byte(b);
      printf("Sex %i %% 0 Male 1 Female\n",n);
      n = buffer_read_byte(b);
      printf("PC Rank %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"INAM") == 0) {
      n = buffer_read_int(b);
      printf("INFO/INAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Info ID \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"NNAM") == 0) {
      n = buffer_read_int(b);
      printf("INFO/NNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Next Info \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"PNAM") == 0) {
      n = buffer_read_int(b);
      printf("INFO/PNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Previous Info \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"NAME") == 0) {
      n = buffer_read_int(b);
      printf("INFO/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Info \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_int(b);
      printf("INFO/FNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Faction \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SCVR") == 0) {
      n = buffer_read_int(b);
      printf("INFO/SCVR %i\n",n);
      s2 = buffer_read_nstring(b,n);
      if (s2[1] == '1') {
	printf("INFO Function %s\n",s2);
      } else {
	printf("%s\n",s2);
      }
      free(s2);
    } else if (strcmp(s,"INTV") == 0) {
      n = buffer_read_int(b);
      printf("INFO/INTV %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"FLTV") == 0) {
      n = buffer_read_int(b);
      printf("INFO/FLTV %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"BNAM") == 0) {
      n = buffer_read_int(b);
      printf("INFO/BNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Result \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ONAM") == 0) {
      n = buffer_read_int(b);
      printf("INFO/ONAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Speaker ID \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ANAM") == 0) {
      n = buffer_read_int(b);
      printf("INFO/ANAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Cell \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DNAM") == 0) {
      n = buffer_read_int(b);
      printf("INFO/DNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("PC Faction \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"CNAM") == 0) {
      n = buffer_read_int(b);
      printf("INFO/CNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Class \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"RNAM") == 0) {
      n = buffer_read_int(b);
      printf("INFO/RNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Race \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SNAM") == 0) {
      n = buffer_read_int(b);
      printf("INFO/SNAM %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Sound Filename \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"QSTN") == 0) { // Tribunal.
      n = buffer_read_int(b);
      printf("INFO/QSTN %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Quest Name\n");
    } else if (strcmp(s,"QSTF") == 0) { // Tribunal.
      n = buffer_read_int(b);
      printf("INFO/QSTF %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Finished\n");
    } else if (strcmp(s,"QSTR") == 0) { // Tribunal.
      n = buffer_read_int(b);
      printf("INFO/QSTR %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Restart\n");
    } else if (strcmp(s,"ACDT") == 0) { // Savefile.
      n = buffer_read_int(b);
      printf("INFO/ACDT %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else {
      printf("Unknown chunk name\n");
      printhexdump(b,-4,120);
      exit(-1);
    }
    free(s);
  }

  printf("End of INFO\n");

  return -1;
}
