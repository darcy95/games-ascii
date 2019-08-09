BASE   = ../..
CC     = g++
LIBDIR = $(BASE)/lib 
INCDIR = $(BASE)/inc
OPT    = -lpthread
RM     = rm -rf
OBJ    = Tetris.o tetris_ext.o
EXE    = Tetris

$(EXE) : $(OBJ)
	$(CC) -Wl,-rpath,$(LIBDIR) -I. -I$(INCDIR) $(OPT) $(OBJ) -o $(EXE) -ltetris

Tetris.o: Tetris.cpp tetris_ext.o
	$(CC) -c Tetris.cpp -I$(INCDIR) -L$(LIBDIR) -o $@

tetris_ext.o: tetris_ext.cpp
	$(CC) -c tetris_ext.cpp -I$(INCDIR) -L$(LIBDIR) -o $@

clean :
	$(RM) $(OBJ)
	$(RM) $(EXE)
	$(RM) tetris_ext.o
