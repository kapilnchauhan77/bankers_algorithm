# Banker's Algorithm
## Meta data
* Name: Kapil Chauhan
* Assignment: Banker's Algorithm
* Date: 11/22/21
## Overview
* Banker's algorithm is a algorithm used to solve deadlock when there are multiple instance per resource type.
## Problems faced
* Inputting resource and process data.
* Keeping track of processes with their resource data.
* Cycle through processes (changing pointer to the beginning when needed).
* Defining a finish point where the algorithm stops finding a safety sequence.
## Solution
* Used csv format.
* Used Process Objects mapped into a System Object.
* Used pointers to solve this problem.
* Defined a runtime variable that limits number of tries in finding the safety sequence.
## How to use?
* Have a csv with data formatted as shown below.
![Data Format](https://github.com/kapilnchauhan77/bankers_algorithm/blob/master/data_format.png?raw=true)

* Use these commands to start the two processes in a linux shell.
```
clang++ bankers_algorithm.cpp -o bankers_algorithm
./bankers_algorithm filename.csv
```
## Example
* CSV
![DATA](https://github.com/kapilnchauhan77/bankers_algorithm/blob/master/data.png?raw=true)

* Program
![Program](https://github.com/kapilnchauhan77/bankers_algorithm/blob/master/program.png?raw=true)
