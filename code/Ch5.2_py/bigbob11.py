# Simple python client example.
# Shows gripper and how it works.

# To run, complie this program.
# execute:
# > player bigbob4.cfg (in one terminal window)
# > ./ex_gripper (in another terminal window)

# Original author: K. Nickels 7/24/13

import sys, os, math
sys.path.append('/usr/local/lib64/python2.7/site-packages/')
from playercpp import *

def gripper_state (state): 
    return {
        1: 'open',
        2: 'closed',
        3: 'moving',
        4: 'error',
        }.get(state,'unknown')


# Make proxies for Client, Gripper, and Position2d
robot = PlayerClient("localhost");
gp = GripperProxy(robot,0);
pp = Position2dProxy(robot,0)

# Keep going till you see something
while(not gp.GetBeams()):
# Read from the proxies
	robot.Read()
# Print out stuff for fun
	print "Gripper is " + gripper_state(gp.GetState())
# Go forward
        pp.SetSpeed(0.1,0.0)
        
# Once robot sees block, stop and close gripper
while(gp.GetBeams() != 0 and gp.GetBeams() != 2):
        pp.SetSpeed(0.0,0.0)
        gp.Close()
        robot.Read()
	print "Gripper is " + gripper_state(gp.GetState())
	print "GetBeams() is " + str(gp.GetBeams())
# Now, gripper is closed.

# Back off with block in gripper
pp.SetSpeed(-0.1,0.0)
for i in range(20):
	robot.Read()
	print "Gripper is " + gripper_state(gp.GetState())

# Stop
pp.SetSpeed(0,0)
