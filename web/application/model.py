def enum(**enums):
	return type('Enum', (), enums)

condition = enum(ON='Pump turned on', OFF='Pump turned off', CHECK='Check Pump status')

class Pump():
	
	working = False

	def status(self):
		if self.working is False:
			return condition.OFF
		else:
			return condition.ON

pump = Pump()