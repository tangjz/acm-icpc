class Solution {
public:
    int similarPairs(vector<string>& words) {
        int ans = 0;
        unordered_map<int, int> ctr;
        for(auto &s: words) {
            int msk = 0;
            for(char ch: s)
                msk |= 1 << (ch - 'a');
            ans += ctr[msk]++;
        }
        return ans;
    }
};
