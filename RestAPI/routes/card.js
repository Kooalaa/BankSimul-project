const express = require('express');
const router = express.Router();
const { model } = require('../models/card_model');

router.get('/:card_num', (req, res) => {
    model.get_info(req.params.card_num,
        (err, db_result) => {
            if (err) res.json(err);
            else res.json(db_result[0]);
        }
    );
});

module.exports = router;
