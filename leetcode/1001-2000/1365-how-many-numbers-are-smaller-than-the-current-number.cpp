class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        map<int, int> ctr, psum;
        for(int x: nums)
            ++ctr[x];
        int sum = 0;
        for(auto &it: ctr) {
            psum[it.first] = sum;
            sum += it.second;
        }
        for(int &x: nums)
            x = psum[x];
        return move(nums);
    }
};
