class Solution {
public:
    vector<int> finalPrices(vector<int>& p) {
        int n = p.size();
        vector<int> ret;
        for(int i = 0; i < n; ++i) {
            int val = p[i];
            for(int j = i + 1; j < n; ++j)
                if(p[j] <= val) {
                    val -= p[j];
                    break;
                }
            ret.push_back(val);
        }
        return ret;
    }
};
