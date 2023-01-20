Anagnostakis Emmanouil
csd3618

Akolouthisa ta vhmata pou perigrafontai sto frontistirio kai stin ekfwnisi tis askisis gia tin ylopoiisi twn system calls
1. Define a system call number

Edit: linux-2.6.38.1/arch/x86/include/asm/unistd_32.h

2. Define a function pointer

Edit: linux-2.6.38.1/arch/x86/kernel/syscall_table_32.S

3. Define a function

Edit: linux-2.6.38.1/include/asm-generic/syscalls.h

4. Implement the system call

H ulopoihsh se source code:

linux-2.6.38.1/kernel/set_deadlines.c
linux-2.6.38.1/kernel/get_deadlines.c

Ta test:

linux-2.6.38.1/kernel/test1.c

Testarei ta system calls me swsta arguments kai pid > -1.

linux-2.6.38.1/kernel/test2.c

Testarei ta system calls me lathos arguments, pid < -1 kai NULL d_arguments.

linux-2.6.38.1/kernel/test3.c

Testarei tin set_deadlines me soft_deadline > hard_deadline (lathos).

linux-2.6.38.1/kernel/test4.c

Testarei ta system calls me pid == -1 (current task).

Ola ta test trexoun opws prepei xwris lathi.



