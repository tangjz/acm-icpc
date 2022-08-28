class Solution {
public:
    vector<int> powerfulIntegers(int x, int y, int bound) {
        vector<int> ret;
        for(int u = 1; u <= bound; u *= x > 1 ? x : bound + 1)
            for(int v = 1; u + v <= bound; v *= y > 1 ? y : bound + 1)
                ret.push_back(u + v);
        sort(ret.begin(), ret.end());
        ret.erase(unique(ret.begin(), ret.end()), ret.end());
        return ret;
    }
};
