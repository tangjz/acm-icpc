class Solution {
public:
    long long pickGifts(vector<int>& A, int k) {
        while(k--) {
            auto it = max_element(A.begin(), A.end());
            *it = floor(sqrtl(*it));
        }
        long long ans = 0;
        for(int x: A)
            ans += x;
        return ans;
    }
};
