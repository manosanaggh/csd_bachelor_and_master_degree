# Standard make targets. The previous file used names like "make spin:",
# which made make treat "make" as a real target and printed override warnings.

CC = gcc
CFLAGS = -pedantic -Wall -g -m32
LDLIBS = -lrt

.PHONY: clean all sieve sieve2 sieve4 sink sort spin spin2 spin3 debug run_and_log run

clean:
	rm -rf *.out *.log a.out

all:
	$(CC) $(CFLAGS) src/main.c src/thread.c src/queue.c src/swtch.s $(LDLIBS)

sieve:
	$(CC) $(CFLAGS) src/sieve.c src/thread.c src/sem.c src/chan.c src/queue.c src/swtch.s $(LDLIBS)

sieve2:
	$(CC) $(CFLAGS) src/sieve2.c src/thread.c src/sem.c src/chan.c src/queue.c src/swtch.s $(LDLIBS)

sieve4:
	$(CC) $(CFLAGS) src/sieve4.c src/thread.c src/sem.c src/chan.c src/queue.c src/swtch.s $(LDLIBS)

sink:
	$(CC) $(CFLAGS) src/sink.c src/thread.c src/sem.c src/chan.c src/queue.c src/swtch.s $(LDLIBS)

sort:
	$(CC) $(CFLAGS) src/sort.c src/thread.c src/queue.c src/swtch.s $(LDLIBS)

spin:
	$(CC) $(CFLAGS) src/spin.c src/thread.c src/queue.c src/swtch.s $(LDLIBS)

spin2:
	$(CC) $(CFLAGS) src/spin2.c src/thread.c src/sem.c src/queue.c src/swtch.s $(LDLIBS)

spin3:
	$(CC) $(CFLAGS) src/spin3.c src/thread.c src/sem.c src/queue.c src/swtch.s $(LDLIBS)

debug:
	gdb ./a.out

run_and_log:
	./a.out > mylog.log

run:
	./a.out
