const { json } = require('express');
const express = require('express');
const router = express.Router();
const { model } = require('../models/login_model');

router.post('/', (req, res) => {
    console.log(req.body.hash);
    var hash_buff = Buffer.from(req.body.hash, "base64");
    var hash = hash_buff.toString("hex");
    console.log(hash);
    model.login(req.body.card_num,
        (err, db_result) => {
            if (err) res.json(err);
            else if (db_result[0].Lukossa == 1) {
                var ret = {
                    status: -1,
                    ids: {},
                    attempts_left: 0
                };

                res.json(ret);
            } else {
                if (db_result[0].Pin == hash) {
                    var ret = {
                        status: 1,
                        ids: {
                            card_id: db_result[0].id,
                            customer_id: db_result[0].Asiakas_id,
                            account_id: db_result[0].Tili_id
                        },
                        attempts_left: 3
                    };
                    model.success(db_result[0].id, (err, db_result) => {
                        if (err) res.json(err);
                        else res.json(ret);
                    });

                } else {
                    var attempts = db_result[0].Väärä_pin - 1;
                    var ret = {
                        status: 0,
                        ids: {},
                        attempts_left: attempts
                    };

                    if (attempts == 0) model.lock_card(db_result[0].id, (err, db_result) => {
                        if (err) res.json(err);
                        else {
                            ret.status = -1;
                            res.json(ret);
                        }
                    });
                    else model.wrong_pin(db_result[0].id, attempts, (err, db_result) => {
                        if (err) res.json(err);
                        else res.json(ret);
                    });

                }
            }
        }
    );
});

module.exports = router;
