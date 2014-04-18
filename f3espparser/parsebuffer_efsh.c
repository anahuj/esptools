
int parsebuffer_efsh(void *b)
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
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("EFSH/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("EFSH/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Fill Texture Effect Texture \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ICO2") == 0) {
      n = buffer_read_short(b);
      printf("EFSH/ICO2 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Particle Shader Texture \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("EFSH/DATA %i\n",n);
      size = n;
      if (size >= 96) {
	n = buffer_read_ubyte(b);
	printflags8(n);
	//      0000,0000
	printf("        ^~Membrane Shader\n");
	printf("     ^~Particle Shader\n");
	printf("   ^Inverse (Edge Effect Color)\n");
	printf("  ^Affect Skin Only\n");
	n = buffer_read_ubyte(b);
	printf("%i (unused)\n",n);
	n = buffer_read_ubyte(b);
	printf("%i (unused\n",n);
	n = buffer_read_ubyte(b);
	printf("%i (unused\n",n);
	n = buffer_read_int(b);
	printf("Membrane Source Blend Mode %i %% 1 Zero 2 One 3 Source Color 4 Source Inverse Color 5 Source Alpha 6 Source Inverted Alpha 7 Dest Alpha 8 Dest Inverse Alpha 9 Dest Color 10 Dest Inverse Color 11 Source Alpha SAT\n",n);
	n = buffer_read_int(b);
	printf("Membrane Blend Operation %i %% 1 Add 2 Subtract 3 Reverse Subtract 4 Minimum 5 Maximum\n",n);
	n = buffer_read_int(b);
	printf("Membrane Z Test Function %i %% 3 Equal To 5 Greater Than 7 Greater Than or Equal To\n",n);
	n = buffer_read_ubyte(b);
	printf("Fill Color R %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Fill Color G %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Fill Color B %i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	f = buffer_read_float(b);
	printf("Fill Alpha Fade In Time %f\n",f);
	f = buffer_read_float(b);
	printf("Fill Full Alpha Time %f\n",f);
	f = buffer_read_float(b);
	printf("Fill Alpha Fade Out Time %f\n",f);
	f = buffer_read_float(b);
	printf("Fill Persistent Alpha Ratio [0-1] %f\n",f);
	f = buffer_read_float(b);
	printf("Fill Alpha Pulse Amplitude %f\n",f);
	f = buffer_read_float(b);
	printf("Fill Alpha Pulse Frequency %f\n",f);
	f = buffer_read_float(b);
	printf("Fill Texture Animation Speed U %f\n",f);
	f = buffer_read_float(b);
	printf("Fill Texture Animation Speed V %f\n",f);
	f = buffer_read_float(b);
	printf("Edge Effect/Fall Off %f\n",f);
	n = buffer_read_ubyte(b);
	printf("Edge Effect/Color R %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Edge Effect/Color G %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Edge Effect/Color B %i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	f = buffer_read_float(b);
	printf("Edge Effect/Alpha Fade In Time %f\n",f);
	f = buffer_read_float(b);
	printf("Edge Effect/Full Alpha Time %f\n",f);
	f = buffer_read_float(b);
	printf("Edge Effect/Alpha Fade Out Time %f\n",f);
	f = buffer_read_float(b);
	printf("Edge Effect/Persistent Alpha Ratio [0-1] %f\n",f);
	f = buffer_read_float(b);
	printf("Edge Effect/Alpha Pulse Amplitude %f\n",f);
	f = buffer_read_float(b);
	printf("Edge Effect/Alpha Pulse Frequency %f\n",f);
	f = buffer_read_float(b);
	printf("Fill Full Alpha Ratio [0-1] %f\n",f);
	f = buffer_read_float(b);
	printf("Edge Effect/Full Alpha Ratio [0-1] %f\n",f);
	n = buffer_read_int(b);
	printf("Membrane Dest Blend Mode %i %% 1 Zero 2 One 3 Source Color 4 Source Inverse Color 5 Source Alpha 6 Source Inverted Alpha 7 Dest Alpha 8 Dest Inverse Alpha 9 Dest Color 10 Dest Inverse Color 11 Source Alpha SAT\n",n);
      }
      if (size >= 224) {
	n = buffer_read_int(b);
	printf("Particle Source Blend Mode %i %% 1 Zero 2 One 3 Source Color 4 Source Inverse Color 5 Source Alpha 6 Source Inverted Alpha 7 Dest Alpha 8 Dest Inverse Alpha 9 Dest Color 10 Dest Inverse Color 11 Source Alpha SAT\n",n);
	n = buffer_read_int(b);
	printf("Particle Blend Operation %i %% 1 Add 2 Subtract 3 Reverse Subtract 4 Minimum 5 Maximum\n",n);
	n = buffer_read_int(b);
	printf("Particle Z Test Function %i %% 4 Normal 8 Always Show\n",n);
	n = buffer_read_int(b);
	printf("Particle Dest Blend Mode %i %% 1 Zero 2 One 3 Source Color 4 Source Inverse Color 5 Source Alpha 6 Source Inverted Alpha 7 Dest Alpha 8 Dest Inverse Alpha 9 Dest Color 10 Dest Inverse Color 11 Source Alpha SAT\n",n);
	f = buffer_read_float(b);
	printf("Particle Birth Ramp Up Time %f\n",f);
	f = buffer_read_float(b);
	printf("Full Particle Birth Time %f\n",f);
	f = buffer_read_float(b);
	printf("Particle Birth Ramp Down Time %f\n",f);
	f = buffer_read_float(b);
	printf("Full Partical Birth Count %f\n",f);
	f = buffer_read_float(b);
	printf("Persistant Particle Count %f\n",f);
	f = buffer_read_float(b);
	printf("Particle Life Time %f\n",f);
	f = buffer_read_float(b);
	printf("Particle Life Time +- %f\n",f);
	f = buffer_read_float(b);
	printf("Initial Speed Along Normal %f\n",f);
	f = buffer_read_float(b);
	printf("Acceleration Along Normal %f\n",f);
	f = buffer_read_float(b);
	printf("Initial Velocity X %f\n",f);
	f = buffer_read_float(b);
	printf("Initial Velocity Y %f\n",f);
	f = buffer_read_float(b);
	printf("Initial Velocity Z %f\n",f);
	f = buffer_read_float(b);
	printf("Acceleration X %f\n",f);
	f = buffer_read_float(b);
	printf("Acceleration Y %f\n",f);
	f = buffer_read_float(b);
	printf("Acceleration Z %f\n",f);
	f = buffer_read_float(b);
	printf("Scale Key 1 %f\n",f);
	f = buffer_read_float(b);
	printf("Scale Key 2 %f\n",f);
	f = buffer_read_float(b);
	printf("Scale Key 1 Time %f\n",f);
	f = buffer_read_float(b);
	printf("Scale Key 2 Time %f\n",f);
	n = buffer_read_ubyte(b);
	printf("Color Key 1 R %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Color Key 1 G %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Color Key 1 B %i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("Color Key 2 R %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Color Key 2 G %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Color Key 2 B %i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("Color Key 3 R %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Color Key 3 G %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Color Key 3 B %i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	f = buffer_read_float(b);
	printf("Color Alpha 1 %f\n",f);
	f = buffer_read_float(b);
	printf("Color Alpha 2 %f\n",f);
	f = buffer_read_float(b);
	printf("Color Alpha 3 %f\n",f);
	f = buffer_read_float(b);
	printf("Color Key Time 1 %f\n",f);
	f = buffer_read_float(b);
	printf("Color Key Time 2 %f\n",f);
	f = buffer_read_float(b);
	printf("Color Key Time 3 %f\n",f);
      }
      if (size >= 244) { // F
	f = buffer_read_float(b);
	printf("Initial Speed Along Normal +- %f\n",f);
	f = buffer_read_float(b);
	printf("Initial Rotation (deg) %f\n",f);
	f = buffer_read_float(b);
	printf("Initial Rotation (deg) +- %f\n",f);
	f = buffer_read_float(b);
	printf("Rotation Speed (deg/sec) %f\n",f);
	f = buffer_read_float(b);
	printf("Rotation Speed (deg/sec) +- %f\n",f);
      }
      if (size >= 248) { // F
	n = buffer_read_int(b);
	printf("Addon Models FormID %i\n",n);
      }
      if (size >= 284) { // F
	f = buffer_read_float(b);
	printf("Holes Start Time %f\n",f);
	f = buffer_read_float(b);
	printf("Holes End Time %f\n",f);
	f = buffer_read_float(b);
	printf("Holes Start Val %f\n",f);
	f = buffer_read_float(b);
	printf("Holes End Val %f\n",f);
	f = buffer_read_float(b);
	printf("Holes Edge Width %f\n",f);
	n = buffer_read_ubyte(b);
	printf("Holes Edge Color R %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Holes Edge Color G %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Holes Edge Color B %i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	f = buffer_read_float(b);
	printf("Explosion Wind Speed %f\n",f);
	n = buffer_read_int(b);
	printf("Texture Count U %i\n",n);
	n = buffer_read_int(b);
	printf("Texture Count V %i\n",n);
      }
      if (size >= 300) { // F
	f = buffer_read_float(b);
	printf("Fade In Time %f\n",f);
	f = buffer_read_float(b);
	printf("Fade Out Time %f\n",f);
	f = buffer_read_float(b);
	printf("Scale Start %f\n",f);
	f = buffer_read_float(b);
	printf("Scale End %f\n",f);
      }
      if (size >= 308) { // F
	f = buffer_read_float(b);
	printf("Scale In Time %f\n",f);
	f = buffer_read_float(b);
	printf("Scale Out Time %f\n",f);
      }
    } else if (strcmp(s,"NAM7") == 0) {
      n = buffer_read_short(b);
      printf("EFSH/NAM7 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Holes texture \"%s\"\n",s2);
      free(s2);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of EFSH\n");

  return -1;
}
