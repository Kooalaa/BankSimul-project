const express = require('express');
const router = express.Router();
const { mobile } = require('../models/mobile_model');
const { randomBytes } = require('crypto');
const base64url = require('base64url');
const { Subject } = require('rxjs');


const error = {
    ER_DUP_ENTRY: 1062
};

const status = new Subject();

router.get('/atm', async (_req, res) => {
    var token = base64url(randomBytes(32));
    do {
        var result = new Promise((resolve, reject) => {
            console.log(token);
            mobile.add_atm(token,
                (err, db_result) => {
                    if (err) reject(err);
                    else resolve(db_result);

                    /*res.json({
                        db: db_result,
                        token: token
                    });*/
                }
            );
        });

        var retry = 0;
        await result.then((db_result) => {
            res.json({
                db: db_result,
                token: token
            });
        }).catch((err) => {
            if (err.errno != error.ER_DUP_ENTRY) return;
            retry = true;
            token = base64url(randomBytes(32));
        });
    } while (retry);
});

router.get('/mobile/:atm_token?', (req, res) => {
    if (req.params.atm_token) {
        mobile.get_status(req.params.atm_token,
            (err, db_result) => {
                console.log(db_result);
                if (err) res.json(err);
                else if (!db_result[0]) res.status(404).json({ error: "No such atm token" });
                else res.json(db_result[0]);
            }
        );
        return;
    }
    res.status(404).json({ error: "No atm token provided" });
});

router.get('/login/:atm_token', (req, res) => {
    if(!req.params.atm_token) res.status(400).json({error: "No atm token", status: 400});
    var ret = {
        status: 0,
        ids: {},
        card_num: ""
    };
    
    const timeout = setTimeout((res) => {
        res.status(504).json({
            error: "Didnt get response",
            status: 504
        });
        subscription.unsubscribe();
    }, 15000, res);
    
    var subscription = status.subscribe({
        next: (atm_token) => {
            if (atm_token != req.params.atm_token) return;
            mobile.get_status(req.params.atm_token, (err, db_result) => {
                if (err) res.json(err);
                else if (!db_result[0]) res.json({ error: "Status not found" });
                else {
                    if (!db_result[0].Login) res.json(ret);
                    else mobile.login(db_result[0].Kortti_id, (err, db_result) => {
                        if (err) res.json(err);
                        else {
                            ret = {
                                status: 1,
                                ids: {
                                    card_id: db_result[0].id,
                                    customer_id: db_result[0].Asiakas_id,
                                    account_id: db_result[0].Tili_id
                                },
                                card_num: db_result[0].Kortinnumero
                            };
                            res.json(ret);
                        }
                    });
                }
                subscription.unsubscribe();
                clearTimeout(timeout);
            });
        }
    });

});

router.get('/:atm_token', (req, res) => {
    mobile.get_status(req.params.atm_token,
        (err, db_result) => {
            if (err) res.json(err);
            else res.json(db_result[0]);
        }
    );
});

router.post('/mobile', (req, res) => {
    console.log(req.body);
    mobile.get_card_id(req.body.mobile_identification,
        (err, db_result) => {
            console.log(db_result[0]);
            if (err) res.json(err);
            else if (!db_result[0]) res.status(404).json({ error: "No such token" });
            else mobile.response_to_login(req.body.atm_token, db_result[0].id, req.body.accept_status,
                (err, db_result) => {
                    if (err) res.json(err);
                    else res.json(db_result);
                    status.next(req.body.atm_token);
                }
            );
        }
    );
});


router.put('/:card_id', async (req, res) => {
    var token = base64url(randomBytes(64));
    do {
        var result = new Promise((resolve, reject) => {
            console.log(token);
            mobile.add_identification(token, req.params.card_id,
                (err, db_result) => {
                    if (err) reject(err);
                    else resolve(db_result);
                }
            );
        });

        var retry = 0;
        await result.then((db_result) => {
            res.json({
                db: db_result,
                token: token
            });
        }).catch((err) => {
            if (err.errno != error.ER_DUP_ENTRY) return;
            retry = true;
            token = base64url(randomBytes(64));
        });
    } while (retry);
});

module.exports = router;
