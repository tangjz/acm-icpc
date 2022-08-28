class Solution {
public:
    char slowestKey(vector<int>& seq, string buf) {
        int n = buf.size(), cost = seq[0];
        char ans = buf[0];
        for(int i = 1; i < n; ++i) {
            int tmp = seq[i] - seq[i - 1];
            tie(cost, ans) = max(make_pair(cost, ans), make_pair(tmp, buf[i]));
        }
        return ans;
    }
};
