LIBDIR=lib
SRCDIR=src
INCDIR=inc

RM=rm -rf

CC=g++
CFLAGS=-I. -I./inc/ -g -c -Wall
OPT=-O2 -lpthread

PACMAN=libpacman
PACMANLIBS=$(LIBDIR)/pacman.o $(LIBDIR)/jhastar.o $(LIBDIR)/jhansi.o

TETRIS=libtetris
TETRISLIBS=$(LIBDIR)/tetris.o $(LIBDIR)/jhansi.o

SNAKE=libsnake
SNAKELIBS=$(LIBDIR)/snake.o $(LIBDIR)/jhansi.o

TICTACTOE=libtictactoe
TICTACTOELIBS=$(LIBDIR)/tictactoe.o $(LIBDIR)/jhansi.o

POKER=libpoker
POKERLIBS=$(LIBDIR)/poker.o $(LIBDIR)/jhansi.o


all: $(LIBDIR) $(LIBDIR)/$(PACMAN).so $(LIBDIR)/$(TETRIS).so $(LIBDIR)/$(SNAKE).so $(LIBDIR)/$(TICTACTOE).so $(LIBDIR)/$(POKER).so

$(LIBDIR):
	mkdir $(LIBDIR)

$(LIBDIR)/$(PACMAN).so: $(PACMANLIBS)
	$(CC) -g -shared -ldl -o $(LIBDIR)/$(PACMAN).so -lpthread $(PACMANLIBS)

$(LIBDIR)/$(TETRIS).so: $(TETRISLIBS)
	$(CC) -g -shared -ldl -o $(LIBDIR)/$(TETRIS).so -lpthread $(TETRISLIBS)

$(LIBDIR)/$(SNAKE).so: $(SNAKELIBS)
	$(CC) -g -shared -ldl -o $(LIBDIR)/$(SNAKE).so -lpthread $(SNAKELIBS)

$(LIBDIR)/$(TICTACTOE).so: $(TICTACTOELIBS)
	$(CC) -g -shared -ldl -o $(LIBDIR)/$(TICTACTOE).so -lpthread $(TICTACTOELIBS)

$(LIBDIR)/$(POKER).so: $(POKERLIBS)
	$(CC) -g -shared -ldl -o $(LIBDIR)/$(POKER).so -lpthread $(POKERLIBS)

$(LIBDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/%.h
	$(CC) $(CFLAGS) $(OPT) $< -fPIC -DPIC -o $@

clean:
	$(RM) $(LIBDIR)

.PHONY:
