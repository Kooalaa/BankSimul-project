const express = require('express');
const router = express.Router();
const { model } = require('../models/time_model');

router.get('/', (req, res) => {
    model.get_time_zones((err, db_result) => {
        if (err) res.json(err);
        else res.json(db_result);
    });
});

router.get('/now', (req, res) => {
    model.get_now((err, db_result) => {
        var date = new Date(db_result[0].now);
        var date_string = date.toLocaleString("EN-us", { timeZone: "Europe/Helsinki", hour12: false });
        var string_arr = date_string.split(/[/:]|(?:, )/);
        console.log(string_arr);
        var real_str = string_arr[2] + "-" + string_arr[0] + "-" + string_arr[1]
            + "T" + string_arr[3] + ":" + string_arr[4] + ":" + string_arr[5] + ".000Z";
        console.log(real_str);
        if (err) res.json(err);
        else res.json(db_result);
    });
});

module.exports = router;