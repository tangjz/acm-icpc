class Solution {
public:
    int sumDistance(vector<int>& nums, string s, int d) {
        typedef long long LL;
        int n = s.size();
        vector<LL> pos;
        for(int i = 0; i < n; ++i)
            pos.push_back((LL)nums[i] + (s[i] == 'L' ? -d : d));
        sort(pos.begin(), pos.end());
        static const int mod = (int)1e9 + 7;
        LL ans = 0, sum = 0;
        for(int i = 0; i < n; ++i) {
            (ans += pos[i] * i - sum) %= mod;
            (sum += pos[i]) %= mod;
        }
        ans < 0 && (ans += mod);
        return ans;
    }
};
