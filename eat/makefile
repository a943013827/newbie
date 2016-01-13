src=$(wildcard *.c)
obj=$(patsubst %.c,%,$(src))

all:$(obj)

$(obj):%:%.c
	gcc -g -o $@ $< -lpthread

.PHONY: all
