Everything asked by the man pages is implemented | max number of threads = 1 million (try with 100k because of memory problems) | * means all options

There are 3 print statements activated, one for showing an interval outside of library and my functions combined with one showing context switches in the handler 
and one for the end of program.



Build instructions:

make clean -> clean all executables and log files
make "test name" (e.g. sieve, sieve2 etc.) -> build for a certain test
(!ignore) make all -> was used to build a test of mine
(!ignore) make run -> was used to run the above test
(!ignore) make run_and_log -> was used to run the above test and write the output to a log
(!ignore) make debug -> was used to call gdb





Test run examples

------------------

General pattern:

1) Build one test:
   make <test-name>

2) Run the produced executable:
   ./a.out [arguments]

The Makefile always writes the executable as ./a.out, so build the test you want immediately before running it.
If you want to avoid hangs while experimenting, run through timeout, for example:
   timeout 5 ./a.out 10

Available tests:

all / main.c
Build:
   make all
Run:
   ./a.out

spin
Purpose: creates m worker threads; each worker decrements a shared counter copy and increments global n.
Arguments:
   argv[1] = number of worker threads, default 5
Examples:
   make spin
   ./a.out
   ./a.out 10
   ./a.out 1000
Expected output shape:
   <actual> == <expected>

spin2
Purpose: semaphore-protected increments.
Arguments:
   argv[1] = number of worker threads, default 5
Examples:
   make spin2
   ./a.out
   ./a.out 10
   ./a.out 1000
Expected output shape:
   <actual> = <expected>

spin3
Purpose: repeated semaphore-protected increment batches.
Arguments:
   argv[1] = worker threads per batch, default 4
   argv[2] = number of batches, default 3
Examples:
   make spin3
   ./a.out
   ./a.out 10 3
   ./a.out 100 10

sort
Purpose: quicksort using custom threads for large partitions.
Arguments:
   argv[1] = number of array elements, default 100000
   argv[2] = cutoff for creating new sort threads, default 10000
Examples:
   make sort
   ./a.out
   ./a.out 1000
   ./a.out 100000 50000
Expected final output:
   sorted

sink
Purpose: channel send/receive test that prints numbers from 0 up to limit - 1.
Arguments:
   argv[1] = limit, default 100
Examples:
   make sink
   ./a.out
   ./a.out 20
   ./a.out 1000

sieve
Purpose: prime sieve with channel pipeline.
Arguments:
   argv[1] = upper limit for generated candidate numbers, default 100
   argv[2] = primes per sink/filter group, default 5
Examples:
   make sieve
   ./a.out
   ./a.out 1000 5
   ./a.out 10000 4

sieve2
Purpose: prime sieve variant that prints a requested number of primes over a requested number of logical groups.
Arguments:
   argv[1] = number of primes to print, default 100
   argv[2] = number of groups/threads used to split the primes, default 16
Examples:
   make sieve2
   ./a.out
   ./a.out 100 10
   ./a.out 10000 100

sieve4
Purpose: prime sieve variant with explicit stop after nprime primes.
Arguments:
   argv[1] = number of primes to print, default 100
   argv[2] = primes per sink/filter group, default 5
Examples:
   make sieve4
   ./a.out
   ./a.out 100 10
   ./a.out 10000 100

Suggested quick smoke test sequence:

   make spin && timeout 5 ./a.out 10
   make spin2 && timeout 5 ./a.out 10
   make sort && timeout 5 ./a.out
   make sink && timeout 5 ./a.out 20
   make sieve && timeout 5 ./a.out 1000 5
   make sieve2 && timeout 5 ./a.out 100 10
   make sieve4 && timeout 5 ./a.out 100 10


Non-preemptive

------------------

sieve

Successful runs: (argv[1],argv[2]) = ("100000", "5"), (argv[1],argv[2]) = ("100000", "4"), (argv[1],argv[2]) = ("100000", "3"), (argv[1],argv[2]) = ("100000", "2")

Unsuccessful runs: (argv[1],argv[2]) = ("100000", "1")

------------------

sieve2

Successful runs: (argv[1],argv[2]) = ("10000", "1000"), (argv[1],argv[2]) = ("10000", "100") 

Unsuccessful runs: (argv[1],argv[2]) = ("100000", "1000"), (argv[1],argv[2]) = ("100000", "10000")

------------------

sieve4

Successful runs: (argv[1],argv[2]) = ("10000", "100"), (argv[1],argv[2]) = ("10000", "10")

Unsuccessful runs: (argv[1],argv[2]) = ("100000", "100"), (argv[1],argv[2]) = ("100000", "10")

------------------

sink

Successful runs: argv[1] = "1000", argv[1] = "10000", argv[1] = "100000", argv[1] = "1000000", argv[1] = "10000000" 

------------------

sort

Successful runs: default

-----------------

spin

Successful runs: argv[1] = "1000", argv[1] = "10000", argv[1] = "100000"                                                                                                                                                                                                                                                                                                 

------------------

spin2

Successful runs: argv[1] = "1000", argv[1] = "10000", argv[1] = "100000" 

------------------

spin3 

Successful runs: (argv[1],argv[2]) = ("100000", "1"), (argv[1],argv[2]) = ("1000", "100"), (argv[1],argv[2]) = ("10000", "10")






==================






Preemptive 0.5 ms interval

------------------

sieve

Successful runs: (argv[1],argv[2]) = ("100000", "4"), (argv[1],argv[2]) = ("100000", "3"), (argv[1],argv[2]) = ("100000", "5"), (argv[1],argv[2]) = ("10000", *)

Unsuccessful runs (intervals ,when outside of library and critical sections, create problems): 
(argv[1],argv[2]) = ("100000", "1"), (argv[1],argv[2]) = ("100000", "4"), (argv[1],argv[2]) = ("100000", "5"), (argv[1],argv[2]) = ("100000", "2"), (argv[1],argv[2]) = ("100000", "3")

------------------

sieve2

Successful runs : (argv[1],argv[2]) = ("10000", "1000"), (argv[1],argv[2]) = ("10000", "100")

Unsuccessful runs (intervals ,when outside of library and critical sections, create problems): 
(argv[1],argv[2]) = ("100000", "1000"), (argv[1],argv[2]) = ("100000", "10000")

------------------

sieve4

Successful runs: (argv[1],argv[2]) = ("10000", "100"), (argv[1],argv[2]) = ("10000", "10")

Unsuccessful runs (intervals ,when outside of library and critical sections, create problems): 
(argv[1],argv[2]) = ("100000", "100"), (argv[1],argv[2]) = ("100000", "10"), (argv[1],argv[2]) = ("10000", "10")

------------------

sink

Successful runs: argv[1] = "1000", argv[1] = "10000", argv[1] = "100000", argv[1] = "1000000", argv[1] = "10000000"
Unsuccesful runs (intervals ,when outside of library and critical sections, create problems):
argv[1] = "10000000" 
------------------

sort

Successful runs: default

-----------------

spin

Successful runs: argv[1] = "1000", argv[1] = "10000", argv[1] = "100000"                                                                                                                                                                    $

------------------

spin2

Successful runs: argv[1] = "1000", argv[1] = "10000", argv[1] = "100000"
Unsuccesful runs (SOMETIMES intervals ,when outside of library and critical sections, create problems):  argv[1] = "100000"

------------------

spin3

Successful runs: (argv[1],argv[2]) = ("100000", "1"), (argv[1],argv[2]) = ("1000", "100"), (argv[1],argv[2]) = ("10000", "10")
Unsuccesful runs: all of the above (SOMETIMES intervals ,when outside of library and critical sections, create problems)
