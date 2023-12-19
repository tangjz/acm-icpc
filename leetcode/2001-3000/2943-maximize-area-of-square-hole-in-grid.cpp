class Solution {
public:
    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {
        auto calc = [&](int n, vector<int> &vec) {
            int ret = 1, m = vec.size();
            sort(vec.begin(), vec.end());
            for(int i = 0, j; i < m; i = j) {
                for(j = i + 1; j < m && vec[j] - 1 == vec[j - 1]; ++j);
                ret = max(ret, j - i + 1);
            }
            return ret;
        };
        int sz = min(calc(n, hBars), calc(m, vBars));
        return sz * sz;
    }
};
