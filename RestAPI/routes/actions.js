const express = require('express');
const router = express.Router();
const { model } = require('../models/actions_model');

router.get('/:account_id/:index', (req, res) => {
    model.get_ten_actions(req.params.account_id, req.params.index,
        (err, db_result) => {
            if (err) res.json(err);
            else res.json(db_result);
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
