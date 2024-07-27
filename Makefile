CC = gcc
ODIR = obj
SDIR = src

_OBJS = ccloc.o langs.o

OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

ifeq ($(OS), Windows_NT)
	LIB := ccloc.lib
	CLI := ccloc.exe
else
	LIB := libccloc.a
	CLI := ccloc
endif

cli: lib
	gcc main.c -o $(CLI) -L. -lccloc

lib: $(OBJS) 
	ar rcs $(LIB) $^

$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	$(CC) -c $< -o $@

$(ODIR):
	mkdir $@

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o