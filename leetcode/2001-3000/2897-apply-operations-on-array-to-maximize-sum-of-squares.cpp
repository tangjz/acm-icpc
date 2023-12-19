class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ctr;
        for(int x: nums)
            for(int i = 0; x > 0; ++i, x >>= 1)
                if(x & 1) {
                    if(i >= ctr.size())
                        ctr.resize(i + 1);
                    ++ctr[i];
                }
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int ans = 0;
        while(k > 0 && !ctr.empty()) {
            int tp = n + 1, val = 0;
            for(int i = 0; i < (int)ctr.size(); ++i)
                if(ctr[i]) {
                    tp = min(tp, ctr[i]);
                    val |= 1 << i;
                }
            tp = min(tp, k);
            k -= tp;
            for(int &x: ctr)
                if(x > 0)
                    x -= tp;
            while(!ctr.empty() && !ctr.back())
                ctr.pop_back();
            ans = (ans + (LL)val * val % mod * tp) % mod;
        }
        return ans;
    }
};
