class Solution {
public:
    int widestPairOfIndices(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), ans = 0;
        unordered_map<int, int> pos;
        pos.insert({0, -1});
        for(int i = 0, s = 0; i < n; ++i) {
            s += nums1[i] - nums2[i];
            ans = max(ans, i - pos.insert({s, i}).first -> second);
        }
        return ans;
    }
};
