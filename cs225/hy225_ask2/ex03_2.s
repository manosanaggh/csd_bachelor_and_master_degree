.data
str1: .asciiz "xyz"
.text
main:
li $v0,1
la $a0,str1
syscall

