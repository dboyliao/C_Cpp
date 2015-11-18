#Makefile
.PHONY:clean
myapp :main.o func1.o func2.o
	gcc -o myapp main.o func1.o func2.o
main.o:main.c func1.h func2.h
	gcc -c main.c
func1.o:func1.c func1.h
	gcc -c func1.c
func2.o:func2.c func1.h func2.h
	gcc -c func2.c
clean:
	$(RM) *.o myapp
