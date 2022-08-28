class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        int n = (int)arr.size();
        vector<int> ord(n), rnk(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return arr[u] < arr[v];
        });
        for(int i = 0, j = 0, rk = 1; i < n; ++i) {
            for( ; j < i && arr[ord[j]] < arr[ord[i]]; ++j)
                if(!j || arr[ord[j - 1]] != arr[ord[j]])
                    ++rk;
            rnk[ord[i]] = rk;
        }
        return rnk;
    }
};
