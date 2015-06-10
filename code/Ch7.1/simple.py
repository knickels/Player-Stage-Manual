import sys
import os

# Check with "locate playerc.py"
sys.path.append('/usr/local/lib64/python2.7/site-packages/')

import math
from playerc import *

# Create a client object
c = playerc_client(None, 'localhost', 6665)

# Connect it to the server
if c.connect() !=0:
	raise playerc_error_str()

# Create a proxy for position2d:0 device
p = playerc_position2d(c,0)
if p.subscribe(PLAYERC_OPEN_MODE) !=0:
	raise playerc_error_str()

# Make the robot spin!
p.set_cmd_vel(0.0, 0.0, 40.0 * math.pi / 180.0, 1)

for i in range(0,30):
# Wait for new data from server
	if c.read() == None:
		raise playerc_error_str()

# Print current robot pose

	print 'Robot pose: (%.3f,%.3f,%.3f)' % (p.px,p.py,p.pa)
	
# Now stop
p.set_cmd_vel(0.0, 0.0, 0.0, 1)

# Clean up (l.unsubcribe is for laser sensor)
p.unsubscribe()
c.disconnect()
