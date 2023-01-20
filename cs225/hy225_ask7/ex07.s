.align 2

.data
	space: .asciiz " "
	newLine: .asciiz "\n"

.text
.globl main

read_int:
	addi $v0,$0,5 #system call for read int
	syscall	
	jr $ra
	
node_alloc:
	addi $a0,$0,8#a new node...
	addi $v0,$0,9
	syscall
	jr $ra

main:
	jal node_alloc
	addi $s0,$v0,0 #$s0 is the head of the list
	addi $s1,$v0,0 #s1 is the tail of the list
	addi $s7,$v0,0
	sw $0,0($v0) #dummy data=0
	sw $0,4($v0) #dummy nxtPtr=0

loop1:
	jal read_int
	addi $t0,$v0,0 #$t0 is the data to be inserted to the new node
	beq $t0,$0,out #if data=0 continue to print the list
	slt $t6,$t0,$0 #if data<0 continue to print the list
	bne $t6,$0,out
	jal node_alloc
	sw $t0,0($v0) #we store the number read to the data section of the new node
	sw $0,4($v0) #next is 0(null)
	sw $v0,4($s7) #and the new node is the next of the previous
	addi $s1,$v0,0
	addi $s7,$v0,0 #temp previous node
	j loop1

traverseList:
	addi $v0,$0,4
	la $a0,newLine
	syscall
	jal read_int
	addi $a1,$v0,0 #keep it in $s1
	addi $s1,$v0,0
	slt $t6,$a1,$0 #if int is negative finish program
	bne $t6,$0,finish
	addi $a0,$s0,0 #keep head in $a0
	addi $s2,$s0,0
	jal search_list
	j traverseList

search_list:
	addi $a0,$s2,0
	addi $a1,$s1,0
	jal print_node
	lw $s5,4($s2)
	beq $s5,$0,out
	addi $s2,$s5,0
	j search_list

print_node:
	lw $t5,0($a0)#
	slt $t6,$t5,$a1#
	bne $t6,$0,printData#
	jr $ra
	
printData:
	addi $v0,$0,1
	addi $a0,$t5,0
	syscall
	addi $v0,$0,4
	la $a0,space
	syscall
	jr $ra

out:
	j traverseList

finish:
	j finish









