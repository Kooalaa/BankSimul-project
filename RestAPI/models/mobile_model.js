const { connection: db } = require('../database');


module.exports.mobile = {
    get_card: function(mobile_identification, callback) {
        return db.query(
            'select * from Kortti where Mobiili_varmenne=?',
            [mobile_identification],
            callback
        );
    },

    add_identification: function(mobile_identification, card_id, callback) {
        return db.query(
            'update Kortti set Mobiili_varmenne=? where id=?;',
            [mobile_identification, card_id],
            callback
        );
    },
    
    delete_identification: function(card_id, callback) {
        return db.query(
            'update Kortti set Mobiili_varmenne=NULL where id=?;',
            [card_id],
            callback
        );
    }
};