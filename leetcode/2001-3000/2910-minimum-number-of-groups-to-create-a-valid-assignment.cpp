class Solution {
public:
    int minGroupsForValidAssignment(vector<int>& nums) {
        unordered_map<int, int> ctr, ctr2;
        for(int x: nums)
            ++ctr[x];
        int n = nums.size(), low = n, ans = low;
        for(auto &it: ctr) {
            ++ctr2[it.second];
            low = min(low, it.second);
        }
        for(int i = 1; i <= low + 1; ++i) {
            int tmp = 0;
            bool skp = 0;
            for(auto &it: ctr2) {
                int c = (it.first - 1) / i + 1;
                if(it.first < (i - 1) * c) {
                    skp = 1;
                    break;
                }
                tmp += c * it.second;
            }
            if(!skp)
                ans = min(ans, tmp);
        }
        return ans;
    }
};
