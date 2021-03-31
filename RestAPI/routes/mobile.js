var express = require('express');
var router = express.Router();
var model = require('../models/mobile_model')

/* GET users listing. */
router.get('/', function(req, res, next) {
  res.send('respond with a resource');
});

module.exports = router;
