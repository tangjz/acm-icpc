class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size(), ans = n + 1;
        for(int i = 0, j = n, c = 0; i < n; ++i) { // [0, i) [j, n)
            for( ; i < j && c < x; c += nums[--j]);
            if(c == x)
                ans = min(ans, i + n - j);
            if(i == j) {
                ++j;
            } else {
                c += nums[i];
            }
            for( ; j < n && c > x; c -= nums[j++]);
        }
        return ans <= n ? ans : -1;
    }
};
