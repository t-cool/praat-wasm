#!/bin/bash
# build_wasm.sh - Build script for WebAssembly version of Praat

echo "Building Praat for WebAssembly..."

# Check if emscripten is installed
if ! command -v emcc &> /dev/null; then
    echo "Error: Emscripten not found. Please install Emscripten SDK first."
    echo "Visit: https://emscripten.org/docs/getting_started/downloads.html"
    exit 1
fi

# Copy WebAssembly makefile configuration
cp makefiles/makefile.defs.wasm makefile.defs

# Clean previous build
echo "Cleaning previous build..."
make clean 2>/dev/null || true

# Build the project
echo "Building WebAssembly modules..."
emmake make all

# Check if build was successful
if [ -f "praat.js" ] && [ -f "praat.wasm" ]; then
    echo ""
    echo "✅ Build successful! Files generated:"
    echo "  - praat.js (JavaScript loader): $(du -h praat.js | cut -f1)"
    echo "  - praat.wasm (WebAssembly module): $(du -h praat.wasm | cut -f1)"

    # Copy to web directory
    cp praat.js praat.wasm web/ 2>/dev/null
    echo ""
    echo "Files copied to web/ directory"
    echo ""
    echo "To run the application:"
    echo "  1. cd web"
    echo "  2. python3 server.py [port]"
    echo "  3. Open browser at: http://localhost:[port]/web/"
    echo ""
    echo "Note: Some function signature warnings are expected and can be ignored."
else
    echo "Build failed. Please check the error messages above."
    exit 1
fi