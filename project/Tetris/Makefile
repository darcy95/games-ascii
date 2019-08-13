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

$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) -L$(LIBDIR) -I$(INCDIR) $(OPT) $(CFLAGS) $(OBJ) -o $(EXE) -ltetris

$(OBJ) : $(SRC)
	$(CC) -c $(SRC) -I$(INCDIR) -o $(OBJ)

clean:
	$(RM) *.o
	$(RM) $(EXE)
