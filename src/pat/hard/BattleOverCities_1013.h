//
// Created by guojm on 2021/2/20.
//

#ifndef ALGORITHM_BATTLEOVERCITIES_1013_H
#define ALGORITHM_BATTLEOVERCITIES_1013_H

/**
 * keywords: graph connectivity dfs
 * description:
 *      Remove a node from a undirected connected graph.
 *      And then,we need to add some edges to repair the connectivity of remaining nodes.
 *      Try get the minimum number of edges which should be added into the graph.
 */
namespace BattleOverCities_1013 {
    /**
     * key words: connected component dfs
     * when a node removed from a graph,the graph consist of remaining nodes can have more than one connected components
     * The most important point is how to repair connectivity of two connected components.
     * Obviously, we only need to add a any edge between two connected components;
     * For example:
     *      node 'a' is a arbitrary node belong to connected components A;
     *      node 'b' is a arbitrary node belong to connected components B;
     *      if we build a edge connecting a and b,the two components will be connected
     * So result is
     */
    namespace ConnectedComponents {
        #include <cstdio>

        using namespace std;

        bool **graph = nullptr;
        bool *visited = nullptr;
        int N, M, K, exclude;

        int detectComponents();

        void dfs(int);

        int main() {
            std::iostream::sync_with_stdio(false);
            cin.tie(nullptr);
            cin >> N >> M >> K;
            graph = new bool *[N + 1];
            for (int i = 1; i <= N; ++i) {
                graph[i] = new bool[N + 1]();
            }
            visited = new bool[N + 1]();
            int s, d;
            for (int i = 0; i < M; ++i) {
                cin >> s >> d;
                graph[s][d] = true;
                graph[d][s] = true;
            }
            for (int i = 0; i < K; ++i) {
                cin >> exclude;
                cout << detectComponents() - 1;
                if (i < K - 1) {
                    cout << "\n";
                }
            }
            return 0;
        }

        /**
         * @param exclude node excluded
         * @return amount of connected components
         */
        int detectComponents() {
            for (int i = 1; i <= N; ++i) {
                visited[i] = false;
            }
            int count = 0;
            for (int i = 1; i <= N; ++i) {
                if (!visited[i] && i != exclude) {
                    count++;
                    dfs(i);
                }
            }
            return count;
        }

        void dfs(int node) {
            if (node == exclude)
                return;
            for (int i = 1; i <= N; ++i) {
                if (graph[node][i] && !visited[i]) {
                    visited[i] = true;
                    dfs(i);
                }
            }
        }
    }
}


#endif //ALGORITHM_BATTLEOVERCITIES_1013_H
