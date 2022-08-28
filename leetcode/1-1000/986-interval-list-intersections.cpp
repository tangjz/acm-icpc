class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        vector<vector<int> > ret;
        while(!A.empty() && !B.empty()) {
            auto it = A.back();
            A.pop_back();
            int las = A.empty() ? -1 : A.back()[1];
            while(!B.empty()) {
                auto &jt = B.back();
                int low = max(it[0], jt[0]), upp = min(it[1], jt[1]);
                if(low <= upp)
                    ret.push_back({low, upp});
                if(jt[0] <= las)
                    break;
                B.pop_back();
            }
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
