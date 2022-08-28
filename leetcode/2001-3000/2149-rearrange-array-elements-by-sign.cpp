class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        vector<int> vec[2];
        for(int x: nums)
            vec[x < 0].push_back(x);
        int n = vec[0].size();
        vector<int> ret;
        for(int i = 0; i < n; ++i) {
            ret.push_back(vec[0][i]);
            ret.push_back(vec[1][i]);
        }
        return ret;
    }
};
