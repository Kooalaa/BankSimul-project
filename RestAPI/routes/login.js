const express = require('express');
const router = express.Router();
const { model } = require('../models/login_model');

router.post('/', (req, res) => {
    model.login(req.body.hash, req.body.card_num,
        (err, db_result) => {
            if (err) res.json(err);
            else res.json(db_result[0]);
        }
    );
});

module.exports = router;