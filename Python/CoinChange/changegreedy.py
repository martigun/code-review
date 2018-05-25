def changegreedy(arr, val):
	m = 0
	coinArr = [0 for i in arr] #init array
	i = len(arr) - 1
	while(val > 0):
		if(arr[i] <= val):
			val -= arr[i]
			coinArr[i] += 1
			m += 1
		else:
			i -= 1
	return [coinArr, m]
	

