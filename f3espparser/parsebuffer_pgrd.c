
int parsebuffer_pgrd(void *b)
{
  int n;
  int i,j,k,kk;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int num;
  int numpathgridpoints;
  int numpathgridendpoints;
  int *pathgridlines;
  int *pathgridendpoints;
  int *pointtypes;
  float *pointz;
  int iz,miz;
  int *pgriconnections;
  int *pgrinodes;
  int numpgrinodes;

  numpathgridpoints = -1;
  numpathgridendpoints = -1;
  pathgridlines = NULL;
  pathgridendpoints = NULL;
  pointtypes = NULL;
  pointz = NULL;
  pgriconnections = NULL;
  pgrinodes = NULL;
  numpgrinodes = -1;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"DATA") == 0) {
      n = buffer_read_short(b);
      printf("PGRD/DATA %i\n",n);
      n = buffer_read_short(b);
      printf("Path Grid Points %i\n",n);
      numpathgridpoints = n;
    } else if (strcmp(s,"PGRP") == 0) {
      n = buffer_read_short(b);
      printf("PGRD/PGRP %i\n",n);
      m = n/16;
      pathgridlines = (int *)malloc(m*sizeof(int));
      pointz = (float *)malloc(m*sizeof(float));
      for (i = 0; i < m; i++) {
	printf("Point %i:\n",i);
	f = buffer_read_float(b);
	printf("X %f\n",f);
	f = buffer_read_float(b);
	printf("Y %f\n",f);
	f = buffer_read_float(b);
	printf("Z %f\n",f);
	pointz[i] = f;
	n = buffer_read_byte(b);
	printf("Path Lines %i\n",n);
	pathgridlines[i] = n;
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
      }
    } else if (strcmp(s,"PGAG") == 0) {
      n = buffer_read_short(b);
      printf("PGRD/PGAG %i\n",n);
      k = 0;
      m = n;
      kk = 0;
      pointtypes = (int *)malloc(8*m*sizeof(int));
      for (i = 0; i < m; i++) {
	n = buffer_read_byte(b);
	printf("%i\n",n);
	if (n != 0) k = 1;
	pointtypes[kk+0] = n & 0x01;
	pointtypes[kk+1] = n & 0x02;
	pointtypes[kk+2] = n & 0x04;
	pointtypes[kk+3] = n & 0x08;
	pointtypes[kk+4] = n & 0x10;
	pointtypes[kk+5] = n & 0x20;
	pointtypes[kk+6] = n & 0x40;
	pointtypes[kk+7] = n & 0x80;
	kk += 8;
      }
      if (k == 1) {
	printf("xxxx pgag is not zero\n");
      }
    } else if (strcmp(s,"PGRR") == 0) {
      n = buffer_read_short(b);
      printf("PGRD/PGRR %i\n",n);
      m = n/2;
      numpathgridendpoints = m;
      pathgridendpoints = (int *)malloc(m*sizeof(int));
      for (i = 0; i < m; i++) {
	n = buffer_read_short(b);
	printf("%i\n",n);
	pathgridendpoints[i] = n;
      }
    } else if (strcmp(s,"PGRI") == 0) {
      n = buffer_read_short(b);
      printf("PGRD/PGRI %i\n",n);
      m = n/16;
      numpgrinodes = m;
      pgrinodes = (int *)malloc(m*sizeof(int));
      for (i = 0; i < m; i++) {
	n = buffer_read_short(b);
	printf("Node %i\n",n);
	pgrinodes[i] = n;
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	f = buffer_read_float(b);
	printf("%f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
	f = buffer_read_float(b);
	printf("%f\n",f);
      }
    } else if (strcmp(s,"PGRL") == 0) {
      n = buffer_read_short(b);
      printf("PGRD/PGRL %i\n",n);
      num = n/4 - 1;
      n = buffer_read_int(b);
      printf("Linked Object FormID %i\n",n);
      for (i = 0; i < num; i++) {
	n = buffer_read_int(b);
	printf("Point %i\n",n);
      }
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  // Print the pathgrid lines.
  if ((pathgridendpoints != NULL) &&
      (pathgridlines != NULL) &&
      (numpathgridpoints > 0)) {

    if (pgrinodes != NULL) {
      pgriconnections = (int *)malloc(numpathgridpoints*sizeof(int));
      for (i = 0; i < numpathgridpoints; i++) {
	pgriconnections[i] = 0;
      }
      for (i = 0; i < numpgrinodes; i++) {
	if ((pgrinodes[i] < 0) || (pgrinodes[i] >= numpathgridpoints)) {
	  printf("pgrinodes[%i] = %i out of point range\n",i,pgrinodes[i]);
	} else {
	  pgriconnections[pgrinodes[i]]++;
	}
      }
    }

    printf("Path Grid Lines:\n");
    k = 0;
    for (i = 0; i < numpathgridpoints; i++) {
      iz = (int)pointz[i];
      miz = iz % 2;
      if (pointtypes == NULL) {
	printf("point %i (\?\?\?) -->",i);
      } else {
	if (pointtypes[i] == 0) {
	  if (miz == 0) {
	    printf("point %i (red) -->",i);
	  } else {
	    printf("point %i (red/blue) -->",i);
	  }
	} else {
	  if (miz == 0) {
	    printf("point %i (orange) -->",i);
	  } else {
	    printf("point %i (orange/blue) -->",i);
	  }
	}
      }
      if (pathgridlines[i] > 0) {
	// for (j = 0; j < pathgridlines[i] - 1; j++) {
	for (j = 0; j < pathgridlines[i]; j++) {
	  printf(" %i",pathgridendpoints[k]);
	  k++;
	}
#if 0
	printf(" %i\n",pathgridendpoints[k]);
	k++;
#endif
      } else {
	printf(" nowhere");
      }
      if (pgrinodes != NULL) {
	if (pgriconnections[i] > 0) {
	  printf(" + %i PGRI connections\n",pgriconnections[i]);
	} else {
	  printf("\n");
	}
      } else {
	printf("\n");
      }
    }
    if (k == numpathgridendpoints) {
      printf("Total number of path lines %i equal %i\n",k,numpathgridendpoints);
    } else {
      printf("Total number of path lines %i mismatch %i\n",k,numpathgridendpoints);
    }

    if (pgrinodes != NULL) {
      free(pgriconnections);
      free(pgrinodes);
    }

    if (pointtypes != NULL) {
      free(pointtypes);
    }

    free(pathgridendpoints);
    free(pointz);
    free(pathgridlines);
  }

  printf("End of PGRD\n");

  return -1;
}
