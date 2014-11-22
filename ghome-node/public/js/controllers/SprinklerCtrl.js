angular.module('SprinklerCtrl', []).controller('SprinklerController', function($scope, $http) {

    $http.get('/api/sprinklers').success(function(data) {
	$scope.zones = data.zones;
    });

    $scope.tagline = 'Sprinkler Automation';
});
