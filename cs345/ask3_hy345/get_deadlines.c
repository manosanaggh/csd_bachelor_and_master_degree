/*
Anagnostakis Emmanouil
csd3618
*/


#include <asm-generic/errno-base.h>
#include <linux/types.h>
#include <asm/current.h>
#include <linux/sched.h>
#include <asm-generic/syscalls.h>

asmlinkage long sys_get_deadlines(int pid, struct d_params *d_arguments){
        struct task_struct *t;
	if(pid > -1 && d_arguments != NULL){

	for_each_process(t){
		if(t != NULL && t->pid == pid){
			d_arguments->soft_deadline = t->d.soft_deadline;
			d_arguments->hard_deadline = t->d.hard_deadline;
			d_arguments->expected_computation = t->d.expected_computation;
			d_arguments->priority = t->d.priority;
		}
	}

	}
	else if(pid == -1 && d_arguments != NULL){
                        d_arguments->soft_deadline = current->d.soft_deadline;
                        d_arguments->hard_deadline = current->d.hard_deadline;
                        d_arguments->expected_computation = current->d.expected_computation;
                        d_arguments->priority = current->d.priority;
	}
	else return EINVAL;
        return 0;
}



