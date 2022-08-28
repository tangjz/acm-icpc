class Solution {
public:
    vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
        int n = nums.size(), m = l.size();
        vector<bool> ret(m);
        for(int i = 0; i < m; ++i) {
            int L = l[i], R = r[i];
            vector<int> seq;
            for(int j = L; j <= R; ++j)
                seq.push_back(nums[j]);
            sort(seq.begin(), seq.end());
            ret[i] = true;
            for(int j = 1; ret[i] && j < R - L; ++j)
                ret[i] = seq[j - 1] + seq[j + 1] == seq[j] + seq[j];
        }
        return ret;
    }
};
