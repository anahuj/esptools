
// DEST DSTD DSTF
// DMDL??

main()
{
  if () {
    if () {

    // Cut Begin

    } else if (strcmp(s,"DEST") == 0) { // F
      n = buffer_read_short(b);
      printf("/DEST %i\n",n);
      parse_dest(b);
    } else if (strcmp(s,"DSTD") == 0) { // F
      n = buffer_read_short(b);
      printf("/DSTD %i\n",n);
      parse_dstd(b);
    } else if (strcmp(s,"DSTF") == 0) { // F
      n = buffer_read_short(b);
      printf("/DSTF %i\n",n);
      // Empty.
    } else if (strcmp(s,"DMDL") == 0) { // F
      n = buffer_read_short(b);
      printf("/DMDL %i\n",n);
      parse_dmdl(b,n);
    } else if (strcmp(s,"DMDT") == 0) { // F
      n = buffer_read_short(b);
      printf("/DMDT %i\n",n);
      parse_dmdt(b,n);

    // Cut End.
    }
  }
}
