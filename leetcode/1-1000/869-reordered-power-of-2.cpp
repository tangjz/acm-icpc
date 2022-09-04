class Solution {
    unordered_set<string> sp;
public:
    Solution() {
        const int maxv = (int)1e9;
        for(int i = 1; i <= maxv; i <<= 1) {
            string rep = to_string(i);
            sort(rep.begin(), rep.end());
            sp.insert(rep);
        }
    }
    bool reorderedPowerOf2(int n) {
        string rep = to_string(n);
        sort(rep.begin(), rep.end());
        return sp.count(rep);
    }
};
