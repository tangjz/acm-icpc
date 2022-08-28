class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> seq;
        for(int x: nums) {
            auto it = lower_bound(seq.begin(), seq.end(), x);
            if(it == seq.end()) {
                seq.push_back(x);
            } else {
                *it = x;
            }
        }
        return seq.size();
    }
};
