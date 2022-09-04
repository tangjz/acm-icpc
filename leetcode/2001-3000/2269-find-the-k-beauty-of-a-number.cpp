class Solution {
public:
    int divisorSubstrings(int num, int k) {
        string buf = to_string(num);
        int ans = 0, n = buf.size();
        for(int i = 0; i <= n - k; ++i) {
            int val = stoi(buf.substr(i, k));
            ans += val > 0 && num % val == 0;
        }
        return ans;
    }
};
