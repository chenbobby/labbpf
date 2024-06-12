# rust-bpf

## Setup

1. Install `bpftool`

```
git clone --recurse-submodules ...
```

2. Generate `vmlinux.h`

```
bpftool btf dump file /sys/kernel/btf/vmlinux format c > ./include/bpf/vmlinux.h
```

3. Install `libbpf-cargo`

```
cargo install libbpf-cargo
```
