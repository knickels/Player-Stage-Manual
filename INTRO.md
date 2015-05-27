# Chapter 1 -  Introduction

Player/Stage is a robot simulation tool, it comprises of one program,
Player, which is a *Hardware Abstraction Layer*. That means that it
talks to the bits of hardware on the robot (like a claw or a camera) and
lets you control them with your code, meaning you don't need to worry about
how the various parts of the robot work. Stage is a plugin to Player which
listens to what Player is telling it to do and turns these instructions
into a simulation of your robot. It also simulates sensor data and sends
this to Player which in turn makes the sensor data available to your code.

A simulation then, is composed of three parts:
* Your code. This talks to Player.
* Player. This takes your code and sends instructions to a robot. From the robot it gets sensor data and sends it to your code.
* Stage. Stage interfaces with Player in the same way as a robot's hardware would. It receives instructions from Player and moves a simulated robot in a simulated world, it gets sensor data from the robot in the simulation and sends this to Player.

Together Player and Stage are called Player/Stage, and they make a simulation of your robots.

These instructions will be focussing on how to use Player/Stage to make a
simulation, but hopefully this will still be a useful resource for anyone
just using Player (which is the same thing but on a real robot, without any simulation software).

## 1.1 - A Note on Installing Player/Stage
Instructions on how to install Player/Stage onto your computer aren't really the focus of this document. It is very difficult though. If you're lucky the install will work first time but there are a lot of dependencies which may need installing. 
* For computers running Ubuntu there is a very good set of instructions
* here (including a script for downloading the many prerequisites):
* [http://www.control.aau.dk/~tb/wiki/index.php/Installing_Player_and_Stage_in_Ubuntu](http://www.control.aau.dk/~tb/wiki/index.php/Installing_Player_and_Stage_in_Ubuntu)
* For OSX users you might find the following install instructions useful:
[http://alanwinfield.blogspot.com/2009/07/installing-playerstage-on-os-x-with.html](http://alanwinfield.blogspot.com/2009/07/installing-playerstage-on-os-x-with.html)
* Alternatively, you could try the suggestions on the Player ``getting
* help'' page:
[http://playerstage.sourceforge.net/wiki/Getting_help](http://playerstage.sourceforge.net/wiki/Getting_help)

Even after it's installed, you may need to do some per-user setup on your
system.  For example, on our system, the following two lines (adapted as
needed to your particular system) need to be added to each user's
`$HOME/.bashrc` file (or to the system-wide one): ``` export
LD_LIBRARY_PATH=/usr/local/lib64:$LD_LIBRARY_PATH} export
PKG_CONFIG_PATH=/usr/local/lib64/pkgconfig:$PKG_CONFIG_PATH} ```

## 1.2 - A Note about TRY IT OUT sections 
There will be sections scattered throughout this tutorial labeled **TRY IT
OUT** that explain how to run examples. 
In these sections, you'll be given commands to type in a terminal window
(or bash shell).  They'll be shown prefixed with a carrot `>` and
typeset in monospace font. For example, 

> `> ls`

means to go to a terminal window and type the command given (`ls`), without
the `>` character, then hit return.

The first time, you'll need to download the [example
code](/archive/master.zip) which will contain the files. 

In many cases, you'll need two windows, since the first command (`player
configfile.cfg`) doesn't quit till player is done.

## 1.3 - TRY IT OUT
> If you haven't already, download the sample code from [here](/archive/master.zip) 

> Next, you'll need to extract the sample code.  To do this, open a
> terminal and cd to the directory where you put the file
> `tutorial_code.zip`, then extract using zip.  Yes, there are
> GUI-based ways to do this too.  I won't cover them here.

> `> cd $HOME` I'll assume that you put this directory in your home directory.  If not, just replace the commands given with the appropriate directory. 

> `> unzip $HOME/Downloads/Player-Stage-Manual-master.zip` (Again,
> your specific path may differ.)

> `> cd $HOME/Player-Stage-Manual-master/code` (From here on out, I'll
> just say \<source_code\> for brevity and generality.)

> `> ls` 

> At this point, you should see five directories, `Ch3 Ch4 Ch5.1 Ch5.2
> Ch5.3`, which contain the C++ code examples for the respective chapters, and
> one, `bitmaps`, that has pictures used in several different examples.


## 1.4 - TRY IT OUT
> First we will run a world and configuration file that comes bundled with Stage. In your bash shell navigate to the Stage/worlds folder, by default (in Linux at least) this is `/usr/local/share/stage/worlds`. Type the following commands to run the ``simple world'' that comes with Player/Stage: 
> * `> cd /usr/local/share/stage/worlds` 
> * `> player simple.cfg`
> Assuming Player/Stage is installed properly you should now have a window open which looks like the figure below.  Congratulations,you can now build Player/Stage simulations!
> ![The simple.cfg world after being run](https://github.com/NickelsLab/Player-Stage-Manual/blob/master/pics/simpleworld.png)

Up: [README](README.md)

Next: [The Basics](BASICS.md)
