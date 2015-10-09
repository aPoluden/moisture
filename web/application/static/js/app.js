var app = angular.module('moisture', ['moisture.ctrls', 'ui.router'])

    .constant("socket", "http://127.0.0.1:5000")

    .config(function($stateProvider, $urlRouterProvider) {

   		$urlRouterProvider.otherwise("/login");

    	$stateProvider
    		.state('login', {
	    		url:'/login',
	    		templateUrl:'static/templates/login.html', 
	    		controller:'LoginCtrl'
	    	})
	    	.state('dashboard', {
	      		url: '/dashboard',
	      		templateUrl: 'static/templates/dashboard.html',
	      		controller: 'PumpCtrl'
	   		})
   	});