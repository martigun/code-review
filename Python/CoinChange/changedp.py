def changedp(coinDenominations, valueOfChange):
	#set up array to hold minimum coins for each value
    minimumNumberOfCoins = [None for x in range(valueOfChange + 1)]
    minimumNumberOfCoins[0] = []

    for i in range(1, valueOfChange + 1):
        for coin in coinDenominations:
            if coin > i: continue
            elif not minimumNumberOfCoins[i] or len(minimumNumberOfCoins[i - coin]) + 1 < len(minimumNumberOfCoins[i]):
                if minimumNumberOfCoins[i - coin] != None:
                    minimumNumberOfCoins[i] = minimumNumberOfCoins[i - coin][:]
                    minimumNumberOfCoins[i].append(coin)
    #print(len(minimumNumberOfCoins[-1]))

    minimumCoinSolution = [0]*len(coinDenominations)
    for c in minimumNumberOfCoins[-1]:
    	minimumCoinSolution[coinDenominations.index(c)] += 1

    #print(minimumCoinSolution)

    return [minimumCoinSolution, len(minimumNumberOfCoins[-1])]