angular.module('appRoutes', []).config(['$routeProvider', '$locationProvider', function($routeProvider, $locationProvider) {

	$routeProvider

		// home page
		.when('/', {
			templateUrl: 'views/home.html',
			controller: 'MainController'
		})

		.when('/sprinkler', {
			templateUrl: 'views/sprinkler.html',
			controller: 'SprinklerController'
		});

	$locationProvider.html5Mode(true);

}]);
