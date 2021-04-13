const express = require('express');
const router = express.Router();
const { model } = require('../models/customer_model');

router.get('/:customer_id', (req, res) => {
    model.get_info(req.params.customer_id,
        (err, db_result) => {
            if (err) res.json(err);
            else res.json(db_result[0]);
        }
    );
});

module.exports = router;
