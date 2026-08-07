# Build and run
all: build run

# Build WASM module
build:
    zig build

# Run web server
[working-directory('zig-out/web')]
run:
    python3 -m http.server 8000 --bind 127.0.0.1

# Build WAT module
[working-directory('zig-out/web')]
wat: build
    wasm2wat lib.wasm -o lib.wat

# Cleanup all
[working-directory('zig-out')]
clean:
    rm -rf web
