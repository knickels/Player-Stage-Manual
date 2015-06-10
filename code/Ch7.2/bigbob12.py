# Python client example.
# Shows simulation proxy interfaces

# To execute:
# > player bigbob11.cfg (in one terminal window)
# > python bigbob12.py (in another terminal window)
# 
# Original author: K. Nickels 6/10/15

import sys, os, math
sys.path.append('/usr/local/lib64/python2.7/site-packages/')
from playercpp import *

robot = PlayerClient("localhost")
p2dProxy = Position2dProxy(robot)
sp = SimulationProxy(robot)

# Read from the proxies
robot.Read()

# Print out stuff for fun
print sp
print p2dProxy


# command the motors
p2dProxy.SetSpeed(0.1,0.1); # XSpeed (m/s), YawSpeed (rad/s)
robot.Read()

# You must have patched
# client_libs/libplayerc++/bindings/python/playercpp.i as described in 
#  http://sourceforge.net/p/playerstage/mailman/message/33377207/
# (and recompiled and reinstalled player)
# For this pointer magic to work.
px = new_doublePtr()
py = new_doublePtr()
pa = new_doublePtr()

sp.GetPose2d("puck1",px,py,pa)
x = doublePtr_value(px)
y = doublePtr_value(py)
a = doublePtr_value(pa)
print "Puck1 is at Pose = ",x,", ",y,", ",a

sp.GetPose2d("puck3",px,py,pa);
x = doublePtr_value(px)
y = doublePtr_value(py)
a = doublePtr_value(pa)
print "Puck3 is at Pose = ",x,", ",y,", ",a

sp.SetPose2d("puck1",4,5,0);
robot.Read();
x = doublePtr_value(px)
y = doublePtr_value(py)
a = doublePtr_value(pa)
sp.GetPose2d("puck1",px,py,pa);
print "Puck1 is now at Pose = ",x,", ",y,", ",a

for i in range(5):
	robot.Read()
	sp.GetPose2d("bob1",px,py,pa)
	x = doublePtr_value(px)
	y = doublePtr_value(py)
	a = doublePtr_value(pa)
	print "bob1 Pose = %.2f, %.2f, %.2f" % (x,y,a)

# Stop
p2dProxy.SetSpeed(0,0)
