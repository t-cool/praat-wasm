# Praat WebAssembly Build

This directory contains the WebAssembly build configuration for Praat, allowing it to run in web browsers.

## Prerequisites

1. **Emscripten SDK**: Install the Emscripten toolchain
   ```bash
   git clone https://github.com/emscripten-core/emsdk.git
   cd emsdk
   ./emsdk install latest
   ./emsdk activate latest
   source ./emsdk_env.sh
   ```

2. **Python 3**: For running the development server

## Building

1. Run the build script:
   ```bash
   ./build_wasm.sh
   ```

   This will:
   - Configure the build for WebAssembly
   - Compile all C/C++ sources to WASM
   - Generate JavaScript bindings
   - Create HTML interface files

## Running

1. Start the development server:
   ```bash
   cd web
   python3 server.py
   ```

   Or using npm:
   ```bash
   cd web
   npm install
   npm start
   ```

2. Open your browser at: http://localhost:8000/web/

## Project Structure

```
praat-ws/
├── build_wasm.sh              # Build script for WebAssembly
├── makefiles/
│   └── makefile.defs.wasm    # WebAssembly-specific build configuration
├── main/
│   └── main_wasm.cpp         # WebAssembly entry point and bindings
├── web/
│   ├── index.html            # Web interface
│   ├── praat_interface.js    # JavaScript API for Praat
│   ├── server.py             # Python development server
│   └── package.json          # npm configuration
└── README_WASM.md            # This file
```

## Features

- **File Upload**: Drag and drop or browse for audio files
- **Virtual File System**: Files are stored in browser's IndexedDB
- **Command Execution**: Run Praat commands through the web interface
- **File Download**: Export processed audio files

## Browser Requirements

- Modern browser with WebAssembly support
- SharedArrayBuffer support (for multi-threading, if enabled)
- IndexedDB for persistent storage

## Limitations

- Audio playback uses Web Audio API instead of native audio libraries
- GUI components are replaced with web interface
- Some platform-specific features may not be available

## Development

### Modifying the C++ Code

Edit `main/main_wasm.cpp` to add new exported functions. Use `EMSCRIPTEN_KEEPALIVE` macro for C functions or `EMSCRIPTEN_BINDINGS` for C++ bindings.

### Updating the Web Interface

- `web/index.html`: Main UI
- `web/praat_interface.js`: JavaScript API wrapper
- Styles and UI components are included in index.html

### Build Options

Edit `makefiles/makefile.defs.wasm` to modify:
- Optimization level (`-O2`, `-O3`, `-Os`)
- Memory limits (`TOTAL_MEMORY`, `STACK_SIZE`)
- Exported functions and runtime methods

## Troubleshooting

1. **Build fails**: Ensure Emscripten is properly installed and activated
2. **CORS errors**: Use the provided server scripts, not file:// protocol
3. **Out of memory**: Increase `TOTAL_MEMORY` in makefile.defs.wasm
4. **Performance issues**: Try different optimization levels

## License

This WebAssembly build maintains the same GPL-3.0 license as the original Praat software.