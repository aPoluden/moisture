angular.module('moisture.ctrls', ['moisture.services'])

.controller('PumpCtrl', ['$scope', 'arduino', function($scope, arduino) {
	$scope.turnOn = function() {
		arduino.turnOn();
	};

	$scope.turnOff = function() {
		arduino.turnOff();
	};
    
    $scope.getStatus = function() {
    	var stat = arduino.getStatus();
    	console.log(stat);
    };
}])