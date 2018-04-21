
install: main
	cp main /usr/local/bin/vms

# ---------------------------------------------------------------------------- #

TARGET := interface

CFLAGS := -g #-std=c99 -Wall -Wextra -pedantic-errors -O2 -g
CFLAGS += $(shell pkg-config --cflags --libs glib-2.0 gtk+-3.0)
CFLAGS += -L/usr/local/lib -I/usr/local/include -lreadline

SRCS   := $(shell find . -name '*.c' ! -name 'y.tab.c' ! -name 'lex.yy.c')

.PHONY: $(TARGET)
$(TARGET): y.tab.c lex.yy.c
	$(CC) $(SRCS) $^ $(CFLAGS) -o $@

.PHONY: y.tab.c
y.tab.c: syntax.y
	yacc -d $<

.PHONY: lex.yy.c
lex.yy.c: lex.l
	flex $<

.PHONY: clean
clean:
	rm -f $(TARGET) y.tab.c lex.yy.c

	# ---------------------------------------------------------------------------- #
