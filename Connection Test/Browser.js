var WebSocketClient = require('websocket').client;
const readline = require("readline");
const rl =readline.createInterface({
    input: process.stdin,
    output: process.stdout,
});

var client = new WebSocketClient();

client.on('connectFailed', function(error) {
    console.log('Connect Error: ' + error.toString());
});

client.on('connect', function(connection) {
    console.log('WebSocket Client Connected');
    connection.on('error', function(error) {
        console.log("Connection Error: " + error.toString());
    });
    connection.on('close', function() {
        console.log('Connection Closed');
    });
    connection.on('message', function(message) {
        if (message.type === 'utf8') {
            console.log("FROM SERVER: \n" + message.utf8Data);
            //promptFile();
            sendCamView();
        }
    });
    
    function promptFile() {
        if (connection.connected) {
            rl.question("Enter File Number: ", function (answer) {
                connection.send(answer);
            });
            //setTimeout(sendMsg, 1000);
        }
    }

    function sendCamView() {
        const arr = '{"name":"John", "age":30, "cars":["Ford", "BMW", "Fiat"]}' ;
        const myJ = JSON.stringify(arr);
        /*for (let i = 0; i < arr.length; i++) {
            connection.send(arr[i]);
        }*/
        connection.send(myJ);
    }
    //sendMsg();
});

client.connect('ws://192.168.101.242:9000/');