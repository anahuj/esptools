
# Copyright 2006-2008 Juhana Sadeharju

CC=gcc -O2 -Wall
CFLAGS= 
FLAGS=
LIBS= -lm -lz
LD_LIBRARY_PATH=

OBJS_EP= mylib/buffer.o mylib/mmapfile.o mylib/filesdirs.o espparser.o
DEP_EP= parsebuffer_*.c
OBJS_EC= espcompiler.o
OBJS_MWEP= mylib/buffer.o mylib/mmapfile.o mylib/filesdirs.o mwesmparser.o
OBJS_LEP= mylib/buffer.o mylib/mmapfile.o mylib/filesdirs.o libespparser.o
OBJS_LF3EP= mylib/buffer.o mylib/mmapfile.o mylib/filesdirs.o libf3espparser.o

all:: espparser libf3espparser

espparser: $(OBJS_EP)
	$(CC) $(FLAGS) -o espparser $(OBJS_EP) $(LIBS)

espparser.o: $(DEP_EP)

espcompiler: $(OBJS_EC)
	$(CC) $(FLAGS) -o espcompiler $(OBJS_EC) $(LIBS)

mwesmparser: $(OBJS_MWEP)
	$(CC) $(FLAGS) -o mwesmparser $(OBJS_MWEP) $(LIBS)

libespparser: $(OBJS_LEP)
	$(CC) $(FLAGS) -o libespparser $(OBJS_LEP) $(LIBS)

libf3espparser: $(OBJS_LF3EP)
	$(CC) $(FLAGS) -o libf3espparser $(OBJS_LF3EP) $(LIBS)

clean:
	rm -f *.o

mrproper:
	rm -f *.o espparser espcompiler mwesmparser libespparser
