/* Add npm dependencies */

var app  = require('express')()
   , server = require('http').createServer(app)
   , io = require('socket.io').listen(server);
var spawn = require('child_process').spawn;

/* reduce debug messages to level 1 */
io.set('log level', 1);  

/* Server setup */
server.listen(80);

/* sockets.io setup */
io.sockets.on('connection', function (socket) {
  
  socket.emit('conStatus', 'Connected Message');
  
  socket.on('triggerCPPDroneApp', function (data) {
      console.log("Fly Drone App");

      var child = spawn('./Build/BebopRebopAPI', '');

      child.stdout.on('data', function(chunk) {
	  console.log('Data from CPP');
          socket.emit('DroneStatus', chunk.toString('ascii'));
      });

      child.on('exit', function(code) {
	console.log('exit Cpp Program');
      });
  });
  
});

/* http portion of the server */
app.get('/', function (req, res) {
  res.sendfile(__dirname + '/index.html');
});


app.get('/socket.io.js', function(req, res){
	console.log("jquery js file call");
  res.sendfile(__dirname + '/socket.io.js');
});

console.log('End of Server nodejs DroneApp');
