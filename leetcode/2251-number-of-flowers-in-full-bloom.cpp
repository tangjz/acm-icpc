class Solution {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& A, vector<int>& B) {
        int n = A.size();
        vector<int> pos;
        pos.reserve(n + n);
        for(auto &it: A) {
            pos.push_back(it[0]);
            pos.push_back(it[1] + 1);
        }
        sort(pos.begin(), pos.end());
        pos.erase(unique(pos.begin(), pos.end()), pos.end());
        int m = pos.size();
        vector<int> ctr(m);
        for(auto &it: A) {
            int L = lower_bound(pos.begin(), pos.end(), it[0]) - pos.begin();
            int R = lower_bound(pos.begin(), pos.end(), it[1] + 1) - pos.begin();
            ++ctr[L];
            --ctr[R];
        }
        for(int i = 1; i < m; ++i)
            ctr[i] += ctr[i - 1];
        vector<int> ans;
        ans.reserve(B.size());
        for(int x: B) {
            int p = upper_bound(pos.begin(), pos.end(), x) - pos.begin() - 1;
            ans.push_back(p < 0 || p >= m ? 0 : ctr[p]);
        }
        return ans;
    }
};
