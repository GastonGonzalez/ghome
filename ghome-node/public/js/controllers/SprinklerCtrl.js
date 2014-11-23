angular.module('SprinklerCtrl', []).controller('SprinklerController', function($rootScope, $scope, $http) {

    $scope.handleZone = function(zoneNum) {
	$http.get('/api/sprinklers/' + zoneNum)
	    .success(function(data) {
		console.log("Success!");
		$rootScope.$broadcast('updateZones');
	    });
    };

    $scope.$on("updateZones",function(zoneNum){
	$http.get('/api/sprinklers').success(function(data) {
	    $scope.zones = data.zones;
	});
    });

    $http.get('/api/sprinklers').success(function(data) {
	$scope.zones = data.zones;
    });

    $scope.tagline = 'Sprinkler Automation';
});
