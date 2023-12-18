.PHONY: all clean

CC = cc
OUT = out
SRCS := $(wildcard *.c)
BINS := $(SRCS:%.c=%)

all: clean ${BINS}

clean:
	rm -rf $(OUT)

%:
	@echo "Compiling %.c"
	mkdir $(OUT)
	cc -o $(OUT)/$@ $@.c -I ..
	./$(OUT)/$@

