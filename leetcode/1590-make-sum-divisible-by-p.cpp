class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        int n = (int)nums.size(), ans = n, sum = 0;
        unordered_map<int, int> Hash;
        for(int x : nums)
            sum = (sum + x) % p;
        if(!sum)
            return 0;
        int pos = 0, cur = 0;
        for(int x : nums) {
            Hash[cur] = pos++;
            cur = (cur + x) % p;
            int need = (cur - sum) % p;
            if(need < 0)
                need += p;
            auto it = Hash.find(need);
            if(it != Hash.end())
                ans = min(ans, pos - (it -> second));
        }
        return ans < n ? ans : -1;
    }
};
