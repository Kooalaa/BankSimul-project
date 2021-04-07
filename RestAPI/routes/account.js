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

router.put('/:account_id', (req, res) => {
    model.edit_saldo(req.params.account_id, req.body.new_saldo,
        (err, db_result) => {
            if (err) res.json(err);
            else res.json(db_result);
        }
    );
});


module.exports = router;