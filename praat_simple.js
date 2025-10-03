// praat_simple.js - Simple wrapper for Praat WebAssembly

window.PraatWASM = {
    module: null,
    isInitialized: false,
    outputCallbacks: [],
    uploadedFiles: [],

    // Initialize Praat
    async init(options = {}) {
        if (this.isInitialized) return this.module;

        console.log('Initializing Praat WebAssembly...');

        const config = {
            // Prevent Praat from exiting immediately
            arguments: [],

            // Don't run main automatically
            noInitialRun: true,

            preRun: [() => {
                console.log('PreRun: Setting up file system...');
            }],

            postRun: [() => {
                console.log('PostRun: Creating directories...');
                if (this.module && this.module.FS) {
                    try {
                        this.module.FS.mkdir('/workspace');
                    } catch (e) {
                        console.log('workspace dir exists');
                    }
                    try {
                        this.module.FS.mkdir('/uploads');
                    } catch (e) {
                        console.log('uploads dir exists');
                    }
                    try {
                        this.module.FS.mkdir('/output');
                    } catch (e) {
                        console.log('output dir exists');
                    }
                    console.log('File system ready');
                }
            }],

            print: (text) => {
                console.log('Praat:', text);
                this.outputCallbacks.forEach(cb => cb(text, false));
            },

            printErr: (text) => {
                // Filter out expected errors
                if (!text.includes('no-GUI edition') &&
                    !text.includes('program exited') &&
                    !text.includes('keepRuntimeAlive')) {
                    console.error('Praat Error:', text);
                    this.outputCallbacks.forEach(cb => cb(text, true));
                }
            },

            noExitRuntime: true,

            onRuntimeInitialized: () => {
                console.log('✅ Praat WASM Runtime initialized');
                this.isInitialized = true;
            },

            ...options
        };

        try {
            // Check if PraatModule exists
            if (typeof PraatModule === 'undefined') {
                throw new Error('PraatModule is not loaded yet');
            }

            this.module = await PraatModule(config);
            console.log('Module loaded, FS available:', !!this.module.FS);

            // Create directories after module is loaded
            if (this.module && this.module.FS) {
                try {
                    this.module.FS.mkdir('/workspace');
                } catch (e) {}
                try {
                    this.module.FS.mkdir('/uploads');
                } catch (e) {}
                try {
                    this.module.FS.mkdir('/output');
                } catch (e) {}
                console.log('Directories created successfully');
            }

            return this.module;
        } catch (error) {
            console.error('Failed to initialize Praat:', error);
            throw error;
        }
    },

    // Add output listener
    onOutput(callback) {
        this.outputCallbacks.push(callback);
    },

    // Load an audio file
    async loadAudioFile(file) {
        if (!this.isInitialized || !this.module) {
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
                    this.uploadedFiles.push(path);
                    resolve(path);
                } catch (error) {
                    reject(error);
                }
            };

            reader.onerror = reject;
            reader.readAsArrayBuffer(file);
        });
    },

    // Run a Praat script
    async runScript(scriptContent) {
        if (!this.isInitialized || !this.module) {
            throw new Error('Praat not initialized. Call init() first.');
        }

        const FS = this.module.FS;
        const scriptPath = '/workspace/temp_script.praat';

        try {
            // Write script to virtual filesystem
            FS.writeFile(scriptPath, scriptContent);
            console.log('Script written to:', scriptPath);

            // Note: Actual script execution would require Praat API bindings
            // This is a placeholder showing the concept
            console.log('Script content:', scriptContent);

            return true;
        } catch (error) {
            console.error('Error running script:', error);
            throw error;
        }
    },

    // List files in a directory
    listFiles(directory = '/uploads') {
        if (!this.isInitialized || !this.module) {
            console.warn('Praat not initialized yet');
            return [];
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
    },

    // Download file
    downloadFile(virtualPath, downloadName) {
        if (!this.isInitialized || !this.module) {
            throw new Error('Praat not initialized.');
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
};

console.log('PraatWASM simple wrapper loaded');