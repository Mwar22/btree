test: test.o btree.o lista.o
	gcc -o test test.o btree.o lista.o -lm

test.o: test.c
	gcc -c test.c

btree.o: btree.c btree.h list_library/lista.h
	gcc -c btree.c

lista.o: list_library/lista.c list_library/lista.h
	gcc -c list_library/lista.c

clean:
	rm test test.o btree.o lista.o
