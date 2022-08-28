class Solution {
public:
    int thirdMax(vector<int>& nums) {
        vector<int> ret;
        for(int i = 0; i < 3 && !nums.empty(); ++i) {
            ret.push_back(*max_element(nums.begin(), nums.end()));
            nums.erase(remove(nums.begin(), nums.end(), ret.back()), nums.end());
        }
        return ret[(int)ret.size() < 3 ? 0: 2];
    }
};
