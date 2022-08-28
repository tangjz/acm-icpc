class Solution {
public:
    int uniqueLetterString(string s) {
        int n = s.size(), ans = 0;
        unordered_map<char, vector<int> > Hash;
        for(int i = 0; i < n; ++i)
            Hash[s[i]].push_back(i);
        for(auto &it: Hash) {
            auto &vec = it.second;
            int m = vec.size();
            for(int i = 0; i < m; ++i) {
                int L = i ? vec[i - 1] : -1, M = vec[i], R = i + 1 < m ? vec[i + 1] : n;
                ans += (M - L) * (R - M);
            }
        }
        return ans;
    }
};
