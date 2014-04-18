
CC=gcc -O2 -Wall
# CFLAGS = `gtk-config --cflags`
# LIBS= `gtk-config --libs` -lm -ljpeg -lpng
CFLAGS= -I/home/juhana/gtk2/include/glib-2.0 -I/home/juhana/gtk2/include/gtk-2.0 -I/home/juhana/gtk2/lib/glib-2.0/include -I/home/juhana/gtk2/include/cairo -I/home/juhana/gtk2/include/pango-1.0 -I/home/juhana/gtk2/lib/gtk-2.0/include -I/home/juhana/gtk2/include/atk-1.0
# LIBS= -L/home/juhana/gtk2/lib -lgtk -lgdk -rdynamic -lgmodule -lglib -ldl -lXi -lXext -lX11 -lm -ljpeg -lpng
LIBS= -L/home/juhana/gtk2/lib -l:libgtk-x11-2.0.so -l:libgdk-x11-2.0.so -rdynamic -l:libgmodule-2.0.so -l:libglib-2.0.so -ldl -lXi -lXext -lX11 -lm -ljpeg -lpng

O_ESPBROWSER=mylib/filesdirs.o mylib/buffer.o mylib/image.o mylib/gsl_taus.o mylib/clock.o mylib/mmapfile.o mylib/sprint.o mylib/arrays.o espbrowser.o

all:: espbrowser

espbrowser: $(O_ESPBROWSER)
	$(CC) $(CFLAGS) -o espbrowser $(O_ESPBROWSER) $(LIBS)

clean:
	rm -f *.o
