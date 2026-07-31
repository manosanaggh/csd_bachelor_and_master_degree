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
