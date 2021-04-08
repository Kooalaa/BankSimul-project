const express = require('express');
const router = express.Router();
const { model } = require('../models/login_model');

router.post('/', (req, res) => {
    console.log(req.body.hash); 
    var hash_buff = Buffer.from(req.body.hash, "base64");
    var hash = hash_buff.toString("hex");
    console.log(hash);
    model.login(hash, req.body.card_num,
        (err, db_result) => {
            if (err) res.json(err);
            else res.json(db_result[0]);
        }
    );
});

module.exports = router;
