# bigbob.inc
# model for the robot "Bigbob"
# Author: Jennifer Owen
# Date: 16/04/2010

#Bigbob's sonars
define bigbobs_sonars ranger
(
      # number of sonars
      scount 4

      # define the pose of each transducer [xpos ypos heading]
      spose[0] [ 0.75 0.1875 0]	#fr left tooth
      spose[1] [ 0.75 -0.1875 0]	#fr right tooth
      spose[2] [ 0.25 0.5 30]		# left corner
      spose[3] [ 0.25 -0.5 -30]	# right corner
		
      # define the field of view of each transducer 
      #[range_min range_max view_angle]
      sview [0.3 2.0 10]

      # define the size of each transducer
      # [xsize ysize] in meters
      ssize [0.01 0.05]
)

# bigbob's blobfinder
define bigbobs_eyes blobfinder
(
	# number of colours to look for
	colors_count 2

	# which colours to look for
	colors ["orange" "DarkBlue"]

	# camera parameters
	image [160 120]		#resolution
      range 5.00
      fov 1.047196667	# 60 degrees = pi/3 radians
)

# bigbob's laser
define bigbobs_laser laser
(
      # distance between teeth in metres
      range_max 0.25
	
      # does not need to be big
      fov 20
      
      #number of ranges measured
      samples 180
	
      pose [0.625 0.125 -0.975 270]
      size [0.025 0.025 0.025]
)


# bigbob's body
define bigbob position
(
      # actual size
      size [1.25 1 1]

      # Bigbob's centre of rotation is offset from its centre of area
    #  origin [0.125 0 0 0]

      # the shape of Bigbob
 
	block
	(
		points 6
		point[5] [0 0]
		point[4] [0 1]
		point[3] [0.75 1]
		point[2] [1 0.75]
		point[1] [1 0.25]
		point[0] [0.75 0]
		z [0 1]
	)

	block
	(
		points 4
		point[3] [1 0.75]
		point[2] [1.25 0.75]
		point[1] [1.25 0.625]
		point[0] [1 0.625]
		z [0 0.5]
	)

	block
	(
		points 4
		point[3] [1 0.375]
		point[2] [1.25 0.375]
		point[1] [1.25 0.25]
		point[0] [1 0.25]
		z [0 0.5]
	)
  

	
      # differential steering model
      drive "diff"

	
	# sensors attached to bigbob
	bigbobs_sonars()  
	bigbobs_eyes()
	bigbobs_laser()
	
	obstacle_return 1           	# Can hit things.
	laser_return 1                 # reflects laser beams
	ranger_return 1             	# reflects sonar beams
	blob_return 1               	# Seen by blobfinders  
) 



