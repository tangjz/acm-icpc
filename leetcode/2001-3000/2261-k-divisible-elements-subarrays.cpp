class Solution {
public:
    int countDistinct(vector<int>& nums, int k, int p) {
        int n = nums.size();
        set<vector<int> > Hash;
        for(int i = 0; i < n; ++i) {
            vector<int> vec;
            for(int j = i, c = 0; j < n; ++j) {
                c += nums[j] % p == 0;
                if(c > k)
                    break;
                vec.push_back(nums[j]);
                Hash.insert(vec);
            }
        }
        return Hash.size();
    }
};
