LIBDIR      =  ../../
Compiler	= g++
LibDir		= -L$(LIBDIR)lib 
IncDir		= -I$(LIBDIR)include -I$(LIBDIR)src
Linker		= -lpthread
Del			= rm -rf
SrcFile		= TicTacToe.cpp
ObjFile		= TicTacToe.o
ExeFile		= TicTacToe

$(ExeFile) : $(ObjFile)
	$(Del) $(ExeFile)
	$(Compiler) $(ObjFile) -o $(ExeFile) $(Linker)
	$(Del) $(ObjFile)

$(ObjFile) : $(SrcFile)
	$(Compiler) -c $(SrcFile) $(IncDir) $(LibDir) -o $(ObjFile)

clean :
	$(Del) $(ObjFile)
