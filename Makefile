# creates a static library archive and puts it into
# build/
#
# MUST BE RAN IN THE ROOT OF THE PROJECT

OBJECTS := $(addprefix build/, ctable.o)
CFLAGS  := -std=c99
targets := $(addprefix build/, libctable.a ctable.h)

build/libctable.a: $(OBJECTS) build/ctable.h
	$(AR) r $@ $^

build/ctable.h: ctable.h
	cp $< $@

build/ctable.o: ctable.c ctable.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean debug
clean:
	$(RM) $(OBJECTS) $(targets)

debug: CFLAGS += -g -Werror
debug: $(targets)

