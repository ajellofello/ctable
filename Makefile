# creates a static library archive and puts it into
# build/

OBJECTS := $(addprefix build/, table.o)
CFLAGS  := -std=c99
targets  := $(addprefix build/, libtable.a table.h)

build/libtable.a: $(OBJECTS) build/table.h
	$(AR) r $@ $^

build/table.h:
	cp ./table.h build/table.h

build/table.o: table.c table.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean debug
clean:
	$(RM) $(OBJECTS) $(targets)

debug: CFLAGS += -g -Werror
debug: $(targets)

