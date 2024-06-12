#include <stdio.h>

#include <bpf/libbpf.h>

#include "minimal.skel.h"

static int libbpf_print_fn(enum libbpf_print_level level,
                           const char* format,
                           va_list args) {
    return vfprintf(stderr, format, args);
}

int main(int argc, char** argv) {
    struct minimal_bpf* skel;
    int err;

    libbpf_set_print(libbpf_print_fn);

    return 0;
}
