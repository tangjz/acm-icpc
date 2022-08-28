class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> Hash;
        Hash[0] = 0;
        int ans = 0, pos = 0, sum = 0;
        for(int x : nums) {
            ++pos;
            sum += x ? 1 : -1;
            auto it = Hash.find(sum);
            if(it == Hash.end()) {
                Hash[sum] = pos;
            } else {
                ans = max(ans, pos - Hash[sum]);
            }
        }
        return ans;
    }
};
