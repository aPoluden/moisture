def enum(**enums):
	return type('Enum', (), enums)

condition = enum(ON='Pump turned on', OFF='Pump turned off', CHECK='Check Pump status')