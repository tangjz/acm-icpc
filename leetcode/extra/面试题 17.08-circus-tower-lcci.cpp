class Solution {
public:
    int bestSeqAtIndex(vector<int>& height, vector<int>& weight) {
        int n = height.size();
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            int dt = height[u] - height[v];
            return dt < 0 || (!dt && weight[u] > weight[v]);
        });
        vector<int> que;
        for(int u: ord) {
            int p = lower_bound(que.begin(), que.end(), weight[u]) - que.begin();
            if(p == que.size()) {
                que.push_back(weight[u]);
            } else {
                que[p] = weight[u];
            }
        }
        return que.size();
    }
};
