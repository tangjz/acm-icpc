class Solution {
public:
    vector<int> findSwapValues(vector<int>& array1, vector<int>& array2) {
        int n = array1.size(), m = array2.size();
        long long dt = 0;
        unordered_set<int> pos1;
        for(int x: array1) {
            dt += x;
            pos1.insert(x);
        }
        for(int x: array2)
            dt -= x;
        if(dt & 1)
            return {};
        dt >>= 1;
        for(int i = 0; i < m; ++i) {
            long long v = dt + array2[i];
            if(v < INT_MIN || v > INT_MAX)
                continue;
            auto it = pos1.find(v);
            if(it != pos1.end())
                return {(int)v, array2[i]};
        }
        return {};
    }
};
