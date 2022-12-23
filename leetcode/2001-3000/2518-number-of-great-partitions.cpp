class Solution {
public:
    int countPartitions(vector<int>& nums, int k) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int ans = 1;
        LL sum = 0;
        vector<int> ways(k);
        ways[0] = 1;
        for(int x: nums) {
            (ans <<= 1) >= mod && (ans -= mod);
            sum += x;
            for(int i = k - 1; i >= x; --i)
                (ways[i] += ways[i - x]) >= mod && (ways[i] -= mod);
        }
        for(int i = 0; i < k; ++i) {
            LL j = sum - i;
            (ans -= ways[i]) < 0 && (ans += mod);
            if(j >= k)
                (ans -= ways[i]) < 0 && (ans += mod);
        }
        return ans;
    }
};
