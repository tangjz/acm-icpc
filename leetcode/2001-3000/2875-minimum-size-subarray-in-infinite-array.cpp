class Solution {
public:
    int minSizeSubarray(vector<int>& nums, int target) {
        typedef long long LL;
        int n = nums.size();
        vector<LL> psum = {0};
        for(int x: nums)
            psum.push_back(psum.back() + x);
        for(int x: nums)
            psum.push_back(psum.back() + x);
        int ans = INT_MAX;
        LL mod = psum.back() / 2, rem = target % mod;
        unordered_map<LL, int> pos;
        for(int i = 0; i < n + n; ++i) {
            pos[psum[i] % mod] = i;
            LL v = (psum[i + 1] - rem) % mod;
            v < 0 && (v += mod);
            auto it = pos.find(v);
            if(it == pos.end())
                continue;
            int j = it -> second;
            if(psum[i + 1] - psum[j] <= target)
                ans = min((LL)ans, i - j + 1 + (target - (psum[i + 1] - psum[j])) / mod * n);
        }
        return ans < INT_MAX ? ans : -1;
    }
};
