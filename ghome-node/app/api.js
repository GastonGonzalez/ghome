var express = require('express');
var router = express.Router();

router.get('/', function(req, res) {
    var json = {};
    res.json(json);
});

module.exports = router;
