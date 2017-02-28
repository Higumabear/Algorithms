#Algorithms
##introduction
勉強の過程で実装したアルゴリズムを置いています。  
[PKU Online Judge](http://poj.org)で使用することを想定しているためC++98準拠になっています🙏  
一部未検証なものが入っています。   

##データ構造
* [[C++]](/data_structure/union_find.cpp) Union-Find
* [[C++]](/data_structure/fenwick_tree.cpp) Fenwick tree
* [[C++]](/data_structure/leftist_heap.cpp) Leftist heap
* [[C++]](/data_structure/range_minimum_query.cpp) RMQ


##整列  

##文字列  
####検索
#####単一パターン照合
* [[C++]](string/z_algorithm.cpp) Zアルゴリズム
* [[C++]](string/rabin_karp.cpp) ラビン・カープ法 (Rabin-Karp)

##グラフ

####最短経路問題  
#####単一始点最短経路問題
* [[C++]](/graph/dijkstra.cpp) ダイクストラ法 (Dijkstra)
* [[C++]](/graph/bellman_ford.cpp) ベルマン・フォード法 (Bellman-Ford)

####全域木問題  
#####最小全域木
* [[C++]](/graph/kruscal.cpp) クラスカル法 (Kruscal)
* [[C++]](/graph/prim.cpp) プリム法 (Prim)

####強連結成分分解
* [[C++]](/graph/scc_kosaraju.cpp) Kosaraju
* [[C++]](/graph/scc_tarjan.cpp) Tarjan
* [[C++]](/graph/scc_gabow.cpp) Gabow

####ネットワーク流
#####最大流
* [[C++]](/graph/network/ford_fulkerson.cpp) フォード・ファルカーソン法 (Ford-Fulkerson)
* [[C++]](/graph/network/edmonds_karp.cpp) エドモンズ・カープ法 (Edmonds-Karp)
* [[C++]](/graph/network/capacity_scaling.cpp) 容量スケーリング法 (capacity scaling)
* [[C++]](/graph/network/dinic.cpp) Dinic <font size="-1">← Verifyしたけど正しい動作なのか不安😔</font>
* [[C++]](/graph/network/goldberg_tarjan.cpp) (naive) Goldberg-Tarjan

##### マッチング
* [[C++]](/graph/network/bipartite_matching.cpp) 二部マッチング (Ford-Fulkerson)
* [[C++]](/graph/network/bipartite_matching_hopcroft_karp.cpp) 二部マッチング (Hopcroft-Karp)

#####最小費用流
* [[C++]](/graph/network/minimum_cost_flow.cpp) Primal-Dual

####その他
* [[C++]](/graph/topological_sort.cpp)トポロジカルソート

##numerics  
