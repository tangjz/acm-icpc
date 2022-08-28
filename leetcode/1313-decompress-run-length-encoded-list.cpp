class Solution {
public:
    vector<int> decompressRLElist(vector<int>& nums) {
        int n = (int)nums.size();
        vector<int> ret;
        for(int i = 0; i < n; i += 2) {
            int c = nums[i], v = nums[i + 1];
            while(c--)
                ret.push_back(v);
        }
        return ret;
    }
};
