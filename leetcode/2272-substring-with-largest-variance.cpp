class Solution {
    int calc(vector<int> &lft, vector<int> &rht) {
        vector<int> seq, psum = {0};
        for(auto it = lft.begin(), jt = rht.begin(); it != lft.end() || jt != rht.end(); ) {
            if(jt == rht.end() || (it != lft.end() && *it < *jt)) {
                seq.push_back(1);
                psum.push_back(psum.back() + 1);
                ++it;
            } else {
                seq.push_back(-1);
                psum.push_back(psum.back() - 1);
                ++jt;
            }
        }
        int ans = 0, pre = INT_MAX, n = seq.size();
        for(int i = 0, j = 0; i < n; ++i) {
            if(seq[i] < 0)
                for( ; j <= i; ++j)
                    pre = min(pre, psum[j]);
            if(pre < INT_MAX)
                ans = max(ans, psum[i + 1] - pre);
        }
        return ans;
    }
public:
    int largestVariance(string s) {
        const int maxd = 26;
        vector<vector<int> > pos(maxd);
        for(int i = 0; i < (int)s.size(); ++i)
            pos[(int)(s[i] - 'a')].push_back(i);
        int ans = 0;
        for(int i = 0; i < maxd; ++i)
            for(int j = 0; j < maxd; ++j)
                if(i != j && !pos[i].empty() && !pos[j].empty())
                    ans = max(ans, calc(pos[i], pos[j]));
        return ans;
    }
};
