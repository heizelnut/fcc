CC	:= cc
CFLAGS	:= -std=c99 -pedantic -Wall

PREFIX	:= ~/.local
MANPAGE	:= $(PREFIX)/share/man
DIR	:= $(PREFIX)/bin

TARGETS	:= fcc
OBJ	:= fcc.o
MAN	:= fcc.1

.PHONY: all clean

all: $(TARGETS)

clean:
	rm -rf $(TARGETS) $(OBJ)
.c.o:
	$(CC) -c $(CFLAGS) $<

$(TARGETS): $(OBJ)
	$(CC) -o $@ $(OBJ)

install: all
	install $(TARGETS) $(DIR)/$(TARGETS)
	install $(MAN) $(MANPAGE)/man1/$(MAN)

uninstall: clean
	rm -f $(DIR)/$(TARGETS)
	rm -f $(MANPAGE)/man1/$(MAN)
