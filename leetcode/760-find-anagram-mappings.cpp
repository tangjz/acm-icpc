class Solution {
public:
    vector<int> anagramMappings(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> ret(n);
        unordered_map<int, vector<int> > pos;
        for(int i = 0; i < n; ++i)
            pos[nums1[i]].push_back(i);
        for(int i = 0; i < n; ++i) {
            ret[pos[nums2[i]].back()] = i;
            pos[nums2[i]].pop_back();
        }
        return ret;
    }
};
