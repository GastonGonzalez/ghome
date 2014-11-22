var express = require('express');
var router = express.Router();

var apis = [ 'sprinklers' ]; // available APIs

router.get('/', function(req, res) {
    var json = {};
    json.apis = apis;
    res.json(json);
});

router.route('/sprinklers')
   .get(function(req, res) {
    var json = {zones: []};
    for (i = 0; i < 3; i++) {
	json['zones'].push({
	    zone: i,
            location: 'front',
	    status: 'on'
	});
    }
    res.json(json);
    });

router.route('/sprinklers/:zone_id')
   .get(function(req, res) {
	var json = {
	    zone: req.params.zone_id,
            location: 'front',
	    status: 'on'
	}
	res.json(json);
    });

router.route('/sprinklers/:zone_id/:zone_state')
   .get(function(req, res) {
	var json = {
	    zone: req.params.zone_id,
            location: 'front',
	    status: req.params.zone_state
	}
	res.json(json);
    });
module.exports = router;
