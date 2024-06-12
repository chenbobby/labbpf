#include <linux/bpf.h>

#include <bpf/bpf_helpers.h>

char LICENSE[] SEC("license") = "GPL";

// Global configuration variables
int PID;

// Tracepoint handlers
SEC("tp/syscalls/sys_enter_write")
int handle_tp_syscalls_sys_enter_write(void* ctx) {
    int current_pid = bpf_get_current_pid_tgid() >> 32;

    if (current_pid != PID) {
        return 0;
    }

    bpf_printk("Entering `write` syscall from PID %d\n", current_pid);

    return 0;
}
