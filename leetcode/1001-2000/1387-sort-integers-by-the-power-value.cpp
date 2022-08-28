class Solution {
public:
    int getKth(int lo, int hi, int k) {
        unordered_map<int, int> Hash;
        Hash[1] = 0;
        function<int(int)> dfs = [&](int x) -> int {
            auto it = Hash.find(x);
            if(it != Hash.end())
                return it -> second;
            return Hash[x] = dfs(x & 1 ? (x * 3 + 1) : (x >> 1)) + 1;
        };
        vector<pair<int, int> > seq;
        for(int i = lo; i <= hi; ++i)
            seq.push_back(make_pair(dfs(i), i));
        nth_element(seq.begin(), seq.begin() + (k - 1), seq.end());
        return seq[k - 1].second;
    }
};
