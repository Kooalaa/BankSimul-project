const mysql = require('mysql');
module.exports.connection = mysql.createPool({
    host: 'localhost',
    user: 'netuser',
    password: 'netuser',
    database: 'BankSimulDB'
});
