# Chapter 4 - <a name="sec_ConfigurationFile"> Writing a Configuration (.cfg) File</a>

As mentioned earlier, Player is a hardware abstraction layer which connects
your code to the robot's hardware. It does this by acting as a
Server/Client type program where your code and the robot's sensors are
clients to a Player server which then passes the data and instructions
around to where it all needs to go. This stuff will be properly explained
in [Coding](CONTROLLERS.md#sec_Coding), it all sounds more complicated than
it is because Player/Stage takes care of all the difficult stuff. The
configuration file is needed in order to tell the Player server which
drivers to use and which interfaces the drivers will be using.

For each model in the simulation or device on the robot that you want to interact with, you will need to specify a driver. This is far easier than writing worldfile information, and follows the same general syntax. The driver specification is in the form:
```
driver
(
      name "driver_name"
      provides [device_address]
      # other parameters... 
)
```
The 'name' and 'provides' parameters are mandatory information, without
them Player won't know which driver to use (given by 'name') and what kind
of information is coming from the driver ('provides'). The 'name' parameter
is not arbitrary, it must be the name of one of Player's inbuilt drivers.
It is also possible to build your own drivers for a hardware device but
this document won't go into how to do this because it's not relevant to
Player/Stage. that have been written for Player to interact with a robot
device. A [list of supported driver names](http://playerstage.sourceforge.net/doc/Player-3.0.2/player/group__drivers.html)
is in the Player manual, although when using Stage the only one that is
needed is `"stage"`. 

The 'provides' parameter is a little more complicated than 'name'. It is
here that you tell Player what interface to use in order to interpret
information given out by the driver (often this is sensor information from
a robot), any information that a driver 'provides' can be used by your
code. For a Stage simulated robot the `"stage"` driver can provide the
interfaces to the sensors discussed in [Robot Sensors](WORLDFILES.md#sec_BuildingAWorld_BuildingRobot_RobotSensors).  Each interface shares
the same name as the sensor model, so for example a `ranger` model would
use the `ranger` interface to interact with Player and so on (the only
exception to this being the `position` model which uses the `position2d`
interface). 
The Player manual contains [a list of all the different interfaces that can be
used](http://playerstage.sourceforge.net/doc/Player-3.0.2/player/group__interfaces.html),
the most useful ones have already been mentioned in [Robot Sensors](WORLDFILES.md#sec_BuildingAWorld_BuildingRobot_RobotSensors), although there are others too numerable to list here.

The input to the 'provides' parameter is a "device address", which
specifies which TCP port an interface to a robot device can be found,
[Device Address](#sec_ConfigurationFile_DeviceAddress) has more information
about device addresses. This uses the `key:host:robot:interface:index` form
separated by white space.

```
provides ["key:host:robot:interface:index" 
          "key:host:robot:interface:index"
          "key:host:robot:interface:index"
          ...]
```

After the two mandatory parameters, the next most useful driver parameter
is `model`. This is only used if `"stage"` is the driver, it tells Player
which particular model in the worldfile is providing the interfaces for
this particular driver. A different driver is needed for each model that
you want to use.  Models that aren't required to do anything (such as a
map, or in the example of [Other Stuff](WORLDFILES.md#sec_BuildingAWorld_OtherStuff) oranges and boxes) don't need to have a driver written for them.

The remaining driver parameters are 'requires' and 'plugin'. The 'requires'
is used for drivers that need input information such as `"vfh"', it tells
this driver where to find this information and which interface it uses.
The 'requires' parameter uses the same `key:host:robot:interface:index`
syntax as the 'provides' parameter. Finally the `plugin` parameter is used
to tell Player where to find all the information about the driver being
used. 

Earlier we made a .cfg file in order to create a simulation of an empty (or at least unmoving) world, the .cfg file read as follows:
```
driver
(		
      name "stage"
      plugin "stageplugin"

      provides ["simulation:0" ]

      # load the named file into the simulator
      worldfile "empty.world"	
)
```
This has to be done at the beginning of the configuration file because it
tells Player that there is a driver called `"stage"` that we're going to
use and the code for dealing with this driver can be found in the
`stageplugin` plugin. This needs to be specified for Stage because Stage is
an add-on for Player, for drivers that are built into Player by default the
`plugin` doesn't need to be specified.

# <a name=sec_ConfigurationFile_DeviceAddress> Device Addresses </a>

A device address is used to tell Player where the driver you are making
will present (or receive) information and which interface to use in order
to read this information. This is a string in the form
`key:host:robot:interface:index` where each field is separated by a colon.

* `key`: The [Player manual](http://playerstage.sourceforge.net/doc/Player-3.0.2/player/group__tutorial__config.html\#device_addresses) states that: *"The purpose of the
key field is to allow a driver that supports multiple interfaces of the
same type to map those interfaces onto different devices"* 
This is a driver level thing and has a lot to do with the `name` of the
driver that you are using, generally for `"stage"` the `key` doesn't need
to be used. If you're using Player without Stage then there is a useful
section about device address keys in the [Player manual](http://playerstage.sourceforge.net/doc/Player-3.0.2/player/group__tutorial__config.html#device_key).
* `host`: This is the address of the host computer where the device is
located. With a robot it could be the IP address of the robot. The default
host is "localhost" which means the computer on which Player is running.
* `robot`: this is the TCP port through which Player should expect to receive data from the interface usually a single robot and all its necessary interfaces are assigned to one port. The default port used is 6665, if there were two robots in the simulation the ports could be 6665 and 6666 although there's no rule saying which number ports you can or can't use.
* `interface`: The interface to use in order to interact with the data. There is no default value for this option because it is a mandatory field.
* `index`: If a robot has multiple devices of the same type, for instance it has 2 cameras to give the robot depth perception, each device uses the same interface but gives slightly different information. The index field allows you to give a slightly different address to each device. So two cameras could be `camera:0` and `camera:1`. 
This is very different from the `key` field because having a "driver that supports multiple interfaces of the same type" is NOT the same as having multiple devices that use the same interface. Again there is no default index, as this is a mandatory field in the device address, but you should use 0 as the index if there is only one of that kind of device. 

If you want to use any of the default values it can just be left out of the
device address. So we could use the default host and robot port and specify
(for example) a laser interface just by doing `"ranger:0"`. 

However, if you want to specify fields at the beginning of the device
address but not in the middle then  the separating colons should remain.
For example if we had a host at `"127.0.0.1"` with a `ranger` interface
then we would specify the address as `"127.0.0.1::ranger:0"`, the robot
field is empty but the colons around it are still there. You may notice
that the key field here was left off as before.

# <a name=sec_ConfigurationFile_FinishingCFG> Putting the Configuration File Together </a>

We have examined the commands necessary to build a driver for a model in
the worldfile, now it is just a case of putting them all together. To
demonstrate this process we will build a configuration file for the
worldfile developed in [Building a World](WORLDFILES.md#sec_BuildingAWorld).
In this world we want our code to be able to interact with the robot, so in
our configuration file we need to specify a driver for this robot.
```
driver
(
      # parameters... 
)
```

The inbuilt driver that Player/Stage uses for simulations is called `"stage"` so the driver name is `"stage"`.
```
driver
(
      name "stage"
)
```

The Bigbob robot uses `position`, `blobfinder` and `ranger`
sensors. These correspond to the `position2d`, `blobfinder` and
`ranger` interfaces respectively. 

All range-finding sensors (i.e. sonar, laser, and IR sensors) are
represented by the ranger interface.  In Stage 4.1.1 there is only legacy
support for separate laser or IR interfaces.  All new development should
use rangers.
       
We want our code to be able to read from these sensors, so we need to
declare interfaces for them and tell Player where to find each device's
data, for this we use the configuration file's 'provides' parameter. This
requires that we construct device addresses for each sensor; to remind
ourselves, this is in the key:host:robot:interface:index format. We aren't
using any fancy drivers, so we don't need to specify a key. We are running
our robot in a simulation on the same computer as our Player sever, so the
host name is 'localhost' which is the default, so we also don't need to
specify a host. The robot is a TCP port to receive robot information over,
picking which port to use is pretty arbitrary but what usually happens is
that the first robot uses the default port 6665 and subsequent robots use
6666, 6667, 6668 etc. There is only one robot in our simulation so we will
use port 6665 for all our sensor information from this robot.  We only have
one sensor of each type, so our devices don't need separate indices. What
would happen if we did have several sensors of the same type (like say two
cameras) is that we put the first device at index 0 and subsequent devices
using the same interface have index 1, then 2, then 3 and so on.

There are lots of ranger sensors in our model but when we
created the robot's sensors in 
[Sensors and Devices](WORLDFILES.md#sec_BuildingAWorld_BuildingRobot_RobotSensorsDevices)

we put them all into two ranger models (one for all the sonars and one for
the one laser).  So as far as the configuration file is concerned there are
only two ranging devices, because all the separate sonar sensors are lumped
together into one device.  We don't need to declare each sonar device on an
index of its own.
}
Finally we use interfaces appropriate to the sensors the robot has, so in
our example these are the `position2d`, `blobfinder` interfaces
and for our sonar and laser devices we will use the `ranger`
interface.

Putting all this together under the `\provides\ parameter gives us:
```
driver
(
  name "stage"
  provides ["position2d:0" 
            "ranger:0" 
            "blobfinder:0" 
            "ranger:1" ]
)
```
The device addresses can be on the same line as each other or separate lines, just so long as they're separated by some form of white space.

The last thing to do on our driver is the `model "model_name"` parameter
which needs to be specified because we are using Player/Stage. This tells
the simulation software that anything you do with this driver will affect
the model `\"model_name"\ in the simulation. In the simulation we built we
named our robot model "bob1", so our final driver for the robot will be:
```
driver
(
      name "stage"
      provides ["position2d:0" 
            "ranger:0" 
            "blobfinder:0" 
            "ranger:1"]
      model "bob1" 
)
```
If our simulation had multiple Bigbob robots in it, the configuration file
drivers would be very similar to one another. If we created a second robot
in our worldfile and called it "bob2" then the driver would be:
```
driver
( 
      name "stage" 
      provides ["position2d:0" 
            "ranger:0" 
            "blobfinder:0" 
            "ranger:1"]
      model "bob2" 
)
```
Notice that the port number and model name are the only differences because the robots have all the same sensors.

A driver of this kind can be built for any model that is in the worldfile, not just the robots. For instance a map driver can be made which uses the `\map\ interface and will allow you to get size, origin and occupancy data about the map. The only requirement is that if you want to do something to the model with your code then you need to build a driver for it in the configuration file. Finally when we put the bit which declares the `\stage\ driver (this part is compulsory for any simulation configuration file) together with our drivers for the robot we end up with our final configuration file:
```
driver
(		
      name "stage"
      plugin "stageplugin"

      provides ["simulation:0" ]

      # load the named file into the simulator
      worldfile "worldfile_name.world"
)      

driver
(
      name "stage"
      provides ["position2d:0" 
            "ranger:0" 
            "blobfinder:0" 
            "ranger:1"]
      model "bob1" 
)
```

\tiobox{
{ \tt cd <source\_code>/Ch4} \\
{\tt > player bigbob8.cfg (in one terminal window)}\\
{\tt > playerv --position2d:0} \\(in another terminal window)\\
{\tt > playerv -p 6666 -position2d:0} \\(in yet another terminal window)

To drive the robots around, you select Devices/Position2d/Command in a
playerv window, then drag the red bulls-eye around.
}





* Up: [README](README.md)
* Prev: [Building a World](WORLDFILES.md)
* Next: [Getting Your Simulation to Run Your Code](CONTROLLERS.md)
