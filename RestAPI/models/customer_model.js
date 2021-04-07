const { connection: db } = require('../database');

module.exports.model = {
    get_info: (customer_id, callback) => {
        return db.query(
            'select * from Asiakas where id=?',
            [customer_id],
            callback
        );
    }
}