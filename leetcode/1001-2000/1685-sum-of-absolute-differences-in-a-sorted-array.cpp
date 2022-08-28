class Solution {
public:
    vector<int> getSumAbsoluteDifferences(vector<int>& nums) {
        int n = nums.size();
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return nums[u] < nums[v];
        });
        int sL = 0, sR = 0;
        vector<int> seq;
        for(int x: ord) {
            seq.push_back(nums[x]);
            sR += nums[x];
        }
        vector<int> ans(n);
        for(int i = 0; i < n; ++i) {
            ans[ord[i]] = sR - seq[i] * (n - i) + seq[i] * i - sL;
            sR -= seq[i];
            sL += seq[i];
        }
        return ans;
    }
};
