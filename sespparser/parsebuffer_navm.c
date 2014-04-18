
int parsebuffer_navm(void *b)
{
  int n;
  int i,j;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int size;
  int num;
  float x,y,z;
  int k0,k1,k2;
  int ka0,ka1,ka2;
  int d1,d2;
  int cellid;
  float xmean;
  float ymean;
  float zmean;
  float xmin,xmax;
  float ymin,ymax;
  float zmin,zmax;
  int numcells;

  cellid = -1;
  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"EDID") == 0) {
      n = buffer_read_short(b);
      printf("NAVM/EDID %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"NVER") == 0) {
      n = buffer_read_short(b);
      printf("NAVM/NVER %i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
    } else if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("NAVM/DATA %i\n",n);
      n = buffer_read_int(b);
      printf("Cell FormID %i\n",n);
      cellid = n;
      n = buffer_read_int(b);
      printf("Number of vertices %i\n",n);
      n = buffer_read_short(b); // Could be 3 1/2 bytes.
      printf("Number of triangles %i\n",n);
      n = buffer_read_short(b); // Warning status in highest 4 bits.
      printf("%i error status in highest 4 bits (short)\n",n);
      n = buffer_read_int(b);
      printf("Number of border edges (NVEX size) %i\n",n);
      n = buffer_read_int(b);
      printf("Number of cover edge triangles (NVCA size) %i\n",n);
      n = buffer_read_int(b);
      printf("Number of linked door triangles (NVDP size) %i\n",n);
    } else if (strcmp(s,"NVVX") == 0) {
      n = buffer_read_short(b);
      printf("NAVM/NVVX %i\n",n);
      size = n;
      num = size/4/3; // 3D vertex data
      xmean = 0.0;
      ymean = 0.0;
      zmean = 0.0;
      xmin = 10000000000000.0;
      xmax = -10000000000000.0;
      ymin = 10000000000000.0;
      ymax = -10000000000000.0;
      zmin = 10000000000000.0;
      zmax = -10000000000000.0;
      printf("Vertex data:\n");
      for (i = 0; i < num; i++) {
	printf("Vertex %i:\n",i);
	f = buffer_read_float(b);
	printf("%f\n",f);
	x = f;
	xmean += x;
	if (xmin > x) xmin = x;
	if (xmax < x) xmax = x;
	f = buffer_read_float(b);
	printf("%f\n",f);
	y = f;
	ymean += y;
	if (ymin > y) ymin = y;
	if (ymax < y) ymax = y;
	f = buffer_read_float(b);
	printf("%f\n",f);
	z = f;
	zmean += z;
	if (zmin > z) zmin = z;
	if (zmax < z) zmax = z;
	printf("navmeshvertex %i %f %f %f\n",i,x,y,z);
      }
      xmean = xmean/num;
      ymean = ymean/num;
      zmean = zmean/num;
      printf("vertex mean %f %f %f\n",xmean,ymean,zmean);
      printf("vertex min %f %f %f\n",xmin,ymin,zmin);
      printf("vertex max %f %f %f\n",xmax,ymax,zmax);
    } else if (strcmp(s,"NVTR") == 0) {
      n = buffer_read_ushort(b);
      printf("NAVM/NVTR %i\n",n);
      size = n;
      num = size/16; // Triangle vertex index data, 16 bytes per triangle
      printf("Triangle data:\n");
      for (i = 0; i < num; i++) {
	printf("Triangle %i:\n",i);
	n = buffer_read_short(b);
	printf("Vertex 0: %i\n",n);
	k0 = n;
	n = buffer_read_short(b);
	printf("Vertex 1: %i\n",n);
	k1 = n;
	n = buffer_read_short(b);
	printf("Vertex 2: %i\n",n);
	k2 = n;
	n = buffer_read_short(b);
	printf("Edge 0: adjacent triangle / border edge index %i\n",n);
	ka0 = n;
	n = buffer_read_short(b);
	printf("Edge 1: adjacent triangle / border edge index %i\n",n);
	ka1 = n;
	n = buffer_read_short(b);
	printf("Edge 2: adjacent triangle / border edge index %i\n",n);
	ka2 = n;
	n = buffer_read_ushort(b);
	printflags16(n);
	//      0000,0000,0000,0000
	printf("                  ^Edge 0: border edge\n");
	printf("                 ^Edge 1: border edge\n");
	printf("                ^Edge 2: border edge\n");
	printf("             ^No large creature\n");
	printf("           ^Preferred\n");
	printf("       ^Water\n");
	printf("      ^Linked door\n");
	printf("     ^Unknown\n");
	d1 = n;
	n = buffer_read_ushort(b);
	printflags16(n);
	//      0000,0000,0000,0000
	printf("               ^^^^Edge 01 cover data %i: 1 Wall 2 Ledge 4 64u 5 80u ... 8 128u ... 14 224u 15 Max\n",n&0xf);
	// printf("                  ^Wall (no cover)\n");
	// printf("                 ^Ledge\n");
	printf("             ^Edge 01 Left side cover\n");
	printf("            ^Edge 01 Right side cover\n");
	printf("       ^^-^^Edge 12 cover data %i: 1 Wall 2 Ledge 4 64u 5 80u ... 8 128u ... 14 224u 15 Max\n",(n >> 6)&0xf);
	printf("      ^Edge 12 Left side cover\n");
	printf("     ^Edge 12 Right side cover\n");
	// printf("  (%i)\n",n);
	d2 = n;
	printf("navmeshtriangle %i %i %i %i adjacy %i %i %i data %i %i\n",i,k0,k1,k2,ka0,ka1,ka2,d1,d2);
      }
    } else if (strcmp(s,"NVCA") == 0) {
      n = buffer_read_short(b);
      printf("NAVM/NVCA %i\n",n);
      size = n;
      num = size/2; // shorts
      printf("Triangles which have cover edges:\n");
      for (i = 0; i < num; i++) {
	n = buffer_read_short(b);
	printf("%i\n",n);
      }
    } else if (strcmp(s,"NVDP") == 0) {
      n = buffer_read_short(b);
      printf("NAVM/NVDP %i\n",n);
      size = n;
      num = size/4/2;
      for (i = 0; i < num; i++) {
	n = buffer_read_int(b);
	printf("Teleport Reference FormID %i\n",n);
	n = buffer_read_int(b);
	printf("Linked Door triangle %i\n",n);
      }
    } else if (strcmp(s,"NVGD") == 0) {
      n = buffer_read_short(b);
      printf("NAVM/NVGD %i\n",n);
      size = n;
      n = buffer_read_int(b);
      printf("Grid cells %i (total %i^2 = %i cells)\n",n,n,n*n);
      f = buffer_read_float(b);
      printf("Grid cell size X %f\n",f);
      f = buffer_read_float(b);
      printf("Grid cell size Y %f\n",f);
      f = buffer_read_float(b);
      printf("Grid min point X %f\n",f);
      f = buffer_read_float(b);
      printf("Grid min point Y %f\n",f);
      f = buffer_read_float(b);
      printf("Grid min point Z %f\n",f);
      f = buffer_read_float(b);
      printf("Grid max point X %f\n",f);
      f = buffer_read_float(b);
      printf("Grid max point Y %f\n",f);
      f = buffer_read_float(b);
      printf("Grid max point Z %f\n",f);
      num = (size - 1*4 - 8*4)/2; // shorts
      while (num > 0) {
	m = buffer_read_short(b);
	printf("Number of triangles %i\n",m);
	num--;
	printf("Triangle indexes:\n");
	for (i = 0; i < m; i++) {
	  n = buffer_read_short(b);
	  printf("%i\n",n);
	  num--;
	}
      }
#if 0
      num = (size - 1*4 - 8*4)/2; // shorts
      for (i = 0; i < num; i++) {
	n = buffer_read_short(b);
	printf("%i\n",n);
      }
#endif
    } else if (strcmp(s,"NVEX") == 0) {
      n = buffer_read_short(b);
      printf("NAVM/NVEX %i\n",n);
      size = n;
      num = size/10;
      for (i = 0; i < num; i++) {
	printf("Border edge %i:\n",i);
	n = buffer_read_int(b);
	printf("%i %% 0 Regular border edge (green) 1 Edge of Drop Down (to up/lower, purple) 2 Edge of Drop Down (to down/higher, purple) 3 Edge of Separated NavMesh (blue)\n",n);
	printf("border edge unknown has value %i in navm %i (0x%.8x) in cell %i (0x%.8x)\n",n,global_formid,global_formid,cellid,cellid);
	n = buffer_read_int(b);
	printf("NavMesh FormID %i\n",n);
	n = buffer_read_short(b);
	printf("Triangle index %i\n",n);
      }
    } else if (strcmp(s,"NVNM") == 0) {
      n = buffer_read_short(b);
      printf("NAVM/NVNM %i\n",n);
      n = buffer_read_int(b);
      printf("Version %i\n",n);
      n = buffer_read_int(b);
      printf("unknown1 %x\n",n);
      n = buffer_read_int(b);
      printf("unknown2 %i\n",n);
      n = buffer_read_int(b);
      printf("num1 %i\n",n);
      n = buffer_read_int(b);
      printf("num2 %i\n",n);
      num = n;
      for (i = 0; i < num; i++) {
	f = buffer_read_float(b);
	printf("X %f\n",f);
	f = buffer_read_float(b);
	printf("Y %f\n",f);
	f = buffer_read_float(b);
	printf("Z %f\n",f);
      }
      loc = buffer_getloc(b);
      printf("loc = %i\n",loc);
      n = buffer_read_int(b);
      printf("num3 %i\n",n);
      loc = buffer_getloc(b);
      printf("loc = %i\n",loc);
      num = n;
      printf("Triangle data:\n");
      for (i = 0; i < num; i++) {
	printf("Triangle %i:\n",i);
	n = buffer_read_short(b);
	printf("Vertex 0: %i\n",n);
	k0 = n;
	n = buffer_read_short(b);
	printf("Vertex 1: %i\n",n);
	k1 = n;
	n = buffer_read_short(b);
	printf("Vertex 2: %i\n",n);
	k2 = n;
	n = buffer_read_short(b);
	printf("Edge 0: adjacent triangle / border edge index %i\n",n);
	ka0 = n;
	n = buffer_read_short(b);
	printf("Edge 1: adjacent triangle / border edge index %i\n",n);
	ka1 = n;
	n = buffer_read_short(b);
	printf("Edge 2: adjacent triangle / border edge index %i\n",n);
	ka2 = n;
	n = buffer_read_ushort(b);
	printflags16(n);
	//      0000,0000,0000,0000
	printf("                  ^Edge 0: border edge\n");
	printf("                 ^Edge 1: border edge\n");
	printf("                ^Edge 2: border edge\n");
	printf("             ^No large creature\n");
	printf("           ^Preferred\n");
	printf("       ^Water\n");
	printf("      ^Linked door\n");
	printf("     ^Unknown\n");
	d1 = n;
	n = buffer_read_ushort(b);
	printflags16(n);
	//      0000,0000,0000,0000
	printf("               ^^^^Edge 01 cover data %i: 1 Wall 2 Ledge 4 64u 5 80u ... 8 128u ... 14 224u 15 Max\n",n&0xf);
	// printf("                  ^Wall (no cover)\n");
	// printf("                 ^Ledge\n");
	printf("             ^Edge 01 Left side cover\n");
	printf("            ^Edge 01 Right side cover\n");
	printf("       ^^-^^Edge 12 cover data %i: 1 Wall 2 Ledge 4 64u 5 80u ... 8 128u ... 14 224u 15 Max\n",(n >> 6)&0xf);
	printf("      ^Edge 12 Left side cover\n");
	printf("     ^Edge 12 Right side cover\n");
	// printf("  (%i)\n",n);
	d2 = n;
	printf("navmeshtriangle %i %i %i %i adjacy %i %i %i data %i %i\n",i,k0,k1,k2,ka0,ka1,ka2,d1,d2);
      }
      loc = buffer_getloc(b);
      printf("loc = %i\n",loc);
      n = buffer_read_int(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("%i\n",n);
      f = buffer_read_float(b);
      printf("%f\n",f);
      f = buffer_read_float(b);
      printf("%f\n",f);
      n = buffer_read_short(b);
      printf("%i\n",n);
      n = buffer_read_int(b);
      printf("num %i\n",n);
      num = n;
      for (i = 0; i < num; i++) {
	n = buffer_read_short(b);
	printf("%i\n",n);
      }
      loc = buffer_getloc(b);
      printf("loc = %i\n",loc);
      n = buffer_read_int(b);
      printf("num cell grids %i\n",n);
      numcells = n;
      f = buffer_read_float(b);
      printf("cell size x %f\n",f);
      f = buffer_read_float(b);
      printf("cell size y %f\n",f);
      f = buffer_read_float(b);
      printf("min x %f\n",f);
      f = buffer_read_float(b);
      printf("min y %f\n",f);
      f = buffer_read_float(b);
      printf("min z %f\n",f);
      f = buffer_read_float(b);
      printf("max x %f\n",f);
      f = buffer_read_float(b);
      printf("max y %f\n",f);
      f = buffer_read_float(b);
      printf("max z %f\n",f);
      for (j = 0; j < numcells*numcells; j++) {
	n = buffer_read_int(b);
	printf("num %i\n",n);
	num = n;
	for (i = 0; i < num; i++) {
	  n = buffer_read_short(b);
	  printf("%i\n",n);
	}

      }
      loc = buffer_getloc(b);
      printf("loc = %i\n",loc);


    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of NAVM\n");

  return -1;
}
