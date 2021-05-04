var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
var helmet = require('helmet');

/**
 * Routers for express
 */
var mobile_router = require('./routes/mobile');
var login_router = require('./routes/login');
var customer_router = require('./routes/customer');
var account_router = require('./routes/account');
var actions_router = require('./routes/actions');
var card_router = require('./routes/card');
var time_router = require('./routes/time');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));
app.use(helmet());

/**
 * Add routers to the app
 */
app.use('/mobile', mobile_router);
app.use('/login', login_router);
app.use('/customer', customer_router);
app.use('/account', account_router);
app.use('/actions', actions_router);
app.use('/card', card_router);
app.use('/time', time_router);

module.exports = app;




/**
 * Https server
 */
 const { readFileSync } = require('fs');
 const { createServer } = require('https');
 
 const cert = {
     key: readFileSync('../../privkey.pem', "utf-8"),
     cert: readFileSync('../../fullchain.pem', 'utf-8')
 };
 
 var port = 8443;
 var https_server = createServer(cert, app);
 https_server.listen(port, () => {
     console.log("Listenning ...");
 });
 https_server.on("error", (err) => {
     console.log(err);
     if (err.syscall !== 'listen') {
         throw err;
     }
 
     var bind = typeof port === 'string'
         ? 'Pipe ' + port
         : 'Port ' + port;
 
     // handle specific listen errors with friendly messages
     switch (err.code) {
         case 'EACCES':
             console.error(bind + ' requires elevated privileges');
             process.exit(1);
             break;
         case 'EADDRINUSE':
             console.error(bind + ' is already in use');
             process.exit(1);
             break;
         default:
             throw err;
     }
 });
 
