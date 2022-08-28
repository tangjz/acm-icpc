class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        unordered_map<int, int> pos;
        vector<int> ans(n, -1), pR(m, m + 1);
        for(int i = 0; i < n; ++i)
            pos[nums1[i]] = i;
        for(int i = m - 1; i >= 0; --i) {
            for(pR[i] = i + 1; pR[i] < m && nums2[i] > nums2[pR[i]]; pR[i] = pR[pR[i]]);
            if(pR[i] == m)
                continue;
            auto it = pos.find(nums2[i]);
            if(it != pos.end())
                ans[it -> second] = nums2[pR[i]];
        }
        return ans;
    }
};
