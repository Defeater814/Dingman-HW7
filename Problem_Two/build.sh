#!/bin/bash
# This script builds an executable file for the myCopier.cpp file.

echo "Building executable file for myCopier.cpp..."
g++ -g myCopier.cpp -o myCopier
echo "Executable file created!"
