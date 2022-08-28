class Solution {
public:
    int characterReplacement(string s, int k) {
        int n = s.size(), ans = 0;
        unordered_map<char, vector<int> > pos;
        for(int i = 0; i < n; ++i)
            pos[s[i]].push_back(i);
        for(auto &it: pos) {
            auto &vec = it.second;
            int m = vec.size();
            for(int i = 0, j = 0; i < m; ++i) {
                for(j = max(j - 1, i); j < m; ++j) {
                    int adt = vec[j] - vec[i] - (j - i);
                    if(adt > k)
                        break;
                    adt += i > 0 ? vec[i] - vec[i - 1] - 1 : vec[i];
                    adt += j + 1 < m ? vec[j + 1] - vec[j] - 1 : n - 1 - vec[j];
                    ans = max(ans, j - i + 1 + min(adt, k));
                }
            }
        }
        return ans;
    }
};
