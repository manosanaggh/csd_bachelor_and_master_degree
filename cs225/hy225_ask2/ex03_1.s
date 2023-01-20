      .data
a: .space  32
rdprompt: .asciiz "Enter 8 numbers: "
borderLine: .asciiz "----------------"
sp: .asciiz " "
	  .text    
	  .globl loop
main:
	  addi $16,$0,32 #end of loop
	  addi $17,$0,0 #i=0;
	  #Printing prompt:
      li $v0,4
	  la $a0,rdprompt
	  syscall
loop:
	  #Reading the integer:
      li $v0,5
	  syscall
	  addi $t0,$v0,0  
	  sw $t0,a($17)
	  #Increasing loop counter and check
	  addi $17,$17,4 #i++;
	  bne $17,$16,loop #repeat while i < 8
	  #Printing borderline
	  li $v0,4
	  la $a0,borderLine
	  syscall
	  addi $17,$0,32
loop2:
      lw $t6,a($17)
	  add $t1,$t6,$t6
	  add $t2,$t1,$t1
	  add $t3,$t1,$t2
	  #Printing out the number
	  li $v0,1
	  addi $a0,$t3,0
	  syscall
	  #Printing a space
	  li $v0,4
	  la $a0,sp
	  syscall
	  addi $17,$17,-4
	  bne $0,$17,loop2
	  j main
	  
	  
	  

      
	  
	  
	  