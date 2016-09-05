def edit_distance(str1, str2):
<<<<<<< HEAD
    L = len(str1)
    M = len(str2)
    dp = [[0 for x in range(L)] for y in range(M)]

    for i in range(L):
        for j in range(M):
            if(i == 0 or j == 0):
                dp[i][j] = max(i, j)
            else:
                dp[i + 1][j + 1] = min(dp[i][j + 1] + 1, dp[i + 1][j] + 1, dp[i][j] + 1)
=======
	N = len(str1)
	M = len(str2)
	dp = [[0 for i in range(M + 1)] for j in range(N + 1)]
	
	for i in range(N + 1):
		dp[i][0] = i
	for j in range(M + 1):
		dp[0][j] = j
		
	for i in range(1, N + 1):
		for j in range(1, M + 1):
			if str1[i - 1] == str2[j - 1]:
				x = 0
			else:
				x = 1
			dp[i][j] = min(dp[i - 1][j] + 1,dp[i][j - 1] + 1, dp[i - 1][j - 1] + x)
			
	return dp[-1][-1]
>>>>>>> 17a22e498a59eee1894a3144c6d80de52d98cc4d
