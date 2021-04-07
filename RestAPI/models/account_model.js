const { connection: db } = require('../database');

module.exports.model = {
    get_info: (account_id, callback) => {
        return db.query(
            'select * from Tili where id=?',
            [account_id],
            callback
        );
    },

    edit_saldo: (account_id, new_value, callback) => {
        return db.query(
            'update Tili set Saldo=? where id=?',
            [new_value, account_id],
            callback
        );
    }
}
