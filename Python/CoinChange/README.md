## README Project 2

## To use 
main.py {algo.py} {read_file.txt}
[algo.py]: This is the python file containing the algorithm to run.
The choices are:
			1) changeslow.py
			2) changegreedy.py
			3) changedp.py

[read_file.txt]: This is the TXT file of the set of arrays and amounts to be processed.
				 Note that the input arguments are in the order V[], A 

## Example use
`python main.py changedp.py Amount.txt`

## Note on changeslow.py
This implementation of changeslow.py will have a runtime dependent upon A, but also the
number of items are are in V[]. For reference, changeslow.py ran the array of 
V = [1, 5, 10, 25, 50] with A = 600 in about 11 seconds. However, if A was held at
600 and V was set such that V = [1, 2, 3, ... 598, 599], then changeslow could
take hours to run. Any value of A under 20 should be safe to run without
waiting too long.