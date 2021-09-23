var CONSOLE = false;

var PORT = 5005;
var HOST = '192.168.15.2';
var dictId = "eeg_dict";

var dgram = require('dgram');
var server = dgram.createSocket('udp4');

try {
  const maxApi = require("max-api");
}
catch (e) {
  if (e.code !== 'MODULE_NOT_FOUND') {
      throw e;
  }
  console.log("Not found Max")
  CONSOLE = true;
}

function print(text) {
  if(CONSOLE) console.log(text)
  else maxApi.post(text);
}

server.on('listening', function() {
  var address = server.address();
  print('UDP Server listening on ' + address.address + ':' + address.port);
});

server.on('message', function(message, remote) {
  var obj = JSON.parse(message);
  print(JSON.stringify(obj,null,2));
  if(!CONSOLE) maxApi.setDict(dictId, obj);
});

if(!CONSOLE) {
	maxApi.addHandler('dict', (...msg) => {
	  dictId = msg[0];
    maxApi.post("Dict name updated to: " + dictId);
	});
  maxApi.addHandler('ip', (...msg) => {
	  HOST = msg[0];
    maxApi.post("IP updated to: " + HOST);
	});
  maxApi.addHandler('port', (...msg) => {
	  PORT = msg[0];
    maxApi.post("PORT updated to: " + PORT);
	});
}

server.bind(PORT, HOST);
