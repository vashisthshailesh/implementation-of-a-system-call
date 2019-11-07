# implementation-of-a-system-call


– Description of your code and how you implemented the function – the logical and  implementation details

Making a new system call ,let's say x() ,
 
Then the main entry point for this will be sys_x();

So to write about a new system call i will make a function sys_x() in a new and since it will return a value to kernel then it’s return type be long and as i would be needing information from stack(like the rest of the system calls) to write this system call I will be assigning the word asmlinkage prior to it .
asmlinkage long sys_process(pid_t pid, char *filename){...}

 --------------
But before we continue,  the new entry point also requires a  corresponding function prototype in include/linux/syscalls.h .

And as seen in the diff of syscalls.h we can see that one line has been added
+asmlinkage long sys_process(pid_t pid, char *filename);
-----------------

To wire up this system call we also have to assign it a syscall number in the syscall table .since we are working on the x86 arch we need to upadte the mster syscall table which is in

arch/x86/entry/syscalls/syscall_64.tbl

We can see the following line is added in the diff of syscall_64.tbl

+318    common  process			    sys_process

And similarly for 32 bit 

-----------------

So now let's go back to implement the “asmlinkage long sys_process(pid_t pid, char *filename)” funciton.


Things to look for (errors to be handled)

 if it the passed pid is wrong then return EINVAL
If file passed is a directory-type return EISDIR

Making an object of task struct and then storing its value in a variable and last adding that to a file.
 
For every parameter  of the above mentioned object we have to store their current value for  which we can use sprintf() and strcat(), now that the value is stored in a buffer via the sprintf command we can then add 2 strings using strcat and then we can store all their attributes(like priority) in a storing string, we would also like to reflect it in the kernel logs , as we can use that information afterwards for debugging. Hence we also use printk(), 


And to get the info for the blocked signal set.
We see which - which signal numbers are blocked for it and then correspondingly we convert it into the string signals(like  SIGHUP, SIGNINT), and and it to the storing string.


-----------------------------------------------------------------------------------------------------------------------------


The input user should give :- 

It should run the test file(./a.out) along with the parameters pid, the name of the file


-----------------------------------------------------------------------------------------------------------------------------


If the system call is executed without any error:
Then the below statement will be print
"System Call 'sh_task_info' executed correctly.\nUse dmesg to check processInfo\n" 
Else it will print
"System call sh_task_info did not execute as expected\n"

If the system call is executed correctly then the file name which was passed will have all the fields corresponding to the pid.


------------------------------------------------------------------------------------------------------------------------------

If the pid doesn’t exist then it will show error

Instead of passing a file a directory is passed it will show error

If the number of input arguments are not same then it will say need more input
