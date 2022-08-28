class Solution {
public:
    int maximumSum(vector<int>& nums) {
        int ans = -1;
        unordered_map<int, int> mp;
        for(int x: nums) {
            int s = 0;
            for(int tmp = x; tmp > 0; s += tmp % 10, tmp /= 10);
            if(mp.count(s)) {
                ans = max(ans, mp[s] + x);
            }
            mp[s] = max(mp[s], x);
        }
        return ans;
    }
};
