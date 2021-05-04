const { connection: db } = require('../database');

module.exports.model = {
    get_time_zones: (callback) => {
        return db.query(
            'select @@GLOBAL.time_zone, @@SESSION.time_zone',
            callback
        );
    },
    get_now: (callback) => {
        return db.query(
            'select now() as now',
            callback
        );
    }
};
