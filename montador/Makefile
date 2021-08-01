IDIR=inc
CC=g++
CFLAGS=-I$(IDIR)
SDIR=src
EXEC_NAME=montador
BDIR=bin

ODIR=obj

_DEPS = logs.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = logs.o main.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

build: $(BDIR) $(ODIR) $(BDIR)/$(EXEC_NAME)

$(BDIR)/$(EXEC_NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

$(BDIR):
	mkdir bin
$(ODIR):
	mkdir obj


clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
$(ODIR)/%.o:
