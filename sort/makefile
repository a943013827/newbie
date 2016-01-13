src=$(wildcard *.c)
obj=$(patsubst %.c,%,$(src))

all:$(obj)

$(obj):%:%.c
	gcc -g -o $@ $<

.PHONY: all
