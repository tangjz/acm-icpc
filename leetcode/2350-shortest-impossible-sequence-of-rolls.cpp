class Solution {
public:
    int shortestSequence(vector<int>& rolls, int k) {
        int n = rolls.size();
        if(k == 1)
            return n + 1;
        vector<vector<int> > pos(k + 1);
        for(int i = 0; i < n; ++i)
            pos[rolls[i]].push_back(i);
        queue<pair<int, int> > que;
        que.push({0, -1});
        while(!que.empty()) {
            int len, idx;
            tie(len, idx) = que.front();
            que.pop();
            int best = -1;
            for(int i = 1; i <= k; ++i) {
                auto it = lower_bound(pos[i].begin(), pos[i].end(), idx + 1);
                if(it == pos[i].end())
                    return len + 1;
                best = max(best, *it);
            }
            que.push({len + 1, best});
        }
        return -1;
    }
};
