# Based on example0.cc from player distribution
# Original Author: K. Nickels 7/24/13

# Import all of this for all entries
import sys, os, math
sys.path.append('/usr/local/lib64/python2.7/site-packages/')
from playercpp import *

# Create proxies for Client, Sonar, Tooth, Laser, Position2d
robot = PlayerClient("localhost");
sp = RangerProxy(robot,0);
tp = RangerProxy(robot,1);
lp = RangerProxy(robot,2);
pp = Position2dProxy(robot,0);

# Request Geometry
sp.RequestConfigure(); # fills up angle structures
tp.RequestConfigure();
lp.RequestConfigure();



# Read from the proxies
robot.Read()

# Request Geometry from the rest of the proxies
sonarstr="Sonar scan: "
for i in range(sp.GetRangeCount()):
	sonarstr += '%.3f ' % sp.GetRange(i)
print sonarstr

toothstr="Tooth scan: "
for i in range(tp.GetRangeCount()):
	toothstr += '%.3f ' % tp.GetRange(i)
print toothstr
	
laserstr="Laser scan: "	
for i in range(lp.GetRangeCount()):
	laserstr += '%.3f ' % lp.GetRange(i)
print laserstr

# Method 1
print "Sonar Ranges: "
for i in range(sp.GetRangeCount()):
	print str(sp.GetRange(i)) + ", " + str(sp.GetRange(sp.GetRangeCount()-1))

# Method 2, same
print "%d Sonar Ranges: " % sp.GetRangeCount()
for i in range(sp.GetRangeCount()):
	print str(sp.GetRange(i))+", "+str(sp.GetRange(sp.GetRangeCount()-1))

print "%d Laser Ranges: " % lp.GetRangeCount()
for i in range(lp.GetRangeCount()):
	print str(lp.GetRange(i)) + ", " + str(lp.GetRange(lp.GetRangeCount()-1))
