##############################
# hung.makefile
# Author: Jonathon Zeitler
#
# makes: hung
# use: make -f hung.makefile
##############################

hung : hung.cpp
	g++ -std=c++11 -Wall hung.cpp -o hung

