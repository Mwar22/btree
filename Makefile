test: test.o btree.o list.o
	gcc -o test test.o btree.o list.o -lm

test.o: test.c
	gcc -c test.c

btree.o: btree.c btree.h list_library/list.h
	gcc -c btree.c

list.o: list_library/list.c list_library/list.h
	gcc -c list_library/list.c

clean:
	rm test test.o btree.o list.o
