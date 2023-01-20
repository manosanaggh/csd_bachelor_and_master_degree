/*
Anagnostakis Emmanouil
csd3618
*/


#include <stdio.h>
#include "d_params.h"

#define sys_set_deadlines(arg1,arg2,arg3,arg4,arg5) syscall(341, arg1,arg2,arg3,arg4,arg5)
#define sys_get_deadlines(arg1,arg2) syscall(342, arg1,arg2)

int main(){
        struct d_params d;
        long set, get;
        set = sys_set_deadlines(1,4,2,5,1);
        if(!set){
                printf("ok - set_deadlines returned %ld\n",set);
        }
        else printf("error %ld on set_deadlines\n",set);
}
