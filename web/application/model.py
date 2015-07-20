class Pump():
	
	working = False
	
	def status(self):
		if self.working is False:
			return 'Pump turned off'
		else:
			return 'Pump turned on'

pump = Pump()