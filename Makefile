HEADERS = dllist.h

default: list

list.o: main.c dllist.c $(HEADERS)
	    gcc -c main.c -o main.o
	    gcc -c dllist.c -o dllist.o

list: main.o dllist.o
	    gcc main.o dllist.o -o list

clean:
	    -rm -f main.o
	    -rm -f dllist.o
			-rm -f list
