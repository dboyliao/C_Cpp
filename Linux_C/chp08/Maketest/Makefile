#define clean as a phony target
.PHONY:clean
object=$(wildcard *.o)
#object=$(patsubst%.c,%.o,$(wildcard*.c))
#myapp: main.o subcount.o addcount.o
myapp:$(object)
#	gcc -o myapp main.o subcount.o addcount.o
	gcc -o myapp $(object)
main.o: main.c subcount.h addcount.h
	gcc -c main.c
subcount.o: subcount.c subcount.h
	gcc -c subcount.c
addcoutn.o: addcount.c addcount.h
	gcc -c addcount.c
clean:
	rm main.o subcount.o addcount.o myapp
