var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
var helmet = require('helmet');

var mobile_router = require('./routes/mobile');
var login_router = require('./routes/login');
var customer_router = require('./routes/customer');
var account_router = require('./routes/account');
var actions_router = require('./routes/actions');
var card_router = require('./routes/card');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));
app.use(helmet());


app.use('/mobile', mobile_router);
app.use('/login', login_router)
app.use('/customer', customer_router);
app.use('/account', account_router);
app.use('/actions', actions_router);
app.use('/card', card_router);


module.exports = app;
