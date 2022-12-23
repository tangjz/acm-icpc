class Solution {
public:
    int countDistinctStrings(string s, int k) {
        const int mod = (int)1e9 + 7;
        int ans = 1;
        for(int i = s.size(); i >= k; --i)
            (ans <<= 1) >= mod && (ans -= mod);
        return ans;
    }
};
