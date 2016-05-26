var fs = require('fs');
var npas = require("./index.js");


var test = npas();

fs.readFile("da.wav", function(err,data) {
    var blocks = Math.floor(data.length/1024);
    for( var i=0; i < blocks; i++ ) {
        test.write(data.slice(1024*i, 1024));
    }
});
