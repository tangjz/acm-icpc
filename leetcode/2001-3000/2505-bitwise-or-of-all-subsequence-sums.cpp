class Solution {
public:
    long long subsequenceSumOr(vector<int>& nums) {
        typedef long long LL;
        int n = nums.size();
        LL ans = 0, mx = 0;
        vector<pair<int, int> > ord(n);
        for(int x: nums)
            mx += x;
        ans = mx;
        // printf("mx: %d\n", mx);
        for(int i = 0; (1LL << i) <= mx; ++i) {
            if((ans >> i) & 1)
                continue;
            LL msk = (1LL << (i + 1)) - 1;
            // printf("check %d: %lld\n", i, msk);
            for(int j = 0; j < n; ++j)
                ord[j] = {nums[j] & msk, j};
            sort(ord.begin(), ord.end());
            LL sum = 0;
            // for(auto &it: ord)
            //     printf("%d: %d\n", it.second, it.first);
            for(int j = n - 1; j >= 0; --j) {
                sum += nums[ord[j].second];
                if((sum >> i) & 1) {
                    ans |= sum;
                    break;
                }
            }
        }
        return ans;
    }
};
