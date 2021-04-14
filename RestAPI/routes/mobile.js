const express = require('express');
const router = express.Router();
const { mobile } = require('../models/mobile_model');

router.get('/:m_token', (req, res) => {
    mobile.get_card(req.params.m_token,
        (err, db_result) => {
            if (err) res.json(err);
            else res.json(db_result);
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
