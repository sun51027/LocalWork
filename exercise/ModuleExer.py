#########################
#	python exercise
#	lecture 1-3
#	function module
#########################
# import YourModule
import math 
print math.log(10)
print math.log10(10)
x=10
F=math.sin(x-math.pi/2.)**2
print F
y=2*math.pi
Euler = complex(math.cos(y),math.sin(y))
print Euler


import os	
# os : provide functions for interacting with the operating system
print os.getcwd() #print current directory
# module.XXXX : like class in c++...

import sys
for arg in sys.argv:
	print('hello',arg)
import random
print random.choice(['A','B','C'])
print random.random()

import printfib
