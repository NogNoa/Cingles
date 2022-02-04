CC = gcc
CFLAGS = -Wall -g
DEPS = tabbin.h
ODIR = obj
_OBJ = 
TRYLIB = rope
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))
OBJPILE = $(CC) $(CFLAGS) -c -o $@     $<
COMPILE = $(CC) $(CFLAGS)    -o $@.elf $^

try: $(ODIR)/try.o $(ODIR)/$(TRYLIB).lb.o
	$(COMPILE) 
$(ODIR)/try.o: try.c
	$(OBJPILE)
$(ODIR)/$(TRYLIB).lb.o: $(TRYLIB).lb.c
	$(OBJPILE)

.PHONY: check
.PHONY: check++

check: 
	$(CC) -Wall -pedantic -o out.o *.c

check++: %.c
	g++ -Wall -pedantic -c -o out.o $<

.PHONY: cleanex
.PHONY: cleanob
.PHONY: cleanall

cleanex:
	rm *.exe *.elf *.ilk *.pdb

cleanob:
	rm $(ODIR)/*.o *.obj

cleanall:
	cleanex  cleanob
