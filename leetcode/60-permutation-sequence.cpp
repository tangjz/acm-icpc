class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> prd(n);
        prd[0] = 1;
        for(int i = 1; i < n; ++i)
            prd[i] = prd[i - 1] * i;
        string ret = "";
        vector<bool> vis(n, 0);
        for(int i = 0; i < n; ++i) {
            int adt = prd[n - 1 - i], cnt = (k - 1) / adt;
            k -= adt * cnt;
            for(int j = 0; j < n; ++j)
                if(!vis[j] && !(cnt--)) {
                    ret += '1' + j;
                    vis[j] = 1;
                    break;
                }
        }
        return ret;
    }
};
