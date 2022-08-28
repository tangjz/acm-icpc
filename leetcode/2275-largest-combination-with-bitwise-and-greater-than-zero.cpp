class Solution {
public:
    int largestCombination(vector<int>& A) {
        int n = A.size(), mx = *max_element(A.begin(), A.end()) + 1, ans = 0;
        for(int i = 1; i < mx; i <<= 1) {
            int ctr = 0;
            for(int x: A)
                ctr += !!(x & i);
            ans = max(ans, ctr);
        }
        return ans;
    }
};
