# Simple python client example 
# Based on example0.cc from player distribution
# K. Nickels 7/24/13

import math, sys, os
sys.path.append('/usr/local/lib64/python2.7/site-packages/')
from playercpp import *

# Make proxies for Client, blobfinder
robot = PlayerClient("localhost");
bf = BlobfinderProxy(robot,0);

# Read from the proxies
robot.Read();


# Print stuff out for fun
for i in range(bf.GetCount()):
	blob = bf.GetBlob(i);
	print 'BLOB %d, ' % i
        # Can't seem to access .color .x .y .top .left .right .bottom from
        # python.  
		# blob is a pointer to a C structure playerc_blob_t
		# Probably a SWIG problem...

	robot.Read()
