#include <stdio.h>
#include <unistd.h>

#include "minimal.skel.h"

// Callback function for libbpf to print errors and debugging information.
static int libbpf_print_fn(enum libbpf_print_level _level,
                           const char* format,
                           va_list args) {
    return vfprintf(stderr, format, args);
}

int main(int _argc, char** _argv) {
    struct minimal_bpf* program;
    int err;

    // Setup the libbpf callback function for printing errors and debugging
    // information.
    libbpf_set_print(libbpf_print_fn);

    // Open the BPF program.
    program = minimal_bpf__open();
    if (program == NULL) {
        fprintf(stderr, "Failed to open the `minimal` BPF program\n");
        return 1;
    }

    // Configure global variables in the BPF program.
    program->bss->my_pid = getpid();

    // Load and verify the BPF program.
    err = minimal_bpf__load(program);
    if (err != 0) {
        fprintf(stderr, "Failed to load and verify the BPF program\n");
        minimal_bpf__destroy(program);
        return err;
    }

    // Attach the BPF program's tracepoint handlers.
    err = minimal_bpf__attach(program);
    if (err != 0) {
        fprintf(stderr,
                "Failed to attach the BPF program's tracepoint handlers\n");
        minimal_bpf__destroy(program);
        return err;
    }

    printf("Successfully started! Please run `sudo cat "
           "/sys/kernel/debug/tracing/trace_pipe` "
           "to see output of the BPF programs.\n");

    while (true) {
        // Trigger the BPF program's tracepoint handlers by performing a write
        // syscall.
        fprintf(stderr, ".\n");
        sleep(1);
    }

    return 0;
}
