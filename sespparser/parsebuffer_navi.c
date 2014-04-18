
int parsebuffer_navi(void *b)
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
  int numpos;
  int numidx;
  int caseflag;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"NVER") == 0) {
      n = buffer_read_short(b);
      printf("NAVI/NVER %i\n",n);
      n = buffer_read_int(b);
      printf("Version or cell grid size %i\n",n);
    } else if (strcmp(s,"NVMI") == 0) {
      n = buffer_read_short(b);
      printf("NAVI/NVMI %i\n",n);
      size = n;
      n = buffer_read_int(b);
      printf("NavMesh FormID %i\n",n);
      n = buffer_read_int(b);
      printf("Flags %i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      n = buffer_read_int(b);
      printf("%i\n",n);
      // data similar to FO3 NAVI/NVCI follows
      n = buffer_read_int(b);
      printf("Num1 %i\n",n);
      num = n;
      for (i = 0; i < num; i++) {
	n = buffer_read_int(b);
	printf("NavMesh FormID %i\n",n);
      }
      n = buffer_read_int(b);
      printf("Num2 %i\n",n);
      num = n;
      for (i = 0; i < num; i++) {
	n = buffer_read_int(b);
	printf("NavMesh FormID %i\n",n);
      }
      n = buffer_read_int(b);
      printf("Num3 %i\n",n);
      num = n;
      for (i = 0; i < num; i++) {
	n = buffer_read_int(b);
	printf("unknown %i\n",n);
	n = buffer_read_int(b);
	printf("FormID %i\n",n);
      }
      m = buffer_getloc(b);
      printf("loc = %i\n",m);
      n = buffer_read_byte(b);
      printf("Caseflag %i\n",n);
      caseflag = n;
      if (caseflag == 1) {
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
	
	n = buffer_read_int(b);
	printf("Num %i\n",n);
	num = n;
	for (i = 0; i < num; i++) {
	  n = buffer_read_short(b);
	  printf("%i\n",n);
	  n = buffer_read_short(b);
	  printf("%i\n",n);
	  n = buffer_read_short(b);
	  printf("%i\n",n);
	}
	n = buffer_read_int(b);
	printf("Num %i\n",n);
	num = n;
	for (i = 0; i < num; i++) {
	  f = buffer_read_float(b);
	  printf("%f\n",f);
	  f = buffer_read_float(b);
	  printf("%f\n",f);
	  f = buffer_read_float(b);
	  printf("%f\n",f);
	}
      }
      n = buffer_read_short(b);
      printf("%i\n",n);
      n = buffer_read_short(b);
      printf("%i\n",n);
      n = buffer_read_short(b);
      printf("%i\n",n);
      n = buffer_read_short(b);
      printf("%i\n",n);
      n = buffer_read_short(b);
      printf("%i\n",n);
      n = buffer_read_short(b);
      printf("%i\n",n);

      m = buffer_getloc(b);
      printf("loc = %i\n",m);
      buffer_setloc(b,loc+6+size);
      m = buffer_getloc(b);
      printf("loc = %i\n",m);
#if 0
      n = buffer_read_short(b);
      printf("Cell Coordinate X %i\n",n);
      n = buffer_read_short(b);
      printf("Cell Coordinate Y %i\n",n);
      f = buffer_read_float(b); // f % world position
      printf("Center X %f\n",f);
      f = buffer_read_float(b); // f
      printf("Center Y %f\n",f);
      f = buffer_read_float(b); // f
      printf("Center Z %f\n",f);
      if (size > 32) {
	f = buffer_read_float(b);
	printf("Min X %f\n",f);
	f = buffer_read_float(b);
	printf("Min Y %f\n",f);
	f = buffer_read_float(b);
	printf("Min Z %f\n",f);
	f = buffer_read_float(b);
	printf("Max X %f\n",f);
	f = buffer_read_float(b);
	printf("Max Y %f\n",f);
	f = buffer_read_float(b);
	printf("Max Z %f\n",f);
	n = buffer_read_short(b); // s % counts
	printf("Number of vertices %i\n",n);
	numpos = n;
	n = buffer_read_short(b); // s
	printf("Number of triangles %i\n",n);
	numidx = n;
	for (i = 0; i < numpos; i++) {
	  printf("Vertex %i:\n",i);
	  f = buffer_read_float(b);
	  printf("%f\n",f);
	  f = buffer_read_float(b);
	  printf("%f\n",f);
	  f = buffer_read_float(b);
	  printf("%f\n",f);
	}
	for (i = 0; i < numidx; i++) {
	  printf("Triangle %i:\n",i);
	  n = buffer_read_short(b);
	  printf("%i\n",n);
	  n = buffer_read_short(b);
	  printf("%i\n",n);
	  n = buffer_read_short(b);
	  printf("%i\n",n);
	}
      }
      m = buffer_getloc(b);
      f = buffer_read_float(b);
      buffer_setloc(b,m);
      n = buffer_read_int(b);
      printf("%f / %i\n",f,n);
#endif
    } else if (strcmp(s,"NVCI") == 0) {
      n = buffer_read_short(b);
      printf("NAVI/NVCI %i\n",n);
      size = n;
      n = buffer_read_int(b);
      printf("NavMesh FormID %i (0x%.8x)\n",n,n);
      n = buffer_read_int(b);
      printf("Number of ???? NavMeshes %i\n",n);
      num = n;
      for (i = 0; i < num; i++) {
	n = buffer_read_int(b);
	printf("NavMesh with common border edge (green/blue/purple) %i (0x%.8x)\n",n,n);
      }
      n = buffer_read_int(b);
      printf("Number of ???? NavMeshes %i\n",n);
      num = n;
      for (i = 0; i < num; i++) {
	n = buffer_read_int(b);
	printf("NavMesh with common border edge (preferred triangles?) %i (0x%.8x)\n",n,n);
      }
      n = buffer_read_int(b);
      printf("Number of Teleports (Doors) %i\n",n);
      num = n;
      for (i = 0; i < num; i++) {
	n = buffer_read_int(b);
	printf("Teleport (Door) Reference FormID %i (0x%.8x)\n",n,n);
      }
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of NAVI\n");

  return -1;
}
