
int parsebuffer_pgrd(void *b)
{
  int n;
  int i,j,k,kk;
  int m;
  int loc;
  char *s,*s2;
  float f;
  unsigned int flags;
  int has_pgrp;
  int numpoints;
  int *numconnections;

  has_pgrp = 0;
  numpoints = -1;
  numconnections = NULL;

  while (buffer_eof(b) != 1) {
    loc = buffer_getloc(b);
    s = buffer_read_string4(b);
    printf("Chunk name: %s\n",s);
    if (strcmp(s,"DATA") == 0) {
      n = buffer_read_int(b);
      printf("PGRD/DATA %i\n",n);
      n = buffer_read_int(b);
      printf("Exterior Cell X Coord %i\n",n);
      n = buffer_read_int(b);
      printf("Exterior Cell Y Coord %i\n",n);
      n = buffer_read_ushort(b);
      printf("Granularity %i\n",n);
      n = buffer_read_ushort(b);
      printf("Number of path grid points %i\n",n);
    } else if (strcmp(s,"NAME") == 0) {
      n = buffer_read_int(b);
      printf("PGRD/NAME %i\n",n);
      s2 = buffer_read_nstring(b,n);
      printf("%s\n",s2);
      free(s2);
    } else if (strcmp(s,"PGRP") == 0) {
      n = buffer_read_int(b);
      printf("PGRD/PGRP %i\n",n);
      m = n/16;
      numpoints = m;
      numconnections = (int *)malloc(numpoints*sizeof(int));
      for (i = 0; i < m; i++) {
	printf("Point %i:\n",i);
	n = buffer_read_int(b);
	printf("Position X %i\n",n);
	n = buffer_read_int(b);
	printf("Position Y %i\n",n);
	n = buffer_read_int(b);
	printf("Position Z %i\n",n);
	n = buffer_read_ubyte(b);
	printf("Color %i %% 0 Red 1 Blue\n",n);
	n = buffer_read_ubyte(b);
	printf("Number of connections %i\n",n);
	numconnections[i] = n;
	n = buffer_read_ubyte(b);
	printf("%i (unused)\n",n);
	n = buffer_read_ubyte(b);
	printf("%i (unused)\n",n);
      }
      has_pgrp = 1;
    } else if (strcmp(s,"PGRC") == 0) {
      n = buffer_read_int(b);
      printf("PGRD/PGRC %i\n",n);
      if (has_pgrp == 1) {
	for (i = 0; i < numpoints; i++) {
	  printf("Point %i:\n",i);
	  for (j = 0; j < numconnections[i]; j++) {
	    n = buffer_read_int(b);
	    printf("Connection to point %i\n",n);
	  }
	}
      } else {
	printf("error: no PGRP\n");
	m = n/4;
	for (i = 0; i < m; i++) {
	  n = buffer_read_int(b);
	  printf("%i\n",n);
	}
      }
    } else {
      printf("Unknown chunk name\n");
      exit(-1);
    }
    free(s);
  }

  printf("End of PGRD\n");

  return -1;
}
