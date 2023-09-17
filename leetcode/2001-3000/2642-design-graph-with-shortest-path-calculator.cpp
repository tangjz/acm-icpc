const int INF = 0x3f3f3f3f;

class Graph {
    int sz;
    vector<vector<int> > dis;
public:
    Graph(int n, vector<vector<int>>& edges) {
        sz = n;
        dis.assign(n, vector<int>(n, INF));
        for(auto &it: edges) {
            int &v = dis[it[0]][it[1]];
            v = min(v, it[2]);
        }
        for(int i = 0; i < n; ++i)
            dis[i][i] = 0;
        for(int k = 0; k < n; ++k)
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < n; ++j)
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    }

    void addEdge(vector<int> edge) {
        auto &it = edge;
        for(int i = 0; i < sz; ++i)
            for(int j = 0; j < sz; ++j)
                dis[i][j] = min(dis[i][j], dis[i][it[0]] + it[2] + dis[it[1]][j]);
    }

    int shortestPath(int node1, int node2) {
        int &v = dis[node1][node2];
        return v < INF ? v : -1;
    }
};

/**
 * Your Graph object will be instantiated and called as such:
 * Graph* obj = new Graph(n, edges);
 * obj->addEdge(edge);
 * int param_2 = obj->shortestPath(node1,node2);
 */
