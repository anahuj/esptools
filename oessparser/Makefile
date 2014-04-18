
# Copyright 2009 Juhana Sadeharju

CC=gcc -O2 -Wall
CFLAGS= 
FLAGS=
LIBS= -lm -lz
LD_LIBRARY_PATH=

OBJS_ESSP= mylib/buffer.o mylib/mmapfile.o mylib/filesdirs.o essparser.o
DEP_EP= parsebuffer_*.c
OBJS_EC= espcompiler.o
OBJS_MWEP= mylib/buffer.o mylib/mmapfile.o mylib/filesdirs.o mwesmparser.o
OBJS_LEP= mylib/buffer.o mylib/mmapfile.o mylib/filesdirs.o libespparser.o

# all:: espparser
# all:: mwesmparser
all:: essparser

essparser: $(OBJS_ESSP)
	$(CC) $(FLAGS) -o essparser $(OBJS_ESSP) $(LIBS)

espparser.o: $(DEP_EP)

espcompiler: $(OBJS_EC)
	$(CC) $(FLAGS) -o espcompiler $(OBJS_EC) $(LIBS)

mwesmparser: $(OBJS_MWEP)
	$(CC) $(FLAGS) -o mwesmparser $(OBJS_MWEP) $(LIBS)

libespparser: $(OBJS_LEP)
	$(CC) $(FLAGS) -o libespparser $(OBJS_LEP) $(LIBS)

clean:
	rm -f *.o

mrproper:
	rm -f *.o espparser espcompiler mwesmparser libespparser
