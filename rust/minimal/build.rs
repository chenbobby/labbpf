use std::env;
use std::ffi;
use std::path;

use libbpf_cargo::SkeletonBuilder;

const SRC: &str = "src/bpf/minimal.bpf.c";

fn main() {
    let skeleton_output = path::PathBuf::from(
        env::var_os("CARGO_MANIFEST_DIR").expect("CARGO_MANIFEST_DIR must be set in build script"),
    )
    .join("src")
    .join("bpf")
    .join("minimal.skel.rs");

    SkeletonBuilder::new()
        .source(SRC)
        .clang_args([ffi::OsStr::new("-I/usr/include/x86_64-linux-gnu")])
        .build_and_generate(&skeleton_output)
        .unwrap();
    println!("cargo:rerun-if-changed={SRC}");
}
