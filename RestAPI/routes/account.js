const express = require('express');
const router = express.Router();
const { model } = require('../models/account_model');

router.get('/:account_id', (req, res) => {
    model.get_info(req.params.account_id,
        (err, db_result) => {
            if (err) res.json(err);
            else res.json(db_result[0]);
        }
    );
});

router.put('/', (req, res) => {
    console.log(req.body);
    model.edit_saldo(req.body.account_id, req.body.new_balance,
        (err, db_result) => {
            if (err) res.json(err);
            else res.json(db_result);
        }
    );
});

module.exports = router;
