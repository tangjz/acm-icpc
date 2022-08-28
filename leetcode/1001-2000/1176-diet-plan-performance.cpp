class Solution {
public:
    int dietPlanPerformance(vector<int>& seq, int k, int lower, int upper) {
        int n = seq.size();
        vector<int> psum = {0};
        for(int x: seq)
            psum.push_back(psum.back() + x);
        int ans = 0;
        for(int i = k; i <= n; ++i) {
            int val = psum[i] - psum[i - k];
            ans += (val > upper) - (val < lower);
        }
        return ans;
    }
};
