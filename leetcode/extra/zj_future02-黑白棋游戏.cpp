class Solution {
public:
    int minSwaps(vector<int>& chess) {
        int n = chess.size();
        vector<int> psum = {0};
        for(int x: chess)
            psum.push_back(psum.back() + x);
        int m = psum.back(), ans = m;
        for(int i = m; i <= n; ++i) {
            ans = min(ans, m - (psum[i] - psum[i - m]));
        }
        return ans;
    }
};
