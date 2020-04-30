CFILES   = $(wildcard *.c)
OBJFILES = $(CFILES:.c=.o)
OUT      = minish
$(OUT): $(OBJFILES)
.PHONY: clean
clean:
	rm -f $(OBJFILES) $(OUT)