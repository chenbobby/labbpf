minimal.bpf.o.tmp:
	clang \
		-target bpf \
		-g3 -Wall -Wextra \
		-I/usr/include/x86_64-linux-gnu \
		-c minimal.bpf.c \
		-o minimal.bpf.o.tmp

# Clang's default system includes, generated by `clang -v -E - </dev/null 2>&1`
# /usr/lib/llvm-14/lib/clang/14.0.6/include
# /usr/local/include
# /usr/include/x86_64-linux-gnu
# /usr/include

minimal.bpf.o: minimal.bpf.o.tmp
	bpftool gen object \
		minimal.bpf.o \
		minimal.bpf.o.tmp \

minimal.skel.h: minimal.bpf.o
	bpftool gen skeleton \
		minimal.bpf.o \
		> minimal.skel.h

minimal.o: minimal.skel.h
	clang \
		-g3 -Wall -Wextra \
		-c minimal.c \
		-o minimal.o

minimal: minimal.o
	clang \
		-g3 -Wall -Wextra \
		-lelf -lz \
		-o minimal \
		minimal.o ../libbpf/src/libbpf.a

.PHONY: clean
clean:
	rm -f minimal.bpf.o.tmp minimal.bpf.o minimal.skel.h minimal.o minimal
