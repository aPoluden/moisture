import MySQLdb as mdb

con = mdb.connect(host = '193.219.42.49', port = 3036, user = 'artiom', passwd = 'password', db = 'moisture')

def dbStatus():
	con.query("SELECT VERSION()")
	result = con.use_result()
	return result.fetch_row()[0]