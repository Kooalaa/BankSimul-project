const {connection: db} = require('../database');

module.exports.model = {
    login: (hash, card_num, callback) => {
        return db.query(
            'select Asiakas_id, Tili_id, id from Kortti where Pin=? and Kortinnumero=?',
            [hash, card_num],
            callback
        );
    }
}
