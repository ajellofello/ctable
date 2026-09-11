OBJECTS := $(addprefix build/, table.o)
CFLAGS  := -std=c99
target  := build/libtable.a

$(target): $(OBJECTS)
	$(AR) r $@ $^

build/table.o: table.c table.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean debug
clean:
	$(RM) $(OBJECTS) $(target)

debug: CFLAGS += -g -Werror
debug: $(target)

