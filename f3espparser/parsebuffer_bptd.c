
int parsebuffer_bptd(void *b)
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
      printf("BPTD/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"BPTN") == 0) {
      n = buffer_read_short(b);
      printf("BPTD/BPTN %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Part Name \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"BPNN") == 0) {
      n = buffer_read_short(b);
      printf("BPTD/BPNN %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Part Node \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"BPNT") == 0) {
      n = buffer_read_short(b);
      printf("BPTD/BPNT %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("VATS Target \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"BPNI") == 0) {
      n = buffer_read_short(b);
      printf("BPTD/BPNI %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("IK Data Start Node \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"NAM1") == 0) {
      n = buffer_read_short(b);
      printf("BPTD/NAM1 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Explodable Limb Replacement \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"NAM4") == 0) {
      n = buffer_read_short(b);
      printf("BPTD/NAM4 %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Gore Effects Positioning Target Bone \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"NAM5") == 0) {
      n = buffer_read_short(b);
      printf("BPTD/NAM5 %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"BPND") == 0) {
      n = buffer_read_short(b);
      printf("BPTD/BPND %i\n",n);
      f = buffer_read_float(b);
      printf("Damage Mult %f\n",f);
      n = buffer_read_byte(b);
      printflags8(n);
      //      0000,0000
      printf("        ^Severable\n");
      printf("       ^IK Data\n");
      printf("      ^Biped Data (Not marked when IK Data = 0)\n");
      printf("     ^Explodable\n");
      printf("   ^Is Head\n");
      printf("  ^Headtracking\n");
      printf(" ^Explodable Explosion Chance %% Absolute\n");
      n = buffer_read_byte(b);
      printf("Part Type %i %% 0 DismemberedLimb0 Torso 1 DismemberedLimb1 Head1 2 DismemberedLimb2 Head2 3 DismemberedLimb3 LeftArm1 4 DismemberedLimb4 LeftArm2 5 DismemberedLimb5 RightArm1 6 DismemberedLimb6 RightArm2 7 DismemberedLimb7 LeftLeg1 8 DismemberedLimb8 LeftLeg2 9 DismemberedLimb9 LeftLeg3 10 DismemberedLimb10 RightLeg1 11 DismemberedLimb11 RightLeg2 12 DismemberedLimb12 RightLeg3 13 DismemberedLimb13 Brain 14 DismemberedLimb14 Weapon\n",n);
      n = buffer_read_ubyte(b);
      printf("Health Percent %i\n",n);
      n = buffer_read_byte(b);
      printf("Actor Value %i\n",n);
      n = buffer_read_byte(b);
      printf("To Hit Chance %i\n",n);
      n = buffer_read_byte(b);
      printf("Explosion Chance %% %i\n",n);
      n = buffer_read_byte(b);
      printf("Explodable Debris Count %i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("Explodable Generic Debris FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Explodable Explosion Type FormID %i\n",n);
      f = buffer_read_float(b);
      printf("IK Data Tracking Max Angle %f\n",f);
      f = buffer_read_float(b);
      printf("Explodable Debris Scale %f\n",f);
      n = buffer_read_int(b);
      printf("Severable Debris Count %i\n",n);
      n = buffer_read_int(b);
      printf("Severable Generic Debris FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Severable Explosion Type FormID %i\n",n);
      f = buffer_read_float(b);
      printf("Severable Debris Scale %f\n",f);
      f = buffer_read_float(b);
      printf("Gore Effects Positioning Local Translate X %f\n",f);
      f = buffer_read_float(b);
      printf("Gore Effects Positioning Local Translate Y %f\n",f);
      f = buffer_read_float(b);
      printf("Gore Effects Positioning Local Translate Z %f\n",f);
      f = buffer_read_float(b);
      printf("Gore Effects Positioning Local Rotate X %f %% UI displays %f/(2*Pi)*360 = %i\n",f,f,(int)(f/(2.0*M_PI)*360.0));
      f = buffer_read_float(b);
      printf("Gore Effects Positioning Local Rotate Y %f %% UI displays %f/(2*Pi)*360 = %i\n",f,f,(int)(f/(2.0*M_PI)*360.0));
      f = buffer_read_float(b);
      printf("Gore Effects Positioning Local Rotate Z %f %% UI displays %f/(2*Pi)*360 = %i\n",f,f,(int)(f/(2.0*M_PI)*360.0));
      n = buffer_read_int(b);
      printf("Severable Blood Spurt Decal Impact Data FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Explodable Blood Spurt Decal Impact Data FormID %i\n",n);
      n = buffer_read_byte(b);
      printf("Severable Decal Count %i\n",n);
      n = buffer_read_byte(b);
      printf("Explodable Decal Count %i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
      n = buffer_read_byte(b);
      printf("%i\n",n);
      f = buffer_read_float(b);
      printf("Explodable Limb Replacement Scale %f\n",f);
    } else if (strcmp(s,"RAGA") == 0) {
      n = buffer_read_short(b);
      printf("BPTD/RAGA %i\n",n);
      n = buffer_read_int(b);
      printf("Ragdoll Data FormID %i\n",n);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("BPTD/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Skeleton Model \"%s\"\n",s2);
      free(s2);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of BPTD\n");

  return -1;
}
