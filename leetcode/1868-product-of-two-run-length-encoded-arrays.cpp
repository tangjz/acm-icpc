class Solution {
public:
    vector<vector<int>> findRLEArray(vector<vector<int>>& encoded1, vector<vector<int>>& encoded2) {
        auto it = encoded1.begin(), jt = encoded2.begin();
        vector<vector<int> > ret;
        while(it != encoded1.end() && jt != encoded2.end()) {
            int x = (*it)[0] * (*jt)[0], c = min((*it)[1], (*jt)[1]);
            if(ret.empty() || ret.back()[0] != x) {
                ret.push_back({x, c});
            } else {
                ret.back()[1] += c;
            }
            if(c == (*it)[1]) {
                ++it;
            } else {
                (*it)[1] -= c;
            }
            if(c == (*jt)[1]) {
                ++jt;
            } else {
                (*jt)[1] -= c;
            }
        }
        return ret;
    }
};
