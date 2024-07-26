CC = gcc
ODIR = obj
SDIR = src

_OBJS = ccloc.o langs.o

OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

cli: lib
	gcc main.c -o ccloc.exe -L. -lccloc

lib: $(OBJS) 
	ar rcs ccloc.lib $^

$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	$(CC) -c $< -o $@

$(ODIR):
	mkdir $@

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o