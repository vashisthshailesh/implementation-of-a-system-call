#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/fcntl.h>
#include <asm/uaccess.h>
#include <uapi/asm-generic/errno-base.h>
#define _GNU_SOURCE
#include <linux/string.h>
#include <linux/signal.h>
#include "taskinfo.h"
#define NSIG 32
void write_to_file(struct file *file, char* data)
{
    file->f_op->write(file, data, strlen(data), &file->f_pos);
}
char* find_signal(int signo)
{
    char* name = NULL;
    switch(signo)
    {
        case 1: strcpy(name, "SIGHUP");
            break;
        case 2: strcpy(name, "SIGINT");
            break;
        case 3: strcpy(name, "SIGQUIT");
            break;
        case 4: strcpy(name, "SIGILL");
            break;
        case 5: strcpy(name, "SIGTRAP");
            break;
        case 6: strcpy(name, "SIGABRT, SIGIOT");
            break;
        case 7: strcpy(name, "SIGBUS");
            break;
        case 8: strcpy(name, "SIGFPE");
            break;
        case 9: strcpy(name, "SIGKILL");
            break;
        case 10: strcpy(name, "SIGUSR1");
            break;
        case 11: strcpy(name, "SIGSEGV");
            break;
        case 12: strcpy(name, "SIGUSR2");
            break;
        case 13: strcpy(name, "SIGPIPE");
            break;
        case 14: strcpy(name, "SIGALRM");
            break;
        case 15: strcpy(name, "SIGTERM");
            break;
        case 16: strcpy(name, "SIGSTKFLT");
            break;
        case 17: strcpy(name, "SIGCHLD");
            break;
        case 18: strcpy(name, "SIGCONT");
            break;
        case 19: strcpy(name, "SIGSTOP");
            break;
        case 20: strcpy(name, "SIGTSTP");
            break;
        case 21: strcpy(name, "SIGTTIN");
            break;
        case 22: strcpy(name, "SIGTTOU");
            break;
        case 23: strcpy(name, "SIGURG");
            break;
        case 24: strcpy(name, "SIGXCPU");
            break;
        case 25: strcpy(name, "SIGXFSZ");
            break;
        case 26: strcpy(name, "SIGVTALRM");
            break;
        case 27: strcpy(name, "SIGPROF");
            break;
        case 28: strcpy(name, "SIGWINCH");
            break;
        case 29: strcpy(name, "SIGIO, SIGPOLL");
            break;
        case 30: strcpy(name, "SIGPWR");
            break;
        case 31: strcpy(name, "SIGSYS, SIGUNUSED");
            break;
        case 32: strcpy(name, "SIGRTMIN");
            break;
    }
    return name;
}
asmlinkage long process(int pid, char* filename)
{
    if (pid > 32768 || pid <= 0)
        return -EINVAL;
    struct task_struct *task;
    struct file *file;
    char data[500], concat[500];
    loff_t pos = 0;
    int fd;
    
    mm_segment_t old_fs = get_fs();
    set_fs(KERNEL_DS);
    
    fd = sys_open(filename, O_WRONLY|O_CREAT, 0644);
    for_each_process(task)
    {
        if ((int)task->pid == pid)
        {
            printk("PID Number: %ld\n", (long)task->pid);
            strcat(data, "PID Number: ");
            sprintf(concat, "%ld\n", (long)task->pid);
            strcat(data, concat);
            
            printk("TGID Number: %ld\n", (long)task->tgid);
            strcat(data, "TGID Number: ");
            sprintf(concat, "%ld\n", (long)task->tgid);
            strcat(data, concat);
            
            printk("Process State: %ld\n", (long)task->state);
            strcat(data, "Process State: ");
            sprintf(concat, "%ld\n", (long)task->state);
            strcat(data, concat);
            
            printk("Priority: %ld\n", (long)task->prio);
            strcat(data, "Priority: ");
            sprintf(concat, "%ld\n", (long)task->prio);
            strcat(data, concat);
            
            printk("RT_Priority: %ld\n", (long)task->rt_priority);
            strcat(data, "RT_Priority: ");
            sprintf(concat, "%ld\n", (long)task->rt_priority);
            strcat(data, concat);
            
            printk("Static Priority: %ld\n", (long)task->static_prio);
            strcat(data, "Static Priority: ");
            sprintf(concat, "%ld\n", (long)task->static_prio);
            strcat(data, concat);
            
            printk("Normal Priority: %ld\n", (long)task->normal_prio);
            strcat(data, "Normal Priority: ");
            sprintf(concat, "%ld\n", (long)task->normal_prio);
            strcat(data, concat);
            
            printk("CPU on_cpu: %ld\n", (long)task->on_cpu);
            strcat(data, "CPU: ");
            sprintf(concat, "%ld\n", (long)task->on_cpu);
            strcat(data, concat);
            
            printk("Sched on_rq: %ld\n", (long)task->se.on_rq);
            strcat(data, "Sched on_rq: ");
            sprintf(concat, "%ld\n", (long)task->se.on_rq);
            strcat(data, concat);
            
            printk("Sched exec_start: %llu\n", task->se.exec_start);
            strcat(data, "Sched exec_start: ");
            sprintf(concat, "%llu\n", task->se.exec_start);
            strcat(data, concat);
            
            printk("Sched sum_exec_runtime: %llu\n", task->se.sum_exec_runtime);
            strcat(data, "Sched sum_exec_runtime: ");
            sprintf(concat, "%llu\n", task->se.sum_exec_runtime);
            strcat(data, concat);
            
            printk("Sched vruntime: %llu\n", task->se.vruntime);
            strcat(data, "Sched vruntime: ");
            sprintf(concat, "%llu\n", task->se.vruntime);
            strcat(data, concat);
            
            printk("Sched prev_sum_exec_runtime: %llu\n", task->se.prev_sum_exec_runtime);
            strcat(data, "Sched prev_sum_exec_runtime: ");
            sprintf(concat, "%llu\n", task->se.prev_sum_exec_runtime);
            strcat(data, concat);
            
            printk("Blocked Signal Set: ");
            strcat(data, "Blocked Signal Set: ");
            
            int i, count=0;
            for (i = 1; i < NSIG; i++)
            {
                if (sigismember(&task->blocked, i))
                {
                    count++;
                    char* sig_name = find_signal(i);
                    printk("%d %s\n", i, sig_name);
                    sprintf(concat, "%d %s", i, sig_name);
                    strcat(data, concat);
                }
            }
            if (count == 0)
            {
                printk("<Empty>\n");
                strcat(data, "<Empty>\n");
            }
            
            printk("Real Blocked Signal Set: ");
            strcat(data, "Real Blocked Signal Set: ");
            count=0;
            for (i = 1; i < NSIG; i++)
            {
                if (sigismember(&task->real_blocked, i))
                {
                    count++;
                    char* sig_name = find_signal(i);
                    printk("%d %s\n", i, sig_name);
                    sprintf(concat, "%d %s", i, sig_name);
                    strcat(data, concat);
                }
            }
            if (count == 0)
            {
                printk("<Empty>\n");
                strcat(data, "<Empty>\n");
            }
            
            if (fd < 0)
                return -EISDIR;
            file = fget(fd);
            write_to_file(file, data);
        }
        printk("\n\n");
    }
    set_fs(old_fs);
    return 0;
}
