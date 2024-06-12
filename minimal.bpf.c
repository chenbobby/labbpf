#include <linux/bpf.h>

#include <bpf/bpf_helpers.h>

int my_pid = 0;

SEC("tp/syscall/sys_enter_write")
int handle_tp(void* ctx) {
    int pid = bpf_get_current_pid_tgid() >> 32;

    if (pid != my_pid) {
        return 0;
    }

    bpf_printk("Entering `write` syscall from PID %d\n", pid);

    return 0;
}