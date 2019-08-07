LIB=libpacman

LIBDIR=lib
SRCDIR=src
INCDIR=inc

SRCS=$(SRCDIR)/libpacman.cpp $(SRCDIR)/jhastar.cpp $(SRCDIR)/jhansi.cpp
_LIBS=$(SRCS:.cpp=.o)
LIBS=$(subst $(SRCDIR),$(LIBDIR),$(_LIBS))

RM=rm -rf

CC=g++
CFLAGS=-I. -I./inc/ -g -c -Wall
OPT=-O2 -lpthread

all: $(LIBDIR) $(LIBDIR)/$(LIB).so 

$(LIBDIR):
	mkdir $(LIBDIR)

$(LIBDIR)/$(LIB).so: $(LIBS)
	$(CC) -g -shared -ldl -o $(LIBDIR)/$(LIB).so -lpthread $(LIBS)

$(LIBDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/%.h
	$(CC) $(CFLAGS) $(OPT) $< -fPIC -DPIC -o $@

clean:
	$(RM) $(LIBDIR)

.PHONY:
