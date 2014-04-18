
int parsebuffer_regn(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f,g;
  unsigned int flags;
  int num;
  int tmploc;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("REGN/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"RCLR") == 0) {
      n = buffer_read_short(b);
      printf("REGN/RCLR %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Map Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Map Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Map Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"WNAM") == 0) {
      n = buffer_read_short(b);
      printf("REGN/WNAM %i\n",n);
      n = buffer_read_int(b);
      printf("World Space FormID %i\n",n);
    } else if (strcmp(s,"RPLI") == 0) {
      n = buffer_read_short(b);
      printf("REGN/RPLI %i\n",n);
      n = buffer_read_int(b);
      printf("Edge Fall-off %i\n",n);
    } else if (strcmp(s,"RPLD") == 0) {
      n = buffer_read_short(b);
      printf("REGN/RPLD %i\n",n);
      m = n/8;
      for (i = 0; i < m; i++) {
	f = buffer_read_float(b);
	g = buffer_read_float(b);
	printf("%f, %f\n",f,g);
      }
    } else if (strcmp(s,"RDAT") == 0) {
      n = buffer_read_short(b);
      printf("REGN/RDAT %i\n",n);
      n = buffer_read_int(b);
      printf("Region Data Type %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Override\n");
      n = buffer_read_ubyte(b);
      printf("Priority %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"RDMP") == 0) {
      n = buffer_read_short(b);
      printf("REGN/RDMP %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Map Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"RDMD") == 0) {
      n = buffer_read_short(b);
      printf("REGN/RDMD %i\n",n);
      n = buffer_read_int(b);
      printf("Music Type %i %% 0 Default\n",n);
    } else if (strcmp(s,"RDSD") == 0) {
      n = buffer_read_short(b);
      printf("REGN/RDSD %i\n",n);
      m = n/12;
      for (i = 0; i < m; i++) {
	n = buffer_read_int(b);
	printf("Sound FormID %i\n",n);
	n = buffer_read_int(b);
	printflags(n);
	//      0000,0000,0000,0000,0000,0000,0000,0000
	printf("                                      ^Pleasant\n");
	printf("                                     ^Cloudy\n");
	printf("                                    ^Rainy\n");
	printf("                                   ^Snowy\n");
	n = buffer_read_int(b);
	printf("Chance %i (%f)\n",n,(float)n/100000.0);
      }
    } else if (strcmp(s,"RDOT") == 0) {
      n = buffer_read_short(b);
      printf("REGN/RDOT %i\n",n);
      m = n/52;
      for (i = 0; i < m; i++) {
	printf("Object Tree/Object %i:\n",i);
	n = buffer_read_int(b);
	printf("Generated Object FormID %i\n",n);
	n = buffer_read_short(b);
	printf("Hierarchy Parent Index %i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i (unused)\n",n);
	n = buffer_read_ubyte(b);
	printf("%i (unused)\n",n);
	f = buffer_read_float(b);
	printf("Density %f\n",f);
	n = buffer_read_ubyte(b);
	printf("Clustering %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Min Slope %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Max Slope %i\n",n);
	n = buffer_read_ubyte(b);
	printflags8(n);
	//      0000,0000
	printf("        ^Conform to Slope\n");
	printf("       ^Paint Vertices\n");
	printf("      ^SizeVar+-\n");
	printf("     ^AngleVarX+-\n");
	printf("   ^AngleVarY+-\n");
	printf("  ^AngleVarZ+-\n");
	printf(" ^Is a Tree\n");
	printf("^Is a Huge Rock\n");
	n = buffer_read_short(b);
	printf("Radius wrt Parent %i\n",n);
	n = buffer_read_short(b);
	printf("Radius %i\n",n);
	f = buffer_read_float(b);
	printf("Min Height %f\n",f);
	f = buffer_read_float(b);
	printf("Max Height %f\n",f);
	f = buffer_read_float(b);
	printf("Sink %f\n",f);
	f = buffer_read_float(b);
	printf("Sink Variance %f\n",f);
	f = buffer_read_float(b);
	printf("Size Variance %f\n",f);
	n = buffer_read_short(b);
	printf("Angle Variance X %i\n",n);
	n = buffer_read_short(b);
	printf("Angle Variance Y %i\n",n);
	n = buffer_read_short(b);
	printf("Angle Variance Z %i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i (unused)\n",n);
	n = buffer_read_ubyte(b);
	printf("%i (unused)\n",n);
	n = buffer_read_ubyte(b);
	printf("Vertex Color R %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Vertex Color G %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Vertex Color B %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Percent of Radius %i\n",n);
      }
    } else if (strcmp(s,"RDWT") == 0) { // F check CLMT/WLST
      n = buffer_read_short(b);
      printf("REGN/RDWT %i\n",n);
      num = n/12;
      for (i = 0; i < num; i++) {
	n = buffer_read_int(b);
	printf("Weather FormID %i\n",n);
	n = buffer_read_int(b);
	printf("Weather Probability %i\n",n);
	n = buffer_read_int(b); // F
	printf("%i\n",n);
      }
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("REGN/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"RDGS") == 0) {
      n = buffer_read_short(b);
      printf("REGN/RDGS %i\n",n);
      num = n/8;
      for (i = 0; i < num; i++) {
	n = buffer_read_int(b);
	printf("Grass FormID %i\n",n);
	n = buffer_read_int(b);
	printf("%i\n",n);
      }
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of REGN\n");

  return -1;
}
