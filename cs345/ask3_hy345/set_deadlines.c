/*
Anagnostakis Emmanouil
csd3618
*/


#include <asm-generic/errno-base.h>
#include <linux/types.h>
#include <asm/current.h>
#include <linux/sched.h>
#include <asm-generic/syscalls.h>

asmlinkage long sys_set_deadlines(int pid, int soft, int hard, int expected, int priority){
        if(hard > soft && pid == -1){
                current->d.soft_deadline = soft;
                current->d.hard_deadline = hard;
                current->d.expected_computation = expected;
                current->d.priority = priority;
        }
        else if(hard > soft && pid > -1){
		struct task_struct *t;
		for_each_process(t){
			if(t != NULL && t->pid == pid){
				t->d.soft_deadline = soft;
				t->d.hard_deadline = hard;
				t->d.expected_computation = expected;
				t->d.priority = priority;
			}
		}
        }
        else return EINVAL;
        return 0;
}



