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

all: $(LIBDIR) $(LIBDIR)/$(PACMAN).so  $(LIBDIR)/$(TETRIS).so

$(LIBDIR):
	mkdir $(LIBDIR)

$(LIBDIR)/$(PACMAN).so: $(PACMANLIBS)
	$(CC) -g -shared -ldl -o $(LIBDIR)/$(PACMAN).so -lpthread $(PACMANLIBS)

$(LIBDIR)/$(TETRIS).so: $(TETRISLIBS)
	$(CC) -g -shared -ldl -o $(LIBDIR)/$(TETRIS).so -lpthread $(TETRISLIBS)

$(LIBDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/%.h
	$(CC) $(CFLAGS) $(OPT) $< -fPIC -DPIC -o $@

clean:
	$(RM) $(LIBDIR)

.PHONY:
