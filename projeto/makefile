
# ---------------------------------------------------------------------------- #

TARGET := interface

CFLAGS := -g
#CFLAGS := -std=c99 -Wall -Wextra -pedantic-errors -O2 -g
CFLAGS += $(shell pkg-config --cflags --libs glib-2.0 gtk+-3.0)
GLIB_FLAGS= `pkg-config --cflags glib-2.0`

SRCS   := $(shell find . -name '*.c')

.PHONY: $(TARGET)
$(TARGET):
	$(CC) $(SRCS) $(GLIB_FLAGS) $(CFLAGS) -o $@

.PHONY: clean
clean:
	rm -f $(TARGET)

# ---------------------------------------------------------------------------- #
