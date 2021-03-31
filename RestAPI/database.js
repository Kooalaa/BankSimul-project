import mysql from 'mysql';
const connection = mysql.createPool({
    host: 'localhost',
    user: 'project',
    password: 'project',
    database: 'BankSimulDB'
});
module.exports = connection;