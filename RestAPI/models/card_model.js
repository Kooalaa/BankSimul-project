const { connection: db } = require('../database');

module.exports.model = {
    get_info: (card_num, callback) => {
        db.query(
            'select Lukossa, Väärä_pin from Kortti where Kortinnumero=?',
            [card_num],
            callback
        );
    }
};
