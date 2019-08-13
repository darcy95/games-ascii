BASE      	= ../..
CC		= g++
LIBDIR		= $(BASE)/lib 
INCDIR		= $(BASE)/inc
CFLAGS		= -Wl,-rpath,$(LIBDIR) -g -Wall
OPT		= -lpthread
RM		= rm -rf
SRC		= Tetris.cpp
OBJ		= Tetris.o
EXE		= Tetris

all:
	$(CC) $(CFLAGS) -L. -L$(LIBDIR) -I. -I$(INCDIR) tetris_ext.cpp -o tetris_ext.o -ltetris

clean:
	$(RM) *.o
	$(RM) $(EXE)
