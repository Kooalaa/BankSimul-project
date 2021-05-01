const { connection: db } = require('../database');


module.exports.mobile = {
    get_status: function (atm_token, callback) {
        return db.query(
            'select * from ATM_tokens where token=?',
            [atm_token],
            callback
        );
    },

    add_atm: (atm_token, callback) => {
        return db.query(
            'insert into ATM_tokens (token) values(?)',
            [atm_token],
            callback
        );
    },

    response_to_login: (atm_token, card_id, accept_status, callback) => {
        return db.query(
            'update ATM_tokens set Kortti_id=?, Login=? where token=?',
            [card_id, accept_status, atm_token],
            callback
        );
    },

    get_card_id: (mobile_identification, callback) => {
        return db.query(
            'select id from Kortti where Mobiili_varmenne=?',
            [mobile_identification],
            callback
        );
    },

    add_identification: function (mobile_identification, card_id, callback) {
        return db.query(
            'update Kortti set Mobiili_varmenne=? where id=?;',
            [mobile_identification, card_id],
            callback
        );
    },

    delete_identification: function (card_id, callback) {
        return db.query(
            'update Kortti set Mobiili_varmenne=NULL where id=?;',
            [card_id],
            callback
        );
    },

    get_identificaton: (card_id, callback) => {
        return db.query(
            'select Mobiili_varmenne from Kortti where id=?',
            [card_id],
            callback
        );
    },

    login: (card_id, callback) => {
        db.query(
            'select id, Asiakas_id, Tili_id, Kortinnumero from Kortti where id=?',
            [card_id],
            callback
        );
    },

    remove_atm: (atm_token, callback) => {
        return db.query(
            'delete from ATM_tokens where token=?',
            [atm_token],
            callback
        );
    }
};
