angular.module('moisture.ctrls', ['moisture.services'])

.controller('PumpCtrl', ['$scope', 'arduino', function($scope, arduino) {
	$scope.logs = [];
	$scope.timeStamps = [];
	$scope.turnOn = function() {
		arduino.turnOn().then(function(data) {
			$scope.logs.push({timeStamp : arduino.getTimeStamp(), data : data.data})
		});
	};

	$scope.turnOff = function() {
		arduino.turnOff().then(function(data) {
			$scope.logs.push({timeStamp : arduino.getTimeStamp(), data : data.data});
		});
	};
    
    $scope.getStatus = function() {
    	arduino.getStatus().then(function(data) {
    		$scope.logs.push({timeStamp : arduino.getTimeStamp(), data : data.data})
    	});
    };
}])
.controller('LoginCtrl', ['$scope', function($scope) {

}])