import MySQLdb as mdb
import sys

try:
    con = mdb.connect(host = '193.219.42.49', port = 3036, user = 'artiom', passwd = 'password', db = 'moisture')
    cur = con.cursor()
except mdb.Error, e:
    print "Error %d: %s" % (e.args[0],e.args[1])
    sys.exit(1)

def dbStatus():
    cur.execute("SELECT VERSION()")
    ver = cur.fetchone()
    return ver

def insertValues(timestamp, value):
    try:
        query = """INSERT INTO data (post_date, value) VALUES ('%s','%s')""" % (timestamp, value)
        cur.execute(query)
        con.commit()
    except mdb.Error, e:
        print "Error %d: %s" % (e.args[0],e.args[1])
        sys.exit(1)