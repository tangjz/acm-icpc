class Solution {
public:
    int waysToPartition(vector<int>& nums, int k) {
        typedef long long LL;
        int n = nums.size();
        vector<LL> psum = {0LL};
        for(int x: nums)
            psum.push_back(psum.back() + x);
        // no change: [psum[i] * 2 == psum.back() for i in range(1, n)]
        int ans = 0;
        LL tot = psum.back();
        map<int, int> lft, rht;
        for(int i = 1; i < n; ++i) {
            ans += psum[i] * 2 == tot;
            ++rht[psum[i]];
        }
        // change i in [0, n): left [0, i] unchanged, right [i+1, n) shifted by diff
        for(int i = 0; i < n; ++i) {
            if(i > 0) {
                ++lft[psum[i]];
                --rht[psum[i]];
            }
            LL newTot = tot - nums[i] + k;
            if(newTot & 1)
                continue;
            int ctr = 0, tmp = newTot >> 1;
            if(lft.count(tmp))
                ctr += lft[tmp];
            tmp = tmp - k + nums[i];
            if(rht.count(tmp))
                ctr += rht[tmp];
            ans = max(ans, ctr);
        }
        return ans;
    }
};
