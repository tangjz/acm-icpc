class Solution {
public:
    bool containsPattern(vector<int>& arr, int m, int k) {
        int n = (int)arr.size();
        for(int i = 0; i <= n - m * k; ++i) {
            bool chk = 1;
            for(int j = 0; chk && j < m; ++j)
                for(int id = 1, u = i + j, v = u + m; chk && id < k; ++id, u = v, v += m)
                    chk &= arr[u] == arr[v];
            if(chk)
                return 1;
        }
        return 0;
    }
};
