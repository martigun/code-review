#!/usr/bin/env python
#
# CS325
# Spring 2016
# Project 2
# Group 6	
#
# Filename: main.py
# Usage: `main.py {algo.py} {read_file.txt}`
#
# Example: `python main.py changeslow.py coin.txt`
#
# [algo.py]: This is the python file containing the algorithm to run.
# The choices are:
#			1) changeslow.py
#			2) changegreedy.py
#			3) changedp.py
#
# [read_file.txt]: This is the TXT file of the set of arrays to be read in
# and processed.
#

#import libraries
import sys #for command line
import time #for timing execution

def run_coin_function(coin_function):

	#get TXT files to read and write results/runtimes
	read_file = open(sys.argv[2],'r')
	results_file = open(sys.argv[2].split('.')[0]+'change.txt','a')
	runtime_file = open('run_times.txt','a')
	
	#initialize arrays for test_sets and read them in
	test_sets = []
	lineCount = 0
	for line in read_file:
		lineCount += 1
		line = eval(line)
		if lineCount % 2 == 0: #this is the amount we need to make change from
			amt = line
			test_sets.append([coinSet,amt])
		else:
			coinSet = line
			
	#write the header for the results file
	results_name = sys.argv[1].split('.')[0]+':'
	results_file.write('Results from algorithm ' + results_name + '\n')

	#write the header for the runtime file
	runtime_file.write('|set|A|ms|\n')
		
	#for each test set
	for i in range (0,len(test_sets)):
		
		#keep user updated
		print('Processing set: ' + str(i) + '...')
		
		#get start time
		start_time = time.time()
		
		#run function
		result = coin_function(test_sets[i][0],test_sets[i][1])
		
		#get elapsed time in milliseconds
		elapsed_ms = int((time.time() - start_time)*1000)
		
		#write runtime to runtime_file
		s = '|' + str(i) + '|' + str(test_sets[i][1])
		s += '|' + str(elapsed_ms) + '|'
		runtime_file.write(s + '\n')
		
		#write results to results_file
		results_file.write(str(result[0])) #writes array of coins
		results_file.write('\n')
		results_file.write(str(result[1])) #writes coin total
		results_file.write('\n')
	
	
	#message user
	print('Results appended to: '+sys.argv[2].split('.')[0]+'change.txt')
	print('Run-time statistics appended to: run_times.txt')
	print('---------------------------------------------')
	
#check cmd line arguments
if len(sys.argv)!=3:
	print('usage main.py {algo.py}{read_file.txt}')

else:
	#get the PY file, read file, write file
	py_file = sys.argv[1]
	
	#run function for each PY file
	if py_file == 'changeslow.py':
		print("Getting results using: " + py_file)
		execfile(py_file)
		run_coin_function(changeslow)
	elif py_file == 'changegreedy.py':
		print("Getting results using: " + py_file)
		execfile(py_file)
		run_coin_function(changegreedy)
	elif py_file == 'changedp.py':
		print("Getting results using: " + py_file)
		execfile(py_file)
		run_coin_function(changedp)