class Solution {
public:
    char findKthBit(int n, int k) {
        // len[i] = (1 << i) - 1
        int ans = 0;
        for(int i = n; i > 1; --i) {
            if(k == (1 << (i - 1))) {
                ans ^= 1;
                break;
            }
            if(k > (1 << (i - 1))) {
                k = (1 << i) - k;
                ans ^= 1;
            }
        }
        return '0' + ans;
    }
};
