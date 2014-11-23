var express = require('express');
var http = require('http');
var router = express.Router();

var apis = [ 'sprinklers' ]; // available APIs

router.get('/', function(req, res) {
    var json = {};
    json.apis = apis;
    res.json(json);
});

router.route('/sprinklers')
   .get(function(serverReq, serverRes) {

	var proxyJson = {};
        http.get("http://192.168.1.50", function(res) {
	    console.log("Got response: " + res.statusCode);

	    res.on('data', function (chunk) {
		console.log('Sprinkler response: ' + chunk);
		proxyJson = JSON.parse(chunk);

		var json = {zones: []};
		for (i = 0; i < proxyJson.zones.length; i++) {
		    json['zones'].push({
			zone: proxyJson.zones[i].zoneNum,
			status: proxyJson.zones[i].zoneState === 1 ? 'on' : 'off'
		    });
		}
		serverRes.json(json);
	    });
	}).on('error', function(e) {
	    console.log("Got error: " + e.message);
	});


    });

router.route('/sprinklers/:zone_id')
   .get(function(serverReq, serverRes) {

        http.get("http://192.168.1.50?toggle=" + serverReq.params.zone_id, function(res) {
	    console.log("Got response: " + res.statusCode);
	    serverRes.json({});
	}).on('error', function(e) {
	    console.log("Got error: " + e.message);
	    serverRes.json({});
	});

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
