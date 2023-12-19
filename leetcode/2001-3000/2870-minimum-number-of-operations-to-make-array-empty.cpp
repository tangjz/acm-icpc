class Solution {
public:
    int minOperations(vector<int>& nums) {
        int ans = 0;
        unordered_map<int, int> ctr;
        for(int x: nums)
            ++ctr[x];
        for(auto &[k, v]: ctr) {
            if(v == 1)
                return -1;
            ans += v / 3 + (v % 3 > 0);
        }
        return ans;
    }
};
