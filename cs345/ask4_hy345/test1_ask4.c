#include <stdio.h>
#include "d_params.h"

#define sys_set_deadlines(arg1,arg2,arg3,arg4,arg5) syscall(341, arg1,arg2,arg3,arg4,arg5)
#define sys_get_deadlines(arg1,arg2) syscall(342, arg1,arg2)

int main(){
        struct d_params d;
        long set, get;
        sys_set_deadlines(1,2,4,3,1);
        sys_set_deadlines(2,6,7,7,2);
        sys_set_deadlines(3,10,13,11,3);
        sys_set_deadlines(4,14,16,15,4);
        sys_set_deadlines(5,18,20,19,5);
//	__sched schedule();
}

