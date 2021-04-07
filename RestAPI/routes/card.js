const express = require('express');
const router = express.Router();
const { model } = require('../models/card_model');

router.get('/:id', (req, res) => {
    model.get_info(req.params.id,
        (err, db_result) => {
            if (err) res.json(err);
            else res.json(db_result[0]);
        }
    );
});

module.exports = router;
