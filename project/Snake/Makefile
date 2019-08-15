BASE      	= ../..
CC		= g++
LIBDIR		= $(BASE)/lib 
INCDIR		= $(BASE)/inc
CFLAGS		= -Wl,-rpath,$(LIBDIR)
OPT		= -lpthread
RM		= rm -rf
SRC		= Snake.cpp
OBJ		= Snake.o
EXE		= Snake

$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) -L$(LIBDIR) -I$(INCDIR) $(OPT) $(CFLAGS) $(OBJ) -o $(EXE) -lsnake

$(OBJ) : $(SRC)
	$(CC) -c $(SRC) -I$(INCDIR) -o $(OBJ)

clean :
	$(RM) $(OBJ)
	$(RM) $(EXE)
