
#if 0
typedef struct {
  char *editorid; // EDID
  char *sptfile; // MODL
  float scale; // MODB
  char *leavestexturefile; // ICON
  int formids; // SNAM
  int *formid; // SNAM
  // CNAM, order is yet unknown
  float shadow_radius;
  float leaf_curvature;
  float branch_dimming_value;
  float leaf_dimming_value;
  float minimum_leaf_angle;
  float maximum_leaf_angle;
  float rock_speed;
  float rustle_speed;
  // BNAM
  float billboard_size_x;
  float billboard_size_y;
} ty_record_tree;

ty_record_tree *record_tree_new()
{
  ty_record_tree *p;

  p = (ty_record_tree *)malloc(sizeof(ty_record_tree));
  p->editorid = NULL;
  p->sptfile = NULL;
  p->scale = 1.0;
  p->leavestexturefile = NULL;
  p->formids = 0;
  p->formid = NULL;
  // CNAM
  p->shadow_radius = 0.0;
  p->leaf_curvature = 0.0;
  p->branch_dimming_value = 0.0;
  p->leaf_dimming_value = 0.0;
  p->minimum_leaf_angle = 0.0;
  p->maximum_leaf_angle = 0.0;
  p->rock_speed = 0.0;
  p->rustle_speed = 0.0;
  // BNAM
  p->billboard_size_x = 0.0;
  p->billboard_size_y = 0.0;
  return p;
}

void record_tree_free(ty_record_tree *p)
{
  free(p->formid);
  free(p->leavestexturefile);
  free(p->sptfile);
  free(p->editorid);
  free(p);
}

#endif

#if 1
// Parse and print only.

int parsebuffer_tree(void *b)
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
      printf("TREE/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"MODL") == 0) {
      n = buffer_read_short(b);
      printf("TREE/MODL %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("SPT File \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"MODB") == 0) {
      n = buffer_read_short(b);
      printf("TREE/MODB %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
    } else if (strcmp(s,"MODT") == 0) {
      n = buffer_read_short(b);
      printf("TREE/MODT %i\n",n);
      parse_modt(b,n);
    } else if (strcmp(s,"ICON") == 0) {
      n = buffer_read_short(b);
      printf("TREE/ICON %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("Leaf Texture \"%s\"\n",s2);
      free(s2);
    } else if (strcmp(s,"SNAM") == 0) {
      m = buffer_read_short(b);
      printf("TREE/SNAM %i\n",m);
      for (i = 0; i < m/4; i++) {
	n = buffer_read_int(b);
	printf("SpeedTree Seed %i\n",n);
      }
    } else if (strcmp(s,"CNAM") == 0) {
      n = buffer_read_short(b);
      printf("TREE/CNAM %i\n",n);
      f = buffer_read_float(b);
      printf("Leaf Curvature %f\n",f);
      f = buffer_read_float(b);
      printf("Minimum Leaf Angle %f\n",f);
      f = buffer_read_float(b);
      printf("Maximum Leaf Angle %f\n",f);
      f = buffer_read_float(b);
      printf("Branch Dimming Value %f\n",f);
      f = buffer_read_float(b);
      printf("Leaf Dimming Value %f\n",f);
      n = buffer_read_int(b);
      printf("Shadow Radius %i\n",n);
      f = buffer_read_float(b);
      printf("Rock Speed %f\n",f);
      f = buffer_read_float(b);
      printf("Rustle Speed %f\n",f);
    } else if (strcmp(s,"BNAM") == 0) {
      n = buffer_read_short(b);
      printf("TREE/BNAM %i\n",n);
      f = buffer_read_float(b);
      printf("Billboard Width %f\n",f);
      f = buffer_read_float(b);
      printf("Billboard Height %f\n",f);
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of TREE\n");

  return -1;
}

#endif
