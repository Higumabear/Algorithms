def edit_distance(str1, str2):
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