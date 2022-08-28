class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        int n = nums.size(), ans = n, upp = 0;
        unordered_map<int, vector<int> > pos;
        for(int i = 0; i < n; ++i) {
            auto &vec = pos[nums[i]];
            vec.push_back(i);
            upp = max(upp, (int)vec.size());
        }
        for(auto &it: pos) {
            if((int)it.second.size() != upp)
                continue;
            ans = min(ans, it.second.back() - it.second.front() + 1);
        }
        return ans;
    }
};
