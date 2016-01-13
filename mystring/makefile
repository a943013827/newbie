src=$(wildcard *.cpp)
obj=$(patsubst %.cpp,%.o,$(src))
ALL:m.out

CFLAGS = -Wall -g
CC=g++
m.out:$(obj)
	$(CC) $^ -o $@ $(CFLAGS)

%.o:%.c
	$(CC) $< -o $@ -c $(CFLAGS)

clean:main.o mystring.o
	rm $^ m.out

.PHONY:clean ALL

