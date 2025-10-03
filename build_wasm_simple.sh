#!/bin/bash
# Simple WebAssembly build script for testing

echo "Building simple Praat WebAssembly test..."

# Compile the test module
emcc test_wasm.c -o web/praat_test.js \
    -s EXPORTED_FUNCTIONS='["_add","_say_hello","_get_version","_main"]' \
    -s EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' \
    -s MODULARIZE=1 \
    -s EXPORT_NAME='PraatTestModule' \
    -O2

if [ $? -eq 0 ]; then
    echo "Build successful!"
    echo "Files generated in web/ directory:"
    ls -la web/praat_test.*
    echo ""
    echo "To test:"
    echo "1. cd web"
    echo "2. python3 server.py"
    echo "3. Open http://localhost:8000/test.html"
else
    echo "Build failed!"
    exit 1
fi