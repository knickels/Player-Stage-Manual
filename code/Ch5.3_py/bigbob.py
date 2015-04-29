# Desc: Bigbob code for controlling a junk finding robot.
# Author: Jennifer Owen
# Date: 16/04/2010
# Updates (Stage4) Kevin Nickels 7 Aug 2013

import sys, os, math
sys.path.append('/usr/local/lib64/python2.6/site-packages/')
import playercpp from *
import random
# create a class:
class Item:
	def __init__(self):
		name=[]
		x=0
		y=0

robot = PlayerClient("localhost");
# Left sonar
lp = RangerProxy(robot,0);
# Right sonar
rp = RangerProxy(robot,0);
sp = RangerProxy(robot,0);
pp = Position2dProxy(roboty,0);

# Randomly assigns new speeds into the given addresses.
# This function will always write to the given addresses.
# @param *forwardSpeed the address of the forward speed variable you want this function to change.
# @param *turnSpeed the address of the turn speed vairable you want this function to change.

def Wander(forwardSpeed,turnSpeed):
	maxSpeed=1
	maxTurn=90
	fspeed,tspeed
# fspeed is between 0 and 10
	fspeed=random.uniform(0,10)%11
#(fspeed/10) is between 0 and 1
	fspeed = (fspeed/10)*maxSpeed

	tspeed=random.uniform(0,10)%(2*maxTurn)
	tspeed=tspeed-maxTurn

	*forwardSpeed = fspeed
	*turnsSpeed = tspeed

# Checks sonars for obstacles and updates the given addresses with wheel speeds.
# This function will write to the addresses only if there is an obstacle present.
# Very basic obstacle avoidance only.
# @param *forwardSpeed the address of the forward speed variable you want this function to change.
# @param *turnSpeed the address of the turn speed variable you want this function to change.
# @param &sp the sonar proxy that you want this function to moniter.

def AvoidObstacles(*forwardSpeed,*turnSpeed,\RangerProxy &sp)
# will avoid obstacles closer than 40cm
	avoidDistance = 0.4
# will turn away at 60 degrees/sec
	avoidTurnSpeed = 60

# left corner is sonar no. 2
# right corner is sonar no. 3
	if (sp[2] < avoidDistance)
{
		*forwardSpeed=0
# turn right
		*turnSpeed = (-1)*avoidTurnSpeed
	print("\navoiding obstacle\n")
}
	else if (sp[3] < avoidDistance)
{
		*forwardSpeed = 0
# turn left
		*turnSpeed=avoidTurnSpeed
	print("\navoiding obstacle\n")
}
	else if( (sp[0] < avoidDistance) && (sp[1] < avoidDistance))
{
# back off a little bit
		*forwardSpeed = -0.2
		*turnSpeed = avoidTurnSpeed
		print("\navoiding obstacle\n")
}

# If blobs have been detected this function will turn the robot towards the largest blob. This will be the cosest blob (hopefully!). If called this function will always overwrite information in the given addresses.
