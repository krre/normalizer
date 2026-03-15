web_dir := "web"
wasm_dir := "wasm"

# Build and run
all: wasm web

# Build WASM module
[working-directory: 'wasm']
wasm:
    wasm-pack build --target web --out-dir ../{{web_dir}}/src/lib/wasm

# Run frontend
[working-directory: 'web']
web:
    npm run dev

# Build WASM + Frontend
[working-directory: 'web']
build:
    wasm
    npm run build

# Cleanup all
clean:
    cd {{wasm_dir}} && cargo clean
    rm -rf {{web_dir}}/src/lib/wasm
    rm -rf {{web_dir}}/dist
