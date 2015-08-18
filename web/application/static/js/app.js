var app = angular.module('moistureApp', []);

app.controller('pumpController', ['$scope', function($scope) {

	$scope.turnOn = function() {
		// Turn pump On
		console.log("Turned On");
	}

	$scope.turnOff = function() {
		console.log("Turned off");
		// Turn pump Off	 
	}
    
    $scope.status = function() {
    	console.log("Status");
    	// Get pump status 
    }

}]);