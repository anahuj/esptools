
int parsebuffer_road(void *b)
{
  int n;
  int i,j,k;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int num;
  int numpathgridpoints;
  int numpathgridendpoints;
  int *numpathgridlines;
  int *pathgridendpoints;
  float *pathgridendpointscoords;
  float *pathgridpointcoords;

  numpathgridpoints = -1;
  numpathgridendpoints = -1;
  numpathgridlines = NULL;
  pathgridendpoints = NULL;
  pathgridpointcoords = NULL;
  pathgridendpointscoords = NULL;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"PGRP") == 0) {
      n = buffer_read_ushort(b);
      printf("ROAD/PGRP %i\n",n);
      m = n/16;
      numpathgridpoints = m; // XXXX Note this here.
      numpathgridlines = (int *)malloc(m*sizeof(int));
      pathgridpointcoords = (float *)malloc(3*m*sizeof(float));
      for (i = 0; i < m; i++) {
	printf("Point %i:\n",i);
	f = buffer_read_float(b);
	printf("X %f\n",f);
	pathgridpointcoords[3*i+0] = f;
	f = buffer_read_float(b);
	printf("Y %f\n",f);
	pathgridpointcoords[3*i+1] = f;
	f = buffer_read_float(b);
	printf("Z %f\n",f);
	pathgridpointcoords[3*i+2] = f;
	n = buffer_read_byte(b);
	printf("Path Lines %i\n",n);
	numpathgridlines[i] = n;
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
	n = buffer_read_ubyte(b);
	printf("%i\n",n);
      }
    } else if (strcmp(s,"PGRR") == 0) {
      n = buffer_read_ushort(b);
      printf("ROAD/PGRR %i\n",n);
      m = n/12;
      numpathgridendpoints = m;
      pathgridendpointscoords = (float *)malloc(3*m*sizeof(float));
      for (i = 0; i < m; i++) {
	printf("Endpoint %i:\n",i);
	f = buffer_read_float(b);
	printf("X %f\n",f);
	pathgridendpointscoords[3*i+0] = f;
	f = buffer_read_float(b);
	printf("Y %f\n",f);
	pathgridendpointscoords[3*i+1] = f;
	f = buffer_read_float(b);
	printf("Z %f\n",f);
	pathgridendpointscoords[3*i+2] = f;
      }
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  // Search endpoints from the points by coordinate matching.
  if (numpathgridendpoints > 0) {
    pathgridendpoints = (int *)malloc(numpathgridendpoints*sizeof(int));
    for (i = 0; i < numpathgridendpoints; i++) {
      pathgridendpoints[i] = -1;
      for (j = 0; j < numpathgridpoints; j++) {
	if ((fabs(pathgridendpointscoords[3*i+0]-pathgridpointcoords[3*j+0]) < 0.5) &&
	    (fabs(pathgridendpointscoords[3*i+1]-pathgridpointcoords[3*j+1]) < 0.5) &&
	    (fabs(pathgridendpointscoords[3*i+2]-pathgridpointcoords[3*j+2]) < 0.5)) {
	  if (pathgridendpoints[i] != -1) {
	    printf("double match for endpoint %i\n",i);
	  } else {
	    pathgridendpoints[i] = j;
	  }
	}
      }
    }
  }

  // Print the pathgrid lines.
  if ((pathgridendpoints != NULL) &&
      (numpathgridlines != NULL) &&
      (numpathgridpoints > 0)) {
    printf("Path Grid Lines:\n");
    k = 0;
    for (i = 0; i < numpathgridpoints; i++) {
      printf("point %i -->",i);
      if (numpathgridlines[i] > 0) {
	for (j = 0; j < numpathgridlines[i] - 1; j++) {
	  printf(" %i",pathgridendpoints[k]);
	  k++;
	}
	printf(" %i\n",pathgridendpoints[k]);
	k++;
      } else {
	printf("nowhere\n");
      }
    }
    if (k == numpathgridendpoints) {
      printf("Total number of path lines %i equal %i\n",k,numpathgridendpoints);
    } else {
      printf("Total number of path lines %i mismatch %i\n",k,numpathgridendpoints);
    }

    free(pathgridendpointscoords);
    free(pathgridpointcoords);
    free(numpathgridlines);
  }

  if (numpathgridendpoints > 0) {
    free(pathgridendpoints);
  }

  printf("End of ROAD\n");

  return -1;
}
