class Solution {
    int calc(vector<int> &A, int d) {
        int n = A.size(), ans = 0;
        unordered_map<int, int> ctr;
        for(int i = 0, j = 0, m = 0; i < n; ++i) {
            for( ; j < n && m <= d; ++j) {
                m += !ctr[A[j]];
                ++ctr[A[j]];
                if(m > d) {
                    --ctr[A[j]];
                    m -= !ctr[A[j]];
                    break;
                }
            }
            ans += j - i;
            --ctr[A[i]];
            m -= !ctr[A[i]];
        }
        return ans;
    }
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return calc(nums, k) - calc(nums, k - 1);
    }
};
