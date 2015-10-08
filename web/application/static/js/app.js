var app = angular.module('moisture', ['moisture.ctrls', 'ui.router'])

	.constant("socket", "http://127.0.0.1:5000")

   .config(function($stateProvider, $urlRouterProvider) {

   		$urlRouterProvider.otherwise("/dashboard");

    	$stateProvider
	    	.state('dashboard', {
	      		url: '/dashboard',
	      		templateUrl: 'static/templates/dashboard.html',
	      		controller: 'PumpCtrl'
	    })
   });