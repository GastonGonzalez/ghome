angular.module('SprinklerCtrl', []).controller('SprinklerController', function($scope, $http) {

    $scope.handleZone = function(zoneNum) {
	$http.get('/api/sprinklers/' + zoneNum)
	    .success(function(data) {
		console.log("Success!");
	    });
    };

    $http.get('/api/sprinklers').success(function(data) {
	$scope.zones = data.zones;
    });

    $scope.tagline = 'Sprinkler Automation';
});
