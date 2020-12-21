#!/bin/bash

g++ -o hc main.cpp
./hc
g++ -o hc nearestlandmark.cpp -l sqlite3 -ljsoncpp
./hc
g++ -o hc construction.cpp -l sqlite3
./hc
g++ -o hc module5.cpp -l sqlite3
./hc
