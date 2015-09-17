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
	  		var now = new Date();
	  		var date = [ now.getMonth() + 1, now.getDate(), now.getFullYear() ];
	  		var time = [ now.getHours(), now.getMinutes(), now.getSeconds() ];
	  		var suffix = ( time[0] < 12 ) ? "AM" : "PM";

	  		time[0] = ( time[0] < 12 ) ? time[0] : time[0] - 12;
	  		time[0] = time[0] || 12;

			for ( var i = 1; i < 3; i++ ) {
			   	if ( time[i] < 10 ) {
			      time[i] = "0" + time[i];
			    }
			 }

	  		return date.join("/") + " " + time.join(":") + " " + suffix;
		}
    };
}]);