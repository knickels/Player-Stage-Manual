# Simple python client example 
# Based on example0.cc from player distribution
# K. Nickels 7/24/13

import math, sys, os
sys.path.append('/usr/local/lib64/python2.7/site-packages/')
from playerc import *

# Make proxies for Client, blobfinder
robot = playerc_client(None, 'localhost', 6665)
bf = playerc_blobfinder(robot,0);
if bf.subscribe(PLAYERC_OPEN_MODE):
	raise playerc_error_str()

for i in range(bf.GetCount()):
	robot.Read()
	blob = bf.GetBlob(i);
	print 'BLOB %d, ' % i
        # Can't seem to access .color .x .y .top .left .right .bottom from
        # python.  
		# blob is a pointer to a C structure playerc_blob_t
		# Probably a SWIG problem...

