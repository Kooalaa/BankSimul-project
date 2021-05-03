const { connection: db } = require('../database');

module.exports.model = {
    get_ten_actions: (account_id, index, callback) => {
        db.query(
            'select * from Tili_tapahtumat where Tili_id=? order by Aika desc limit ?, 10',
            [account_id, index*10],
            callback
        );
    },

    add_action: (account_id, sum, callback) => {
        db.query(
            'insert into Tili_tapahtumat (Tili_id, Summa, Aika) values(?, ?, now())',
            [account_id, sum],
            callback
        );
    },

    get_actions_amount: (account_id, callback) => {
        db.query(
            'select count(id) as amount from Tili_tapahtumat where Tili_id=?',
            [account_id],
            callback
        );
    }
};
