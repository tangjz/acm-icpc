class Solution {
public:
    int tupleSameProduct(vector<int>& a) {
        int n = (int)a.size();
        unordered_map<int, int> Hash;
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j) {
                ++Hash[a[i] * a[j]];
            }
        typedef long long LL;
        LL ans = 0;
        for(auto &it: Hash) {
            ans += it.second * (it.second - 1LL) / 2;
        }
        ans *= 8;
        return ans;
    }
};
