const { connection: db } = require('../database');

module.exports.model = {
    get_info: (card_id, callback) => {
        db.query(
            'select * from Kortti where id=?',
            [card_id],
            callback
        );
    }
}
