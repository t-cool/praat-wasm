#!/usr/bin/env python3
"""
Simple HTTP server for serving Praat WebAssembly application
with proper CORS and MIME type headers for WebAssembly files
"""

import http.server
import socketserver
import os
import sys
from pathlib import Path

import sys

PORT = int(sys.argv[1]) if len(sys.argv) > 1 else 8000

class WASMHTTPRequestHandler(http.server.SimpleHTTPRequestHandler):
    """Custom HTTP request handler with WASM MIME types and CORS headers"""

    def end_headers(self):
        # Add CORS headers for WebAssembly
        self.send_header('Cross-Origin-Embedder-Policy', 'require-corp')
        self.send_header('Cross-Origin-Opener-Policy', 'same-origin')
        self.send_header('Access-Control-Allow-Origin', '*')
        self.send_header('Access-Control-Allow-Methods', 'GET, POST, OPTIONS')
        self.send_header('Access-Control-Allow-Headers', 'Content-Type')
        super().end_headers()

    def guess_type(self, path):
        """Add WebAssembly MIME types"""
        mimetype = super().guess_type(path)
        if path.endswith('.wasm'):
            return 'application/wasm'
        elif path.endswith('.js'):
            return 'application/javascript'
        return mimetype

def main():
    """Start the web server"""
    # Serve from the current directory
    os.chdir(Path(__file__).parent)

    Handler = WASMHTTPRequestHandler

    print(f"Starting Praat WebAssembly server...")
    print(f"Server running at: http://localhost:{PORT}/")
    print(f"Press Ctrl+C to stop the server")

    with socketserver.TCPServer(("", PORT), Handler) as httpd:
        try:
            httpd.serve_forever()
        except KeyboardInterrupt:
            print("\nServer stopped.")
            sys.exit(0)

if __name__ == "__main__":
    main()
