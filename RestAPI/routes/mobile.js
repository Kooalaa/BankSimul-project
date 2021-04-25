const { json } = require('express');
const express = require('express');
const router = express.Router();
const { mobile } = require('../models/mobile_model');
const { route } = require('./login');
const { randomBytes } = require('crypto')
const base64url = require('base64url');

var error = {
    ER_DUP_ENTRY: 1062
}

class ERROR {
    ERROR
    constructor(e) {
        this.ERROR = e
    }
}

router.get('/:atm_token', (req, res) => {
    mobile.get_status(req.params.atm_token,
        (err, db_result) => {
            if (err) res.json(err);
            else res.json(db_result[0]);
        }
    );
});

router.post('/atm', (req, res) => {
    var token = "xK_j9o_E7tODTv-TOYyWdX0q-U0-74QyTb0yjZt20jw"//base64url(randomBytes(32))
    do {
        var retry = false
        try {
            mobile.add_atm(token,
                (err, db_result) => {
                    if (err.errno == error.ER_DUP_ENTRY) throw new ERROR(err)
                    else if (err) res.json(err);
                    else res.json({
                        db: db_result,
                        token: token
                    });
                }
            )
        } catch (err) {
            if (err instanceof ERROR) {
                if (err.ERROR.errno == error.ER_DUP_ENTRY)
                    retry = true
                token = base64url(randomBytes(32))
            }
        }
    } while (retry == true)
});

router.get('/mobile/:atm_token?', (req, res) => {
    if (req.params.atm_token) {
        mobile.get_status(req.params.atm_token,
            (err, db_result) => {
                if (err) res.json(err);
                else if (!db_result[0]) res.status(404).json({ error: "No such atm token" });
                else res.json(db_result[0]);
            }
        );
    }
    else res.status(404).json({ error: "No atm token provided" })
});

router.post('/mobile', (req, res) => {
    console.log(req.body)
    mobile.get_card_id(req.body.mobile_identification,
        (err, db_result) => {
            console.log(db_result[0])
            if (err) res.json(err);
            else if (!db_result[0]) res.json({ error: "No such token" });
            else mobile.response_to_login(req.body.atm_token, db_result[0].id, req.body.accept_status,
                (err, db_result) => {
                    if (err) res.json(err);
                    else res.json(db_result);
                }
            );
        }
    );
});


router.put('/:card_id', (req, res) => {
    mobile.add_identification(req.body.m_token, req.params.card_id,
        (err, db_results) => {
            if (err) res.json(err)
            else res.json(db_results);
        }
    );
});

module.exports = router;
