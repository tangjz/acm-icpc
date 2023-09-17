class Solution {
public:
    long long findMaximumElegance(vector<vector<int>>& items, int k) {
        typedef long long LL;
        int n = items.size(), m = 0;
        vector<vector<int> > seq(n);
        for(auto &it: items)
            seq[it[1] - 1].push_back(it[0]);
        for(int i = 0; i < n; ++i) {
            if(seq[i].empty())
                continue;
            sort(seq[i].begin(), seq[i].end());
            seq[m++].swap(seq[i]);
        }
        seq.resize(m);
        sort(seq.begin(), seq.end(), [&](auto const &u, auto const &v) {
            return u.back() < v.back();
        });
        LL ans = 0, tmp = 0;
        priority_queue<int> que;
        for(int i = 0; i < m && i < k; ++i) {
            auto &vec = seq.back();
            tmp += vec.back() + i * 2 + 1;
            vec.pop_back();
            for(int x: vec) {
                tmp += x;
                que.push(-x);
            }
            seq.pop_back();
            while(que.size() >= k - i) {
                tmp += que.top();
                que.pop();
            }
            ans = max(ans, tmp);
        }
        return ans;
    }
};
