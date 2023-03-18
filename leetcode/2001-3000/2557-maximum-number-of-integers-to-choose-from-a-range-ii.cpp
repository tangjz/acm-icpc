class Solution {
public:
    int maxCount(vector<int>& banned, int n, long long maxSum) {
        typedef long long LL;
        sort(banned.begin(), banned.end());
        banned.erase(unique(banned.begin(), banned.end()), banned.end());
        banned.push_back(n + 1);
        int ans = 0, las = 0;
        for(int x: banned) {
            if(las + 1 < x) {
                LL sum = (las + x) * (x - las - 1LL) / 2;
                if(sum > maxSum) {
                    int L = las + 1, R = x;
                    while(L < R) {
                        int M = (L + R + 1) >> 1;
                        sum = (las + M) * (M - las - 1LL) / 2;
                        if(sum > maxSum) {
                            R = M - 1;
                        } else {
                            L = M;
                        }
                    }
                    ans += L - las - 1;
                    break;
                }
                ans += x - las - 1;
                maxSum -= sum;
            }
            las = x;
        }
        return ans;
    }
};