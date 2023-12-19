class Solution {
public:
    vector<int> countVisitedNodes(vector<int>& edges) {
        int n = edges.size();
        vector<int> tim(n, -1), sz(n), que;
        for(int i = 0, j, k; i < n; ++i) {
            if(tim[i] != -1)
                continue;
            que.clear();
            for(j = i; tim[j] == -1; que.push_back(j), tim[j] = i, j = edges[j]);
            if(tim[j] == i) {
                for(k = que.size() - 1; k >= 0 && que[k] != j; --k);
                sz[j = que.back()] = que.size() - k;
                que.pop_back();
                for( ; que.size() > k; sz[que.back()] = sz[j], j = que.back(), que.pop_back());
                for( ; !que.empty(); sz[que.back()] = sz[j] + 1, j = que.back(), que.pop_back());
            } else {
                for( ; !que.empty(); sz[que.back()] = sz[j] + 1, j = que.back(), que.pop_back());
            }
        }
        return sz;
    }
};
