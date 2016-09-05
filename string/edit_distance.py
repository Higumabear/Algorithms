def edit_distance(str1, str2):
    L = len(str1)
    M = len(str2)
    dp = [[0 for x in range(L)] for y in range(M)]

    for i in range(L):
        for j in range(M):
            if(i == 0 or j == 0):
                dp[i][j] = max(i, j)
            else:
                dp[i + 1][j + 1] = min(dp[i][j + 1] + 1, dp[i + 1][j] + 1, dp[i][j] + 1)
