angular.module('moisture.services', [])

.factory('arduino', function() {
	// Connection establishing through back - end
	return {
		turnOn : function turnOn() {
			console.log("turnOn");
	    },
	    turnOff : function turnOff() { 
	    	console.log("turnOff");
	    },
	    status : function status() {
	    	console.log("Status"); 
	    }
    };
});