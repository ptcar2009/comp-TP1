IDIR=inc
CC=g++
CFLAGS=-I$(IDIR)
SDIR=src

ODIR=obj

_DEPS = logs.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = logs.o  main.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(ODIR) $(SDIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)


bin/montador: $(BDIR) $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

$(BDIR):
	mkdir bin
$(ODIR):
	mkdir obj


clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
$(ODIR)/%.o:
