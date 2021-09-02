LOPTS = -Wall -Wextra -g
OBJS = integer.o real.o scanner.o string.o sll.o dll.o stack.o queue.o bst.o heap.o heapsort.o
OOPTS = -Wall -Wextra -g -c

all : test-sll test-dll test-stack test-queue test-bst test-heap heapsort

test: all
	./test-sll
	./test-dll
	./test-stack
	./test-queue
	./test-bst
	./test-heap
	./heapsort -r testr.txt

test-sll : test-sll.o integer.o string.o real.o sll.o
	gcc $(LOPTS) test-sll.o integer.o string.o real.o sll.o -o test-sll

test-dll : test-dll.o integer.o string.o real.o dll.o
	gcc $(LOPTS) test-dll.o integer.o string.o real.o dll.o -o test-dll

test-stack: test-stack.o integer.o string.o real.o stack.o
	gcc $(LOPTS) test-stack.o integer.o string.o real.o stack.o -o test-stack

test-queue: test-queue.o integer.o string.o real.o queue.o
	gcc $(LOPTS) test-queue.o integer.o string.o real.o queue.o -o test-queue

test-bst: test-bst.o integer.o queue.o real.o string.o bst.o
	gcc $(LOPTS) test-bst.o bst.o integer.o real.o string.o queue.o -o test-bst

test-heap: test-heap.o integer.o queue.o real.o string.o stack.o bst.o heap.o
	gcc $(LOPTS) test-heap.o heap.o bst.o integer.o real.o string.o queue.o stack.o -o test-heap

heapsort: heapsort.o integer.o queue.o real.o string.o stack.o bst.o heap.o scanner.o
	gcc $(LOPTS) heapsort.o heap.o bst.o integer.o real.o string.o queue.o stack.o scanner.o -o heapsort

test-sll.o : test-sll.c sll.h integer.h real.h string.h
	gcc $(OOPTS) test-sll.c

test-dll.o : test-dll.c dll.h integer.h real.h string.h 
	gcc $(OOPTS) test-dll.c

test-bst.o : test-bst.c bst.h integer.h real.h string.h queue.h
	gcc $(OOPTS) test-bst.c

test-heap.o : test-heap.c integer.h real.h string.h heap.h bst.h queue.h stack.h
	gcc $(OOPTS) test-heap.c

test-stack.o : test-stack.c stack.h integer.h real.h string.h
	gcc $(OOPTS) test-stack.c

test-queue.o : test-queue.c queue.h integer.h real.h string.h
	gcc $(OOPTS) test-queue.c	

integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c

scanner.o : scanner.c scanner.h
	gcc $(OOPTS) scanner.c

sll.o : sll.c sll.h
	gcc $(OOPTS) sll.c

string.o : string.c string.h
	gcc $(OOPTS) string.c

real.o : real.c real.h
	gcc $(OOPTS) real.c

dll.o : dll.c dll.h
	gcc $(OOPTS) dll.c

queue.o : queue.c queue.h
	gcc $(OOPTS) queue.c

stack.o : stack.c stack.h
	gcc $(OOPTS) stack.c

bst.o : bst.c bst.h queue.h
	gcc $(OOPTS) bst.c 

heap.o : heap.c heap.h bst.h queue.h stack.h 
	gcc $(OOPTS) heap.c

heapsort.o : integer.h string.h real.h bst.h heap.h scanner.h
	gcc $(OOPTS) heapsort.c

valgrind : all
	valgrind ./test-sll
	valgrind ./test-dll
	valgrind ./test-stack
	valgrind ./test-queue
	valgrind ./test-bst
	valgrind ./test-heap

clean : 
	rm -f $(OBJS) test-*.o

		
		