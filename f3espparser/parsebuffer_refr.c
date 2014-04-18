
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

  printf("refsearch 0x%.8x (dec%i) in %s, %s, %i, %i\n",global_formid,global_formid,global_worldspace,global_cell,global_cell_x,global_cell_y);

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
      // Fallout3.esm uses size 1 only. Oblivion.esm uses sizes 1 and 4.
      // To what size GECK editor saves?
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
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
    } else if (strcmp(s,"XPCI") == 0) { // Not in Fallout3.esm
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
    } else if (strcmp(s,"XGLB") == 0) { // Not in Fallout3.esm
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
      printf("  xespformid %i at %i / %s\n",n,global_formid,s_edid);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Set Enable State to Opposite of Parent\n");
      printf("       ^Pop In\n");
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
      printf("XMarker Target FormID %i\n",n);
    } else if (strcmp(s,"XHLT") == 0) { // Not in Fallout3.esm. XHLP instead?
      n = buffer_read_short(b);
      printf("REFR/XHLT %i\n",n);
      strcat(s_list,"XHLT ");
      n = buffer_read_int(b);
      printf("%i\n",n);
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
      n = buffer_read_int(b);
      printf("Level Modifier %i %% 0 Easy 1 Medium 2 Hard 3 Boss (no-XLCM is None)\n",n);
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
      n = buffer_read_int(b);
      printf("%i xactvalue\n",n);
    } else if (strcmp(s,"XTEL") == 0) { // F
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
      n = buffer_read_byte(b); // F
      printflags8(n);
      //      0000,0000
      printf("        ^No alarm\n");
      n = buffer_read_byte(b); // F
      printf("%i\n",n);
      n = buffer_read_byte(b); // F
      printf("%i\n",n);
      n = buffer_read_byte(b); // F
      printf("%i\n",n);
    } else if (strcmp(s,"XLOC") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XLOC %i\n",n);
      strcat(s_list,"XLOC ");
      size = n;
      if (size == 12) {
	n = buffer_read_ubyte(b);
	printf("Level %i\n",n);
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
	printf("Level %i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_int(b);
	printf("Key FormID %i\n",n);
	n = buffer_read_int(b);
	printf("%i\n",n);
	n = buffer_read_int(b);
	printf("%i\n",n);
      }
      if (size == 20) { // F
	n = buffer_read_byte(b);
	printf("Level %i %% -1 Requires Key 0 Very Easy 25 Easy 50 Average 75 Hard 80-100 Very Hard\n",n);
	n = buffer_read_ubyte(b);
	printf("%i (keyunknown1)\n",n);
	n = buffer_read_ubyte(b);
	printf("%i (keyunknown2)\n",n);
	n = buffer_read_ubyte(b);
	printf("%i (keyunknown3)\n",n);
	n = buffer_read_int(b);
	printf("Key FormID %i\n",n);
#if 0
	n = buffer_read_byte(b);
	printf("Leveled %i %% 0 Disabled 4 Enabled\n",n);
#else
	n = buffer_read_ubyte(b);
	printflags8(n);
	//      0000,0000
	printf("      ^Leveled\n");
#endif
	n = buffer_read_byte(b);
	printf("%i (unused)\n",n);
	n = buffer_read_byte(b);
	printf("%i (unused)\n",n);
	n = buffer_read_byte(b);
	printf("%i (keyunknown4)\n",n);
	n = buffer_read_int(b);
	printf("%i (keyunknown5)\n",n);
	n = buffer_read_int(b);
	printf("%i (keyunknown6)\n",n);
      }
    } else if (strcmp(s,"FNAM") == 0) {
      n = buffer_read_short(b);
      printf("REFR/FNAM %i\n",n);
      strcat(s_list,"FNAM ");
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Visible\n");
      printf("       ^Can Travel To\n");
      printf("      ^\"Show All\" hidden\n");
    } else if (strcmp(s,"FULL") == 0) {
      n = buffer_read_short(b);
      printf("REFR/FULL %i\n",n);
      strcat(s_list,"FULL ");
      s2 = buffer_read_nstring(b,n);
      printf("Marker Data Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"ONAM") == 0) {
      n = buffer_read_short(b);
      printf("REFR/ONAM %i\n",n);
      // Empty.
      printf("Open By Default\n");
      strcat(s_list,"ONAM ");
    } else if (strcmp(s,"TNAM") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/TNAM %i\n",n);
      size = n;
      strcat(s_list,"TNAM ");
      if (size == 2) {
	// Marker Data tab.
	n = buffer_read_ubyte(b);
	printf("Marker Data Type %i %% 1 City 2 Settlement 3 Encampment 4 Natural Landmark 5 Cave 6 Factory 7 Monument 8 Military 9 Office 10 Town Ruins 11 Urban Ruins 12 Sewer Ruins 13 Metro 14 Vault\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
      }
      if (size == 4) {
	// Used in what tab?
	n = buffer_read_int(b);
	printf("Topic FormID %i\n",n);
      }
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
    } else if (strcmp(s,"XLKR") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XLKR %i\n",n);
      n = buffer_read_int(b);
      printf("Linked Ref FormID %i\n",n);
    } else if (strcmp(s,"XNDP") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XNDP %i\n",n);
      n = buffer_read_int(b);
      printf("NavMesh FormID %i\n",n);
      n = buffer_read_ushort(b);
      printf("Linked Door triangle index %i\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_byte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"XLTW") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XLTW %i\n",n);
      n = buffer_read_int(b);
      printf("Lit Water Reflected by Ref FormID %i\n",n);
    } else if (strcmp(s,"XRDS") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XRDS %i\n",n);
      f = buffer_read_float(b);
      printf("Radius %f\n",f);
    } else if (strcmp(s,"XEMI") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XEMI %i\n",n);
      n = buffer_read_int(b);
      printf("Emittance Light FormID %i %% LIGH for interior, REGN for exterior\n",n);
    } else if (strcmp(s,"XPWR") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XPWR %i\n",n);
      n = buffer_read_int(b);
      printf("Placeable Water Ref FormID %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Reflected\n");
      printf("       ^Refracted\n");
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
      n = buffer_read_ubyte(b);
      printf("%i (unused)\n",n);
    } else if (strcmp(s,"XPRD") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XPRD %i\n",n);
      f = buffer_read_float(b);
      printf("Idle Time %f\n",f);
    } else if (strcmp(s,"XPPA") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XPPA %i\n",n);
      // Empty.
    } else if (strcmp(s,"INAM") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/INAM %i\n",n);
      n = buffer_read_int(b);
      printf("Idle Animation FormID %i %% Not displayed in Editor??\n",n);
    } else if (strcmp(s,"SCHR") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/SCHR %i\n",n);
      parse_schr(b);
    } else if (strcmp(s,"XMBO") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XMBO %i\n",n);
      f = buffer_read_float(b);
      printf("Bounds X %f %% Editor displays 2xValue = %f %% Cannot be modified in Primitive Tab; what about render window?\n",f,2.0*f);
      f = buffer_read_float(b);
      printf("Bounds Y %f %% Editor displays 2xValue = %f %% Cannot be modified in Primitive Tab; what about render window?\n",f,2.0*f);
      f = buffer_read_float(b);
      printf("Bounds Z %f %% Editor displays 2xValue = %f %% Cannot be modified in Primitive Tab; what about render window?\n",f,2.0*f);
    } else if (strcmp(s,"XPRM") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XPRM %i\n",n);
      f = buffer_read_float(b);
      printf("Bounds X %f %% Not displayed in Editor\n",f);
      f = buffer_read_float(b);
      printf("Bounds Y %f %% Not displayed in Editor\n",f);
      f = buffer_read_float(b);
      printf("Bounds Z %f %% Not displayed in Editor\n",f);
      f = buffer_read_float(b);
      printf("Color R %f\n",f);
      f = buffer_read_float(b);
      printf("Color G %f\n",f);
      f = buffer_read_float(b);
      printf("Color B %f\n",f);
      f = buffer_read_float(b);
      printf("%f unknown\n",f);
      n = buffer_read_int(b);
      printf("Primitive Type %i %% 1 Box 2 Sphere 3 Plane\n",n);
    } else if (strcmp(s,"XRMR") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XRMR %i\n",n);
      n = buffer_read_short(b);
      printf("Number of Linked Rooms %i %% Not displayed in Editor\n",n);
      n = buffer_read_short(b);
      printf("Type %i %% 0 Slave 1 Master\n",n);
    } else if (strcmp(s,"XLRM") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XLRM %i\n",n);
      n = buffer_read_int(b);
      printf("Linked Room Reference FormID %i %% Not displayed in Editor\n",n);
    } else if (strcmp(s,"XRGD") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XRGD %i\n",n);
      m = n/28;
      for (i = 0; i < m; i++) {
	n = buffer_read_byte(b);
	printf("%i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
	n = buffer_read_byte(b);
	printf("%i\n",n);
	f = buffer_read_float(b);
	printf("%f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"XHLP") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XHLP %i\n",n);
      f = buffer_read_float(b);
      printf("Health%% %f %% Editor displays 100x\n",f);
    } else if (strcmp(s,"XPOD") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XPOD %i\n",n);
      n = buffer_read_int(b);
      printf("Portal Ref 1 FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Portal Ref 2 FormID %i\n",n);
    } else if (strcmp(s,"XRDO") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XRDO %i\n",n);
      f = buffer_read_float(b);
      printf("Range Radius %f\n",f);
      n = buffer_read_int(b);
      printf("Broadcast Range Type %i %% 0 Radius 1 Everywhere 2 World Space and Linked Interiors 3 Linked Interiors 4 Current Cell Only\n",n);
      f = buffer_read_float(b);
      printf("Static Percentage %f\n",f);
      n = buffer_read_int(b);
      printf("Exterior Position Ref FormID %i\n",n);
    } else if (strcmp(s,"XAPD") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XAPD %i\n",n);
      n = buffer_read_ubyte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Parent Activate Only\n");
    } else if (strcmp(s,"XAPR") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XAPR %i\n",n);
      n = buffer_read_int(b);
      printf("Activate Parent Ref FormID %i\n",n);
      f = buffer_read_float(b);
      printf("Activate Parent Delay %f\n",f);
    } else if (strcmp(s,"XTRI") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XTRI %i\n",n);
      n = buffer_read_int(b);
      printf("Collision Layer %i %% 0 Unidentified 1 Static 2 Animstatic 3 Transparent 4 Clutter 5 Weapon 6 Projectile 7 Spell 8 Biped 9 Trees 10 Props 11 Water 12 Trigger 13 Terrain 14 Trap 15 Noncollidable 16 Cloudtrap 17 Ground 18 Portal 19 Debris Small 20 Debris Large 21 Acoustic space 22 Actorzone 23 Projectilezone 24 Gastrap 25 Shellcasing 26 Transparent Small 27 Invisible Wall 28 Transparent Small Anim 29 Deadbip 30 Charcontroller 31 Avoidbox 32 Collisionbox 33 Camerasphere 34 Doordetection 35 Camerapick 36 Itempick 37 Lineofsight 38 Pathpick 39 Custompick1 40 Custompick2 41 Spellexplosion 42 Droppingpick\n",n);
    } else if (strcmp(s,"XOCP") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XOCP %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"XAMT") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XAMT %i\n",n);
      n = buffer_read_int(b);
      printf("Ammo FormID %i %% Inherits from Base Object?\n",n);
    } else if (strcmp(s,"XAMC") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XAMC %i\n",n);
      n = buffer_read_int(b);
      printf("Ammo Count %i\n",n);
    } else if (strcmp(s,"XRAD") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XRAD %i\n",n);
      f = buffer_read_float(b);
      printf("Radiation %f\n",f);
    } else if (strcmp(s,"XIBS") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XIBS %i\n",n);
      // Empty.
      printf("Ignored By Sandbox\n");
    } else if (strcmp(s,"XORD") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XORD %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"XMBP") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XMBP %i\n",n);
      // Empty.
    } else if (strcmp(s,"XMBR") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XMBR %i\n",n);
      n = buffer_read_int(b);
      printf("MultiBound Reference FormID %i\n",n);
    } else if (strcmp(s,"XCLP") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XCLP %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Link Start Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Link Start Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Link Start Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("Link End Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Link End Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Link End Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"SCDA") == 0) {
      n = buffer_read_short(b);
      printf("REFR/SCDA %i\n",n);
      parse_scda(b,n);
    } else if (strcmp(s,"SCRO") == 0) {
      n = buffer_read_short(b);
      printf("REFR/SCRO %i\n",n);
      parse_scro(b);
    } else if (strcmp(s,"RCLR") == 0) {
      n = buffer_read_short(b);
      printf("REFR/RCLR %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Link Start Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Link Start Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Link Start Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
      n = buffer_read_ubyte(b);
      printf("Link End Color R %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Link End Color G %i\n",n);
      n = buffer_read_ubyte(b);
      printf("Link End Color B %i\n",n);
      n = buffer_read_ubyte(b);
      printf("%i\n",n);
    } else if (strcmp(s,"XRGB") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XRGB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"XCHG") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XCHG %i\n",n);
      f = buffer_read_float(b);
      printf("Charge %f\n",f);
    } else if (strcmp(s,"XEZN") == 0) { // F
      n = buffer_read_short(b);
      printf("REFR/XEZN %i\n",n);
      n = buffer_read_int(b);
      printf("Encounter Zone FormID %i\n",n);
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
