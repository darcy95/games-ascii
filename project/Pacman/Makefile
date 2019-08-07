HOME      	=  ../..
CC		= g++
LIBDIR		= -L$(HOME)/lib 
INCDIR		= -I$(HOME)/inc
CFLAGS		= -Wl,-rpath=$(HOME)/lib/pacman
OPT		= -lpthread
RM		= rm -rf
SRC		= Pacman.cpp
OBJ		= Pacman.o
EXE		= Pacman

$(EXE) : $(OBJ)
	$(CC) $(LIBDIR) $(INCDIR) $(OPT) $(CFLAGS) $(OBJ) -o $(EXE) -lpacman

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) $(INCDIR) $(LIBDIR) -o $(OBJ)

clean :
	$(RM) $(OBJ)
	$(RM) $(EXE)
