class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = (int)nums.size();
        vector<int> ctr(n, 0), ord, tmp;
        for(int i = 0; i < n; ++i)
            ord.push_back(i);
        tmp.reserve(n);
        function<void(int, int)> solve = [&](int L, int R) {
            if(L == R)
                return;
            int M = (L + R) >> 1;
            solve(L, M);
            solve(M + 1, R);
            for(int u = L, v = M + 1; u <= M || v <= R; )
                if(v > R || (u <= M && nums[ord[u]] <= nums[ord[v]])) {
                    ctr[ord[u]] += v - (M + 1);
                    tmp.push_back(ord[u++]);
                } else {
                    tmp.push_back(ord[v++]);
                }
            int pos = L;
            for(int x : tmp)
                ord[pos++] = x;
            tmp.clear();
        };
        if(n > 0)
            solve(0, n - 1);
        return ctr;
    }
};
