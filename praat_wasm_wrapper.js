// praat_wasm_wrapper.js - Wrapper for Praat WebAssembly module

class PraatWASM {
    constructor() {
        this.module = null;
        this.isInitialized = false;
        this.outputCallbacks = [];
    }

    async init(options = {}) {
        if (this.isInitialized) return this.module;

        const config = {
            // Prevent Praat from running interactively
            arguments: ['--no-interactive'],

            // File system setup
            preRun: [() => {
                if (this.module.FS) {
                    // Create necessary directories
                    try {
                        this.module.FS.mkdir('/workspace');
                        this.module.FS.mkdir('/uploads');
                        this.module.FS.mkdir('/output');
                    } catch (e) {
                        // Directories might already exist
                    }
                }
            }],

            // Capture output
            print: (text) => {
                console.log('Praat:', text);
                this.outputCallbacks.forEach(cb => cb(text, false));
            },

            printErr: (text) => {
                // Filter out the no-GUI warning
                if (!text.includes('no-GUI edition')) {
                    console.error('Praat Error:', text);
                    this.outputCallbacks.forEach(cb => cb(text, true));
                }
            },

            // Keep runtime alive for async operations
            noExitRuntime: true,

            // Override default behavior
            onRuntimeInitialized: () => {
                console.log('Praat WASM Runtime initialized');
                this.isInitialized = true;
            },

            ...options
        };

        try {
            this.module = await PraatModule(config);
            return this.module;
        } catch (error) {
            console.error('Failed to initialize Praat:', error);
            throw error;
        }
    }

    // Add output listener
    onOutput(callback) {
        this.outputCallbacks.push(callback);
    }

    // Run a Praat script
    async runScript(scriptContent) {
        if (!this.isInitialized) {
            throw new Error('Praat not initialized. Call init() first.');
        }

        const FS = this.module.FS;
        const scriptPath = '/workspace/temp_script.praat';

        try {
            // Write script to virtual filesystem
            FS.writeFile(scriptPath, scriptContent);

            // Run the script using ccall if available
            if (this.module.ccall) {
                // Try to call a Praat function to execute script
                // This would need the actual Praat API function name
                console.log('Running script:', scriptPath);
                // this.module.ccall('praat_run_script', 'number', ['string'], [scriptPath]);
            }

            return true;
        } catch (error) {
            console.error('Error running script:', error);
            throw error;
        }
    }

    // Load an audio file
    async loadAudioFile(file) {
        if (!this.isInitialized) {
            throw new Error('Praat not initialized. Call init() first.');
        }

        const FS = this.module.FS;
        const reader = new FileReader();

        return new Promise((resolve, reject) => {
            reader.onload = (e) => {
                const data = new Uint8Array(e.target.result);
                const path = `/uploads/${file.name}`;

                try {
                    FS.writeFile(path, data);
                    console.log(`File loaded: ${path} (${data.length} bytes)`);
                    resolve(path);
                } catch (error) {
                    reject(error);
                }
            };

            reader.onerror = reject;
            reader.readAsArrayBuffer(file);
        });
    }

    // Save a file from virtual filesystem
    downloadFile(virtualPath, downloadName) {
        if (!this.isInitialized) {
            throw new Error('Praat not initialized. Call init() first.');
        }

        const FS = this.module.FS;

        try {
            const data = FS.readFile(virtualPath);
            const blob = new Blob([data], { type: 'application/octet-stream' });
            const url = URL.createObjectURL(blob);

            const a = document.createElement('a');
            a.href = url;
            a.download = downloadName || virtualPath.split('/').pop();
            document.body.appendChild(a);
            a.click();
            document.body.removeChild(a);
            URL.revokeObjectURL(url);

            return true;
        } catch (error) {
            console.error('Error downloading file:', error);
            throw error;
        }
    }

    // List files in a directory
    listFiles(directory = '/uploads') {
        if (!this.isInitialized) {
            throw new Error('Praat not initialized. Call init() first.');
        }

        const FS = this.module.FS;

        try {
            const files = FS.readdir(directory).filter(f => f !== '.' && f !== '..');
            return files.map(filename => {
                const path = `${directory}/${filename}`;
                const stat = FS.stat(path);
                return {
                    name: filename,
                    path: path,
                    size: stat.size,
                    isDirectory: FS.isDir(stat.mode)
                };
            });
        } catch (error) {
            console.error('Error listing files:', error);
            return [];
        }
    }

    // Get file system object
    get FS() {
        return this.module ? this.module.FS : null;
    }
}

// Create global instance
const praatInstance = new PraatWASM();

// Export with both patterns for compatibility
window.PraatWASM = praatInstance;

// Also make sure it's available immediately
if (typeof window !== 'undefined') {
    window.PraatWASM = praatInstance;
}