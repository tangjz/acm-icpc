class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        for(int i = 0; i < n; ++i)
            nums.push_back(nums[i]);
        vector<int> pR(n + n);
        for(int i = n + n - 1; i >= 0; --i)
            for(pR[i] = i + 1; pR[i] < n + n && nums[i] >= nums[pR[i]]; pR[i] = pR[pR[i]]);
        pR.resize(n);
        for(int i = 0; i < n; ++i)
            pR[i] = pR[i] < n + n ? nums[pR[i]] : -1;
        return pR;
    }
};
