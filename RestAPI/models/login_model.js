const {connection: db} = require('../database');

module.exports.model = {
    login: (card_num, callback) => {
        return db.query(
            'select * from Kortti where Kortinnumero=?',
            [card_num],
            callback
        );
    },
    wrong_pin: (card_id, attempts,callback) => {
        return db.query(
            'update Kortti set Väärä_pin=? where id=?',
            [attempts, card_id],
            callback
        );
    },
    lock_card: (card_id, callback) => {
        return db.query(
            'update Kortti set Lukossa=1, Väärä_pin=0 where id=?',
            [card_id],
            callback
        );
    },
    success: (card_id, callback) => {
        return db.query(
            'update Kortti set Väärä_pin=3 where id=?',
            [card_id],
            callback
        );
    }
}
