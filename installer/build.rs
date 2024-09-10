fn main() {
    cc::Build::new()
        .file("src/impl/registry/write_registry.c")
        .include(".")
        .compile("write_registry");
}