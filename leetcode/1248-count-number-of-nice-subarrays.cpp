class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int n = (int)nums.size();
        vector<int> pos;
        pos.push_back(-1);
        for(int i = 0; i < n; ++i)
            if(nums[i] & 1)
                pos.push_back(i);
        pos.push_back(n);
        int ans = 0, m = (int)pos.size();
        for(int i = 1, j = i + k - 1; j + 1 < m; ++i, ++j)
            ans += (pos[i] - pos[i - 1]) * (pos[j + 1] - pos[j]);
        return ans;
    }
};
