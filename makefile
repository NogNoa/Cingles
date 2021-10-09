CC = gcc
CFLAGS = -Wall -g
DEPS = tabbin.h
ODIR = obj
_OBJ = 
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))
OBJPILE = $(CC) $(CFLAGS) -c -o $@     $<
COMPILE = $(CC) $(CFLAGS)    -o $@.elf $^

try: $(ODIR)/try.o $(ODIR)/stdio.lb.o 
	$(COMPILE) 
$(ODIR)/try.o: stdio.lb.h
	$(OBJPILE)
$(ODIR)/stdio.lb.o:
	$(OBJPILE)

transpose: $(ODIR)/transpose.o $(ODIR)/KnR_getline.lb.o
	$(COMPILE)
$(ODIR)/transpose.o : ../KnR_getline.h
	$(OBJPILE)
$(ODIR)/KnR_getline.lb.o : ../KnR_getline.lb.c ../KnR_getline.h
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
