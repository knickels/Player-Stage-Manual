# Simple python client example
# Based on example0.cc from player distribution
# Original author: K. Nickels 7/24/13
import sys, os, math
# This should be wherever "playercpp.py" is
sys.path.append('/usr/local/lib64/python2.7/site-packages/')
from playercpp import *
# Define our ppstr and ppdstr, so that we may use it later
ppstr= '';
ppdstr= '';

def dtor (deg):
	return deg*math.pi/180.0;

# read from the proxies
robot = PlayerClient("localhost");
pp = Position2dProxy(robot,0);
# for carlike robots
# p2dProxy.SetSpeed(0.1,0.1); # XSpeed (m/s), YawSpeed (rad/s)
pp.SetCarlike(0.2,dtor(3)); # XSpeed, Yaw (rad)
# for holonomic robots
# pp.SetSpeed(0.1,0.1,0.1); # XSpeed (m/s), YawSpeed (rad/s)

robot.Read()

for i in range(10):
	ppstr += '%.3f m/s, ' % pp.GetXSpeed()
	ppstr += '%.3f m/s, ' % pp.GetYSpeed()
	ppstr += '%.3f rad/s ' % pp.GetYawSpeed()
	print ppstr
	ppdstr+= '%.3f m, ' % pp.GetXPos()
	ppdstr+= '%.3f m, ' % pp.GetYPos()
	ppdstr+= '%.3f rad' % pp.GetYaw()
	print ppdstr
