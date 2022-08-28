class Solution {
public:
    int maxRepOpt1(string text) {
        int n = text.size();
        unordered_map<char, vector<int> > pos;
        for(int i = 0; i < n; ++i)
            pos[text[i]].push_back(i);
        int ans = 0;
        for(auto &it: pos) {
            auto &vec = it.second;
            int m = vec.size();
            auto check = [&](int L, int R) {
                if(L == 0 && R == m - 1)
                    return vec[R] - vec[L] == R - L;
                return vec[R] - vec[L] <= R - L + 1;
            };
            for(int i = 0, j = 0; i < m; ++i) {
                for( ; j < m && check(i, j); ++j);
                ans = max(ans, j - i + !(!i && j == m));
            }
        }
        return ans;
    }
};
