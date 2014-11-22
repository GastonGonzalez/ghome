// modules =================================================
var express        = require('express');
var app            = express();
var bodyParser     = require('body-parser');
var methodOverride = require('method-override');
var api = require('./app/api-routes'); // back-end routes

// configuration ===========================================
	
var port = process.env.PORT || 8080; // set our port

// get all data/stuff of the body (POST) parameters
app.use(bodyParser.json()); // parse application/json 
app.use(bodyParser.json({ type: 'application/vnd.api+json' })); // parse application/vnd.api+json as json
app.use(bodyParser.urlencoded({ extended: true })); // parse application/x-www-form-urlencoded

app.use(methodOverride('X-HTTP-Method-Override')); // override with the X-HTTP-Method-Override header in the request. simulate DELETE/PUT
app.use(express.static(__dirname + '/public')); // set the static files location /public/img will be /img for users

app.use(function(req, res, next) {
    // do logging
    console.log('GHome request received.');
    next(); // make sure we go to the next routes and don't stop here
});

app.use('/api', api); // back-end routes
require('./app/app-routes')(app); // fron-end routes

// start app ===============================================
app.listen(port);	
console.log('GHome started on port ' + port);
exports = module.exports = app; // expose app
