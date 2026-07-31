make clean:
	rm -rf *.out *.log

make all:
	gcc -pedantic -Wall -g -m32 src/main.c src/thread.c src/queue.c src/swtch.s -lrt

make sieve:
	gcc -pedantic -Wall -g -m32 src/sieve.c src/thread.c src/sem.c src/chan.c src/queue.c src/swtch.s -lrt

make sieve2:
	gcc -pedantic -Wall -g -m32 src/sieve2.c src/thread.c src/sem.c src/chan.c src/queue.c src/swtch.s -lrt

make sieve4:
	gcc -pedantic -Wall -g -m32 src/sieve4.c src/thread.c src/sem.c src/chan.c src/queue.c src/swtch.s -lrt

make sink:
	gcc -pedantic -Wall -g -m32 src/sink.c src/thread.c src/sem.c src/chan.c src/queue.c src/swtch.s -lrt

make sort:
	gcc -pedantic -Wall -g -m32 src/sort.c src/thread.c src/queue.c src/swtch.s -lrt

make spin:
	gcc -pedantic -Wall -g -m32 src/spin.c src/thread.c src/queue.c src/swtch.s -lrt

make spin2:
	gcc -pedantic -Wall -g -m32 src/spin2.c src/thread.c src/sem.c src/queue.c src/swtch.s -lrt

make spin3:
	gcc -pedantic -Wall -g -m32 src/spin3.c src/thread.c src/sem.c src/queue.c src/swtch.s -lrt

make debug:
	gdb ./a.out

make run_and_log:
	./a.out > mylog.log

make run:
	./a.out
