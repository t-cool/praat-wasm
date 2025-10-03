// praat_interface.js - JavaScript interface for Praat WebAssembly module

let PraatInstance = null;
let isInitialized = false;

// Initialize Praat WebAssembly module
async function initPraat() {
    if (isInitialized) return PraatInstance;

    try {
        // Check if PraatModule is available
        if (typeof PraatModule === 'undefined') {
            throw new Error('PraatModule is not loaded. Please wait for the script to load.');
        }

        // Load the Praat module
        PraatInstance = await PraatModule({
            locateFile: (path) => {
                if (path.endsWith('.wasm')) {
                    return 'praat.wasm';
                }
                return path;
            },
            onRuntimeInitialized: () => {
                console.log('Praat WebAssembly runtime initialized');
                setupFileSystem();
            },
            print: (text) => {
                console.log('Praat:', text);
                appendOutput(text);
            },
            printErr: (text) => {
                console.error('Praat Error:', text);
                appendOutput(text, true);
            }
        });

        isInitialized = true;
        updateStatus('Praat initialized successfully');
        return PraatInstance;
    } catch (error) {
        console.error('Failed to initialize Praat:', error);
        updateStatus('Failed to initialize Praat: ' + error.message, true);
        throw error;
    }
}

// Setup virtual file system
function setupFileSystem() {
    if (!PraatInstance || !PraatInstance.FS) {
        console.error('PraatInstance or FS not available');
        return;
    }
    const FS = PraatInstance.FS;

    // Create working directories
    try {
        FS.mkdir('/workspace');
        FS.mkdir('/uploads');
        FS.mkdir('/downloads');
    } catch (e) {
        // Directories may already exist
    }

    // Mount IDBFS for persistent storage
    FS.mount(FS.filesystems.IDBFS, {}, '/workspace');

    // Sync from IndexedDB
    FS.syncfs(true, (err) => {
        if (err) {
            console.error('Failed to sync filesystem:', err);
        } else {
            console.log('Filesystem synced from IndexedDB');
        }
    });
}

// File upload handler
async function handleFileUpload(file) {
    if (!isInitialized) {
        await initPraat();
    }

    const FS = PraatInstance.FS;
    const reader = new FileReader();

    return new Promise((resolve, reject) => {
        reader.onload = (e) => {
            const data = new Uint8Array(e.target.result);
            const path = `/uploads/${file.name}`;

            try {
                FS.writeFile(path, data);
                updateStatus(`File uploaded: ${file.name}`);
                resolve(path);
            } catch (error) {
                updateStatus(`Failed to upload file: ${error.message}`, true);
                reject(error);
            }
        };

        reader.onerror = reject;
        reader.readAsArrayBuffer(file);
    });
}

// Execute Praat command
function executePraatCommand(command) {
    if (!isInitialized) {
        updateStatus('Please wait for Praat to initialize', true);
        return;
    }

    try {
        // Call Praat functions through ccall
        const result = PraatInstance.ccall(
            'praat_execute_command',
            'number',
            ['string'],
            [command]
        );

        if (result === 0) {
            updateStatus('Command executed successfully');
        } else {
            updateStatus('Command failed with code: ' + result, true);
        }
    } catch (error) {
        console.error('Command execution error:', error);
        updateStatus('Error executing command: ' + error.message, true);
    }
}

// Save file from virtual filesystem
function saveFile(virtualPath, downloadName) {
    if (!isInitialized) {
        updateStatus('Praat not initialized', true);
        return;
    }

    const FS = PraatInstance.FS;

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

        updateStatus(`File downloaded: ${a.download}`);
    } catch (error) {
        updateStatus(`Failed to save file: ${error.message}`, true);
    }
}

// List files in virtual filesystem
function listFiles(directory = '/uploads') {
    if (!isInitialized) {
        return [];
    }

    const FS = PraatInstance.FS;

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
        console.error('Failed to list files:', error);
        return [];
    }
}

// UI Helper functions
function updateStatus(message, isError = false) {
    const statusElement = document.getElementById('status');
    if (statusElement) {
        statusElement.textContent = message;
        statusElement.className = isError ? 'status error' : 'status success';
    }
    console.log(isError ? 'Error:' : 'Info:', message);
}

function appendOutput(text, isError = false) {
    const outputElement = document.getElementById('output');
    if (outputElement) {
        const line = document.createElement('div');
        line.className = isError ? 'output-line error' : 'output-line';
        line.textContent = text;
        outputElement.appendChild(line);
        outputElement.scrollTop = outputElement.scrollHeight;
    }
}

// Export functions for use in HTML
window.PraatInterface = {
    init: initPraat,
    uploadFile: handleFileUpload,
    executeCommand: executePraatCommand,
    saveFile: saveFile,
    listFiles: listFiles
};