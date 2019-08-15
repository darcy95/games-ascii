BASE      	= ../..
CC		= g++
LIBDIR		= $(BASE)/lib 
INCDIR		= $(BASE)/inc
CFLAGS		= -Wl,-rpath,$(LIBDIR)
OPT		= -lpthread
RM		= rm -rf
SRC		= TicTacToe.cpp
OBJ		= TicTacTow.o
EXE		= TicTacToe

$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) -L$(LIBDIR) -I$(INCDIR) $(OPT) $(CFLAGS) $(OBJ) -o $(EXE) -ltictactoe

$(OBJ) : $(SRC)
	$(CC) -c $(SRC) -I$(INCDIR) -o $(OBJ)

clean :
	$(RM) $(OBJ)
	$(RM) $(EXE)
