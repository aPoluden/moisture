angular.module('moisture.services', [])

.factory('arduino',['socket', '$http', function(socket, $http) {
	// Connection establishing through back - end
	return {
		turnOn : function() {
			$http.put(socket + '/pump/on').then(function(response) {
	    		console.log(response);
	    	}, function(response) {
	    		console.log(response);
	    	});			
	    },
	    turnOff : function() {
	    	$http.put(socket + '/pump/off').then(function(response) {
	    		console.log(response);
	    	}, function(response) {
	    		console.log(response);
	    	});
	    },
	    getStatus : function() {
	    	return $http.get(socket + "/pump/status").then(function(response) {
	    		return response.data;
	    	}, function(response){
	    		return response.status;
	    	});
	    }
    };
}]);