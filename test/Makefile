.PHONY: all clean

CC = cc
OUT = out
SRCS := $(wildcard *.c)
BINS := $(SRCS:%.c=%)
TESTS := $(SRCS:%.c=%.o)

all: clean ${BINS} ${TESTS}

clean:
	rm -rf $(OUT)

%:
	mkdir -p $(OUT)
	cc -o $(OUT)/$@.o $@.c -I ..

%.o:
	./$(OUT)/$@
