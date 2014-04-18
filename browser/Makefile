
CC=gcc -O2 -Wall
CFLAGS = `gtk-config --cflags`
LIBS= `gtk-config --libs` -lm -ljpeg -lpng -lncurses

O_DECODER= mylib/filesdirs.o mylib/mmapfile.o mylib/buffer.o decoder.o
## O_ESPBROWSER= esptools/oespparser/libespparser.o mylib/filesdirs.o mylib/mmapfile.o mylib/buffer.o mylib/parray.o espbrowser.o
O_ESPBROWSER= mylib/filesdirs.o mylib/mmapfile.o mylib/buffer.o mylib/parray.o espbrowser.o
O_DRAWER= drawer.o

all:: decoder espbrowser drawer

decoder: $(O_DECODER)
	$(CC) $(CFLAGS) -o decoder $(O_DECODER) $(LIBS)

espbrowser: $(O_ESPBROWSER)
	$(CC) $(CFLAGS) -o espbrowser $(O_ESPBROWSER) $(LIBS)

drawer: $(O_DRAWER)
	$(CC) $(CFLAGS) -o drawer $(O_DRAWER) $(LIBS)

clean:
	rm -f *.o
