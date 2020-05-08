CFLAGS=-Wall -Wextra -std=gnu99 -O0 -ggdb -fsanitize=signed-integer-overflow -fsanitize=undefined
CFILES   = $(wildcard *.c)
OBJFILES = $(CFILES:.c=.o)
OUT      = minish
$(OUT): $(OBJFILES)
.PHONY: clean
clean:
	rm -f $(OBJFILES) $(OUT)