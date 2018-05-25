#!/usr/bin/env python

def changeslow(denomArray, targetAmt):
	
	#init bestArray as targetAmt
	bestArray = [targetAmt]
	bestCoinCount = targetAmt
	
	#get number of possible combinations and fill valArray
	totalCombos = 1; valArray = []
	for i in range(1, len(denomArray)):
		
		#store current value and append a zero to bestArray
		valArray.append(totalCombos)
		bestArray.append(0)
		
		#increase value for next "digit"
		totalCombos = totalCombos * (targetAmt / denomArray[i] + 1)

	#loop through each possibility
	for j in range(0, totalCombos):
		
		#get the array, using the ID=j
		coinArray = idToArray(j, valArray)
		v0 = 0;	coinCount = 0
		
		#get the total for this coin combo
		data = getTotal(coinArray, denomArray)
		total = data[0]
		
		#if total for this combo is not over the target
		if total <= targetAmt:
		
			#set v0 (which always = 1) to the
			# targetAmt less the current total
			v0 = (targetAmt - total)
			
			#set the total equal to the current total plus
			# the amount for v0, so that total = targetAmt
			total = total + v0
			
			#get coinCount from the getTotal function
			coinCount = data[1] + v0
			
			#insert the count for v0 into the
			# current coinArray
			coinArray.insert(0,v0)
			
			#if the current coinCount is best then
			# save the count and the array
			if coinCount < bestCoinCount:
				bestArray = coinArray
				bestCoinCount = coinCount
	
	#return the best count and array
	return [bestArray, bestCoinCount]
	
#converts an integer to an array based on values
def idToArray(dividend, valArray):
	
	#init currArray
	currArray = []

	#cycle backward thru valArray
	for i in range(len(valArray)-1,-1,-1):
	
		#insert quotient into currArray
		currArray.insert(0,(dividend / valArray[i]))
		
		#set dividend to remainder
		dividend = (dividend % valArray[i])
		
	#return currArray
	return currArray
	
#gets the total value of coins (and coinCount) for this array
# excluding v0, which always=1
def getTotal(coinArray, denomArray):
	
	#init total and coinCount
	total = 0; coinCount = 0
	
	#cycle thru each member and keep total and
	# skip v0, since we know v0=1
	for i in range(1, len(denomArray)):
		total += coinArray[i-1] * denomArray[i]
		coinCount += coinArray[i-1]
	
	#return the total value and coinCount
	return [total, coinCount]


