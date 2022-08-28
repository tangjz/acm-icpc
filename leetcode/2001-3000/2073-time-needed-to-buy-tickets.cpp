class Solution {
public:
    int timeRequiredToBuy(vector<int>& seq, int k) {
        int ans = 0, n = seq.size();
        for(int i = 0; i < n; ++i) {
            ans += min(seq[i], seq[k] - (i > k));
        }
        return ans;
    }
};
