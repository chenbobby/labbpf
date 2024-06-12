use libbpf_rs::skel::{OpenSkel, Skel, SkelBuilder};
use std::thread;
use std::time;

mod minimal {
    include!(concat!(
        env!("CARGO_MANIFEST_DIR"),
        "/src/bpf/minimal.skel.rs"
    ));
}

fn main() {
    // Initialize the BPF object skeleton builder.
    let mut minimal_skel_builder = minimal::MinimalSkelBuilder::default();
    minimal_skel_builder.obj_builder.debug(true);

    // Open the BPF object.
    let mut open_minimal_skel = minimal_skel_builder.open().unwrap();

    // Configure global variables in the BPF object.
    open_minimal_skel.bss_mut().PID = std::process::id() as i32;

    // Load and verify the BPF object.
    let mut minimal_skel = open_minimal_skel.load().unwrap();

    // Attach the BPF object.
    minimal_skel.attach().unwrap();

    println!("Successfully started! Please run `sudo cat /sys/kernel/debug/tracing/trace_pipe` to see output of the BPF programs.\n");

    // Trigger the BPF program's tracepoint handlers by performing a write syscall.
    loop {
        println!(".");
        thread::sleep(time::Duration::from_secs(1));
    }
}
