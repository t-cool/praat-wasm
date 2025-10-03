/* main_wasm.cpp
 * WebAssembly entry point for Praat
 * Provides C++ interface for JavaScript bindings
 */

#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include "../sys/praat.h"
#include "../sys/praatP.h"

#ifdef __cplusplus
extern "C" {
#endif

// Initialize Praat system
EMSCRIPTEN_KEEPALIVE
int praat_init() {
    try {
        // Initialize Melder
        Melder_setMessageProc(nullptr);

        // Initialize Praat without GUI
        praat_init_no_gui();

        return 0;  // Success
    } catch (...) {
        return -1;  // Failure
    }
}

// Execute a Praat script command
EMSCRIPTEN_KEEPALIVE
int praat_execute_command(const char* command) {
    try {
        // Parse and execute the command
        // This is a simplified version - real implementation would need
        // proper command parsing and execution

        autostring32 commandStr = Melder_dup(Melder_peek8to32(command));

        // Execute script line
        // Note: This would need proper implementation based on Praat's script engine

        return 0;  // Success
    } catch (MelderError) {
        Melder_clearError();
        return -1;  // Failure
    }
}

// Read audio file
EMSCRIPTEN_KEEPALIVE
int praat_read_audio(const char* filepath) {
    try {
        autostring32 path = Melder_dup(Melder_peek8to32(filepath));

        // Read the sound file
        // Note: Implementation would depend on Praat's file reading capabilities

        return 0;  // Success
    } catch (MelderError) {
        Melder_clearError();
        return -1;  // Failure
    }
}

// Save audio file
EMSCRIPTEN_KEEPALIVE
int praat_save_audio(const char* filepath) {
    try {
        autostring32 path = Melder_dup(Melder_peek8to32(filepath));

        // Save the sound file
        // Note: Implementation would depend on Praat's file writing capabilities

        return 0;  // Success
    } catch (MelderError) {
        Melder_clearError();
        return -1;  // Failure
    }
}

// Get Praat version
EMSCRIPTEN_KEEPALIVE
const char* praat_get_version() {
    static char version[256];
    snprintf(version, sizeof(version), "Praat WebAssembly %s",
             Melder_peek32to8(Melder_appVersionSTR()));
    return version;
}

// Clean up Praat resources
EMSCRIPTEN_KEEPALIVE
void praat_cleanup() {
    // Clean up any allocated resources
    praat_exit(0);
}

#ifdef __cplusplus
}
#endif

// Emscripten bindings for more complex operations
#ifdef EMSCRIPTEN_BINDINGS
EMSCRIPTEN_BINDINGS(praat_module) {
    emscripten::function("init", &praat_init);
    emscripten::function("executeCommand", &praat_execute_command);
    emscripten::function("readAudio", &praat_read_audio);
    emscripten::function("saveAudio", &praat_save_audio);
    emscripten::function("getVersion", &praat_get_version);
    emscripten::function("cleanup", &praat_cleanup);
}
#endif