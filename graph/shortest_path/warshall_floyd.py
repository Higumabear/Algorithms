def warshall_floyd(dist):
    n = len(dist)
    for i in range(n):
        dist[i][i] = 0
    
    for k in range(n):
        for i in range(n):
            for j in range(n):
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

    return dist


node = [
    [100000, 4, 100000, 100000, 3],   
    [100000, 100000, 2, 100000, 100000],
    [100000, 100000, 100000, 3, 100000],
    [100000, 100000, 100000, 100000, 100000],
    [100000, 100000, 2, 7, 100000]
];

d = warshall_floyd(node)

print d[4][0]
