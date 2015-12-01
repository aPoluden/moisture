angular.module('moisture.services', [])

.factory('arduino',['socket', '$http', function(socket, $http) {
	// Connection establishing through back - end
	return {
		turnOn : function() {
			return $http.put(socket + '/pump/on').then(function(response) {
	    		return response;
	    	}, function(response) {
	    		return response;
	    	});			
	    },
	    turnOff : function() {
	    	return $http.put(socket + '/pump/off').then(function(response) {
	    		return response;
	    	}, function(response) {
	    		return response;
	    	});
	    },
	    getStatus : function() {
	    	return $http.get(socket + "/pump/status").then(function(response) {
	    		return response;
	    	}, function(response) {
	    		return response;
	    	});
	    },
	    getTimeStamp: function() {
	    	var dt = new Date();
    		var ts = dt.toLocaleString()
	  		return ts;
		}
    };
}])
.factory('auth', ['$http','$q', 'socket', function($http, $q, socket) {
	return {
		userExists: function(user) {
			var deferred = $q.defer();
			var data = angular.toJson(user, false);
			return $http.post(socket + "/check", data).then(function(response) {
				// check if user exists
				deferred.resolve("Ok");
			}, function(error) {
				deffered.reject("Not ok");
			});
			return deferred.promise;
		}		
	}
}]);