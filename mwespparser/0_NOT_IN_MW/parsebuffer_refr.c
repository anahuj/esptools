
// We count how many subrecords and print it.
// We list all subrecord in a one line print.

char s_edid[256];
char s_list[256];

int parsebuffer_refr(void *b)
{
  int n;
  int i;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int num;
  int numsubrecords;
  int size;
  int baseobject;

  numsubrecords = 0;
  s_edid[0] = '\0';
  s_list[0] = '\0';
  baseobject = -1;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    numsubrecords++;
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("REFR/EDID %i\n",n);
      strcat(s_list,"EDID ");
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      strcpy(s_edid,s2);
      free(s2);
    } else if (strcmp(s,"NAME") == 0) {
      n = buffer_read_short(b);
      printf("REFR/NAME %i\n",n);
      strcat(s_list,"NAME ");
      n = buffer_read_int(b);
      printf("Base Object FormID %i\n",n);
      baseobject = n;
    } else if (strcmp(s,"XMRK") == 0) {
      n = buffer_read_short(b);
      printf("REFR/XMRK %i\n",n);
      strcat(s_list,"XMRK ");
    } else if (strcmp(s,"XSED") == 0) {
      n = buffer_read_short(b);
      printf("REFR/XSED %i\n",n);
      strcat(s_list,"XSED ");
      num = n;
      for (i = 0; i < num; i++) {
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
      }
    } else if (strcmp(s,"XLOD") == 0) {
      n = buffer_read_short(b);
      printf("REFR/XLOD %i\n",n);
      strcat(s_list,"XLOD ");
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      printf("xlod used with base object %i\n",baseobject);
    } else if (strcmp(s,"XPCI") == 0) {
      n = buffer_read_short(b);
      printf("REFR/XPCI %i\n",n);
      strcat(s_list,"XPCI ");
      n = buffer_read_int(b);
      printf("unknown Cell(?) FormID %i\n",n);
    } else if (strcmp(s,"XSCL") == 0) {
      n = buffer_read_short(b);
      printf("REFR/XSCL %i\n",n);
      strcat(s_list,"XSCL ");
      f = buffer_read_float(b);
      printf("Scale %f\n",f);
    } else if (strcmp(s,"XOWN") == 0) {
      n = buffer_read_short(b);
      printf("REFR/XOWN %i\n",n);
      strcat(s_list,"XOWN ");
      n = buffer_read_int(b);
      printf("Ownership NPC/Faction FormID %i\n",n);
    } else if (strcmp(s,"XRNK") == 0) {
      n = buffer_read_short(b);
      printf("REFR/XRNK %i\n",n);
      strcat(s_list,"XRNK ");
      n = buffer_read_int(b);
      printf("Required Rank %i %% 0 DUMMY\n",n);
    } else if (strcmp(s,"XGLB") == 0) {
      n = buffer_read_short(b);
      printf("REFR/XGLB %i\n",n);
      strcat(s_list,"XGLB ");
      n = buffer_read_int(b);
      printf("Ownership Global Variable FormID %i\n",n);
    } else if (strcmp(s,"XESP") == 0) {
      n = buffer_read_short(b);
      printf("REFR/XESP %i\n",n);
      strcat(s_list,"XESP ");
      n = buffer_read_int(b);
      printf("Enable Parent Ref FormID %i\n",n);
      printf("xespformid %i at %i / %s\n",n,global_formid,s_edid);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Set Enable State to Opposite of Parent\n");
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"XTRG") == 0) {
      n = buffer_read_short(b);
      printf("REFR/XTRG %i\n",n);
      strcat(s_list,"XTRG ");
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"XHLT") == 0) {
      n = buffer_read_short(b);
      printf("REFR/XHLT %i\n",n);
      strcat(s_list,"XHLT ");
      n = buffer_read_int(b);
      printf("Health %i\n",n);
    } else if (strcmp(s,"XCNT") == 0) {
      n = buffer_read_short(b);
      printf("REFR/XCNT %i\n",n);
      strcat(s_list,"XCNT ");
      n = buffer_read_int(b);
      printf("Count %i\n",n);
    } else if (strcmp(s,"XLCM") == 0) {
      n = buffer_read_short(b);
      printf("REFR/XLCM %i\n",n);
      strcat(s_list,"XLCM ");
      // 4 bytes?
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"XRTM") == 0) {
      n = buffer_read_short(b);
      printf("REFR/XRTM %i\n",n);
      strcat(s_list,"XRTM ");
      n = buffer_read_int(b);
      printf("Master FormID %i\n",n);
    } else if (strcmp(s,"XACT") == 0) {
      n = buffer_read_short(b);
      printf("REFR/XACT %i\n",n);
      strcat(s_list,"XACT ");
      // 4 bytes?
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"XTEL") == 0) {
      n = buffer_read_short(b);
      printf("REFR/XTEL %i\n",n);
      strcat(s_list,"XTEL ");
      n = buffer_read_int(b);
      printf("Teleport Target FormID %i\n",n);
      f = buffer_read_float(b);
      printf("Position X %f\n",f);
      f = buffer_read_float(b);
      printf("Position Y %f\n",f);
      f = buffer_read_float(b);
      printf("Position Z %f\n",f);
      f = buffer_read_float(b);
      printf("Angle X %f\n",f);
      f = buffer_read_float(b);
      printf("Angle Y %f\n",f);
      f = buffer_read_float(b);
      printf("Angle Z %f\n",f);
    } else if (strcmp(s,"XLOC") == 0) {
      n = buffer_read_short(b);
      printf("REFR/XLOC %i\n",n);
      strcat(s_list,"XLOC ");
      size = n;
      if (size == 12) {
	n = buffer_read_ubyte(b);
	printf("Lock Level %i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_int(b);
	printf("Key FormID %i\n",n);
	n = buffer_read_int(b);
	printflags(n);
      }
      if (size == 16) {
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_int(b);
	printf("%i\n",n);
	n = buffer_read_int(b);
	printf("%i\n",n);
	n = buffer_read_int(b);
	printflags(n);
      }
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_short(b);
      printf("REFR/FNAM %i\n",n);
      strcat(s_list,"FNAM ");
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("REFR/FULL %i\n",n);
      strcat(s_list,"FULL ");
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"ONAM") == 0) {
      n = buffer_read_short(b);
      printf("REFR/ONAM %i\n",n);
      // Empty.
      printf("Open By Default\n");
      strcat(s_list,"ONAM ");
    } else if (strcmp(s,"TNAM") == 0) {
      n = buffer_read_short(b);
      printf("REFR/TNAM %i\n",n);
      strcat(s_list,"TNAM ");
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("REFR/DATA %i\n",n);
      strcat(s_list,"DATA ");
      f = buffer_read_float(b);
      printf("Position X %f\n",f);
      f = buffer_read_float(b);
      printf("Position Y %f\n",f);
      f = buffer_read_float(b);
      printf("Position Z %f\n",f);
      f = buffer_read_float(b);
      printf("Rotation X %f\n",f);
      f = buffer_read_float(b);
      printf("Rotation Y %f\n",f);
      f = buffer_read_float(b);
      printf("Rotation Z %f\n",f);
    } else if (strcmp(s,"XSOL") == 0) {
      n = buffer_read_short(b);
      printf("REFR/XSOL %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Soul %i %% 0 None 1 Petty 2 Lesser 3 Common 4 Greater 5 Grand\n",n);
    } else if (strcmp(s,"XCHG") == 0) {
      n = buffer_read_short(b);
      printf("REFR/XCHG %i\n",n);
      f = buffer_read_float(b);
      printf("Charge %f\n",f);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of REFR\n");
  printf("SUBRECORDSREFR %i subrecords / FormID = %i\n",numsubrecords,global_formid);
  printf("LISTREFR %s\n",s_list);

  return -1;
}
