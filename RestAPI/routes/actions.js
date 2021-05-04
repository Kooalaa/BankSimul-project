const express = require('express');
const router = express.Router();
const { model } = require('../models/actions_model');

/**
 * Formater is used to format date ``Date`` objects to string.
 * 
 * @constant formater
 */
const formater = new Intl.DateTimeFormat("en-EN", {
    timeZone: "Europe/Helsinki",
    hour12: false,
    year: "numeric",
    month: "2-digit",
    day: "2-digit",
    hour: "2-digit",
    minute: "2-digit",
    second: "2-digit"
});

router.get('/:account_id/:index', (req, res) => {
    model.get_ten_actions(req.params.account_id, req.params.index,
        (err, db_result) => {
            if (err) res.json(err);
            else {
                db_result.forEach(value => {
                    var date = new Date(value.Aika);
                    var date_str = formater.format(date);
                    var string_arr = date_str.split(/[/:]|(?:, )/);
                    value.Aika = string_arr[2] + "-" + string_arr[0] + "-" + string_arr[1]
                        + "T" + string_arr[3] + ":" + string_arr[4] + ":" + string_arr[5] + ".000Z";
                });
                res.json(db_result);
            }
        }
    );
});

router.get('/year/:account_id/:year', (req, res) => {
    var year = (parseInt(req.params.year) + 1).toString() + "-01-01";
    var last_year = (parseInt(req.params.year) -1).toString() + "-12-31";

    model.get_year(req.params.account_id, last_year, year,
        (err, db_result) => {
            if (err) res.json(err);
            else {
                db_result.forEach(value => {
                    var date = new Date(value.Aika);
                    var date_str = formater.format(date);
                    var string_arr = date_str.split(/[/:]|(?:, )/);
                    value.Aika = string_arr[2] + "-" + string_arr[0] + "-" + string_arr[1]
                        + "T" + string_arr[3] + ":" + string_arr[4] + ":" + string_arr[5] + ".000Z";
                });
                res.json(db_result);
            }
        }
    );
});

router.post('/', (req, res) => {
    model.add_action(req.body.account_id, req.body.sum,
        (err, db_result) => {
            if (err) res.json(err);
            else res.json(db_result);
        }
    );
});

router.get('/:account_id', (req, res) => {
    model.get_actions_amount(req.params.account_id,
        (err, db_result) => {
            if (err) res.json(err);
            else res.json(db_result[0]);
        }
    );
});

module.exports = router;
