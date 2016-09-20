LIBDIR      =  ../../
Compiler	= g++
LibDir		= -L$(LIBDIR)lib 
IncDir		= -I$(LIBDIR)include -I$(LIBDIR)src
Linker		= -lpthread
Del			= rm -rf
SrcFile		= Tetris.cpp
ObjFile		= Tetris.o
ExeFile		= Tetris

$(ExeFile) : $(ObjFile)
	$(Del) $(ExeFile)
	$(Compiler) $(ObjFile) -o $(ExeFile) $(Linker)
	$(Del) $(ObjFile)

$(ObjFile) : $(SrcFile)
	$(Compiler) -c -g $(SrcFile) $(IncDir) $(LibDir) -o $(ObjFile)

clean :
	$(Del) $(ObjFile)
