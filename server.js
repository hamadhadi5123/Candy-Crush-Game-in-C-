const http = require('http');
const fs = require('fs');
const path = require('path');
const { exec } = require('child_process');

const PORT = 3000;
const MIME_TYPES = {
    '.html': 'text/html',
    '.css': 'text/css',
    '.js': 'text/javascript',
    '.png': 'image/png',
    '.jpg': 'image/jpeg',
    '.jpeg': 'image/jpeg',
    '.ttf': 'font/ttf',
    '.otf': 'font/otf',
    '.txt': 'text/plain'
};

const server = http.createServer((req, res) => {
    let reqPath = req.url === '/' ? '/index.html' : decodeURIComponent(req.url);
    let filePath = path.join(__dirname, reqPath);

    fs.stat(filePath, (err, stats) => {
        if (err || !stats.isFile()) {
            res.writeHead(404, { 'Content-Type': 'text/plain' });
            res.end('File Not Found');
            return;
        }

        const ext = path.extname(filePath).toLowerCase();
        const contentType = MIME_TYPES[ext] || 'application/octet-stream';

        res.writeHead(200, { 'Content-Type': contentType });
        fs.createReadStream(filePath).pipe(res);
    });
});

server.listen(PORT, () => {
    const url = `http://localhost:${PORT}`;
    console.log(`\n========================================`);
    console.log(`  Candy Crush Game is running!`);
    console.log(`  URL: ${url}`);
    console.log(`========================================\n`);

    // Open in default browser
    exec(`start ${url}`);
});
