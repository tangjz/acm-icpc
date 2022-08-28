class Solution {
public:
    int numIdenticalPairs(vector<int>& nums) {
        unordered_map<int, int> Hash;
        for(int x : nums)
            ++Hash[x];
        int ans = 0;
        for(auto &it : Hash) {
            int x = it.second;
            ans += x * (x - 1) / 2;
        }
        return ans;
    }
};
