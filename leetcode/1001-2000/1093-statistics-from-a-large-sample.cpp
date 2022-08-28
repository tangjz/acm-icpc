class Solution {
public:
    vector<double> sampleStats(vector<int>& count) {
        typedef long long LL;
        int n = count.size();
        int low = -1, upp = -1, mx = 0, cnt = 0;
        LL sum = 0;
        for(int i = n - 1; i >= 0; --i) {
            sum += cnt;
            cnt += count[i];
            if(count[i]) {
                low = i;
                if(upp == -1) {
                    upp = i;
                }
                if(count[mx] < count[i]) {
                    mx = i;
                }
            }
        }
        int cL = (cnt - 1) >> 1, cR = cnt >> 1;
        int mid1 = -1, mid2 = -1;
        for(int i = 0, c = 0; i < n; ++i) {
            int nxt = c + count[i];
            if(c <= cL && cL < nxt) {
                mid1 = i;
            }
            if(c <= cR && cR < nxt) {
                mid2 = i;
            }
            c = nxt;
        }
        return {1.0 * low, 1.0 * upp, 1.0 * sum / cnt, (mid1 + mid2) / 2.0, 1.0 * mx};
    }
};
