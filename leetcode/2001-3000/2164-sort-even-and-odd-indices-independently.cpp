class Solution {
public:
    vector<int> sortEvenOdd(vector<int>& nums) {
        vector<int> vec[2];
        for(int i = 0; i < (int)nums.size(); ++i)
            vec[i & 1].push_back(nums[i]);
        sort(vec[0].begin(), vec[0].end());
        sort(vec[1].begin(), vec[1].end(), greater<int>());
        nums = {};
        for(int i = 0; i < (int)vec[0].size(); ++i) {
            nums.push_back(vec[0][i]);
            if(i < (int)vec[1].size())
                nums.push_back(vec[1][i]);
        }
        return nums;
    }
};
