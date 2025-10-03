// test_wasm.c - Simple test program for WebAssembly build
#include <stdio.h>
#include <emscripten/emscripten.h>

// Keep function available after compilation
EMSCRIPTEN_KEEPALIVE
int add(int a, int b) {
    return a + b;
}

EMSCRIPTEN_KEEPALIVE
void say_hello() {
    printf("Hello from Praat WebAssembly!\n");
}

EMSCRIPTEN_KEEPALIVE
const char* get_version() {
    return "Praat WASM 1.0.0";
}

int main() {
    printf("Praat WebAssembly Test Module Initialized\n");
    return 0;
}