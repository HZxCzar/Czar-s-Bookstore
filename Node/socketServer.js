
var http = require('http');
var fs = require('fs');
var spawn = require('child_process').spawn;
var path = require('path');
var childCwd = path.join(__dirname);
var child = spawn('/home/czar/Bookstore/code', [], { cwd: childCwd, encoding: 'utf8' });
var socketio = require('socket.io');

var server = http.createServer(function (request, response) {
    fs.readFile('HTMLPage.html', function (error, data) {
        response.writeHead(200, { 'Content-Type': 'text/html' });
        response.end(data);
    });
}).listen(52273, "0.0.0.0", function () {
    console.log('服务器监听地址在 http://127.0.0.1:52273');
    child = spawn('/home/czar/Bookstore/code', [], { cwd: childCwd, encoding: 'utf8' });
    console.log('子程序接入');
});

var io = socketio.listen(server);
io.sockets.on('connection', function (socket) {
    console.log('客户端已接入!');
    socket.on('clientData', function (data) {
        console.log('客户端发来的数据是:', data);
        child.stdin.write(data + '\n');
    });
    child.stdout.on('data', function (output) {
        console.log('result:', output.toString());
        socket.emit('serverData', output.toString());
    });
});