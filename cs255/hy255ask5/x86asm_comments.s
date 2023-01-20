# -----------------------------------
# Program x86asm.s
# Compute and print the sum 0+...+N
# -----------------------------------

	.section .data	#The data section is used for declaring initialized data or constants. This data does not change at runtime.
N:	.long 1000	    #A N constant with value 1000.
S:	.long 0		    #An S constant with value 0.
Msg:	.ascii "The sum from 0 to %d is %d\n\0"


	.section .text	#The text section is used for keeping the actual code.
.globl main
main:
	pushl %ebp	#Stores the stack frame of the calling function on the stack.
	movl %esp, %ebp	#Takes the current stack pointer and uses it as the frame for the called function.

 	# initialize
    movl N, %ebx	#Getting the first argument(which is N) and store it in register %ebx

 	# compute sum
L1:
	addl %ebx, S	#Add ebx value to S value. 
	decl %ebx       #Decrements ebx.
	cmpl $0, %ebx   #Checks if ebx is 0.
	jng  L2	    	#Jump L2 if not greater than.
    movl $L1, %eax	#Stores L1's value to eax register.
    jmp *%eax   	#Goes to the address stored in eax.

L2:
	# print result
	pushl S	    	#Pushes S to the stack.
	pushl N	        #Pushes S to the stack.
	pushl $Msg  	#Pushes the string value of Msg to the stack.
	call printf 	#Calls the printf function.
	popl %eax   	#Pops the address of eax.
	popl %eax   	#Pops the address of eax.
	popl %eax   	#Pops the address of eax.

	# exit
	movl $0, %eax  	#Stores zero to eax value.
    leave	    	#Destroys the stack frame of the called function.
 	ret             #Function return.
