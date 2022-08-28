class Solution {
    int getMax(int upp, vector<int> &vec) {
        sort(vec.begin(), vec.end());
        int las = 0, ret = 0;
        for(int x : vec) {
            ret = max(ret, x - las);
            las = x;
        }
        return max(ret, upp - las);
    }
public:
    int maxArea(int h, int w, vector<int>& a, vector<int>& b) {
        int u = getMax(h, a);
        int v = getMax(w, b);
        return 1LL * u * v % ((int)1e9 + 7);
    }
};
