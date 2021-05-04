const express = require('express');
const router = express.Router();
const { mobile } = require('../models/mobile_model');
const { randomBytes } = require('crypto');
const base64url = require('base64url');
const { Subject } = require('rxjs');

/**
 * MySql error codes
 * 
 * @constant error
 */
const error = {
    ER_DUP_ENTRY: 1062
};

/**
 * Status is used for syncing login request with mobiles reponse request.
 * 
 * @constant status
 */
const status = new Subject();

/**
 * Request hndler for geting new token for mobile login
 */
router.get('/atm', async (_req, res) => {
    var token = base64url(randomBytes(32));
    do {
        var result = new Promise((resolve, reject) => {
            console.log(token);
            mobile.add_atm(token,
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
            token = base64url(randomBytes(32));
        });
    } while (retry);
});

/**
 * Request handler for geting atm_token status.
 */
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

/**
 * Request handler for login in to account
 */
router.get('/login/:atm_token', (req, res) => {
    if (!req.params.atm_token) res.status(400).json({ error: "No atm token", status: 400 });
    mobile.get_status(req.params.atm_token,
        (err, db_result) => {
            console.log(db_result);
            if (err) res.json(err);
            else if (!db_result[0]) res.status(404).json({ error: "No such atm token" });
            else {

                var ret = {
                    status: 0,
                    ids: {},
                    card_num: ""
                };

                /**
                 * Remove pending request if timeout is reached.
                 * 
                 * @constant timeout
                 */
                const timeout = setTimeout((res) => {
                    res.status(504).json({
                        error: "Didnt get response",
                        status: 504
                    });

                    mobile.remove_atm(req.params.atm_token, (err, db_result) => {
                        if (err) console.log(err);
                        else console.log(db_result);
                    });

                    subscription.unsubscribe();
                }, 15000, res);

                /**
                 * Subscription to wait for geting response from mobile client or cancellation request from atm
                 * 
                 * @constant subscription
                 */
                const subscription = status.subscribe({
                    next: (atm_token) => {
                        console.log(atm_token);
                        //Check witch token should react to this.
                        if (atm_token.token != req.params.atm_token) return;
                        //Check if this is cancel request.
                        else if (atm_token.status == "CANCEL") {
                            res.json(ret);
                            subscription.unsubscribe();
                            clearTimeout(timeout);
                            return;
                        }

                        mobile.get_status(req.params.atm_token, (err, db_result) => {
                            if (err) res.json(err);
                            else if (!db_result[0]) res.json({ error: "Status not found" });
                            else {
                                if (!db_result[0].Login) res.json(ret);
                                else mobile.login(db_result[0].Kortti_id,
                                    (err, db_result) => {
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
                                    }
                                );
                                mobile.remove_atm(req.params.atm_token, (err, db_result) => {
                                    if (err) console.log(err);
                                    else console.log(db_result);
                                });
                            }
                            subscription.unsubscribe();
                            clearTimeout(timeout);
                        });
                    }
                });
            }
        }
    );
});

/**
 * Mobile response to login request.
 */
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
                    status.next({
                        token: req.body.atm_token,
                        status: "CONTINUE"
                    });
                }
            );
        }
    );
});

/**
 * Login cancel request.
 * Cancels the pending login request for the given tokne
 */
router.delete('/cancel/:atm_token', (req, res) => {
    console.log(req.params);
    mobile.remove_atm(req.params.atm_token,
        (err, db_result) => {
            if (err) res.json(err);
            if (db_result) {
                status.next({
                    token: req.params.atm_token,
                    status: "CANCEL"
                });
                res.json(db_result);
            }
        }
    );
});

/**
 * Removes mobile identification token from the given account
 */
router.delete('/:card_id', (req, res) => {
    mobile.delete_identification(req.params.card_id,
        (err, db_result) => {
            if (err) res.json(err);
            else res.json(db_result[0]);
        }
    );
});


router.put('/token/:card_id', (req, res) => {
    mobile.get_identificaton(req.params.card_id, (err, db_result) => {
        if (err) res.json(err);
        if (db_result[0]) {
            var ret_token = { token: db_result[0].Mobiili_varmenne };
            if (ret_token.token != null)
                res.json(ret_token);
            else {
                generate_token(req, res);
            }
        }
    });
});

router.put('/new_token/:card_id', (req, res) => {
    generate_token(req, res);
});

async function generate_token(req, res) {
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
            if (err.errno != error.ER_DUP_ENTRY) {
                console.error(err);
                res.json({
                    error: "Unknown error",
                    err
                });
                return;
            }
            retry = true;
            token = base64url(randomBytes(64));
        });
    } while (retry);
}

module.exports = router;
