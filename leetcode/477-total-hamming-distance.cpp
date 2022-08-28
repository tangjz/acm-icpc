class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        int n = nums.size();
        vector<int> ctr;
        for(int x: nums)
            for(int i = 0; x > 0; ++i, x >>= 1)
                if(x & 1) {
                    while(i >= ctr.size())
                        ctr.push_back(0);
                    ++ctr[i];
                }
        long long ans = 0;
        for(int x: ctr)
            ans += x * (n - x);
        return ans;
    }
};
