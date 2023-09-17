class Solution {
public:
    vector<long long> distance(vector<int>& A) {
        typedef long long LL;
        int n = A.size();
        unordered_map<int, vector<int> > pos;
        vector<LL> ret(n);
        for(int i = 0; i < n; ++i)
            pos[A[i]].push_back(i);
        for(auto &it: pos) {
            auto &vec = it.second;
            int cL = 0, cR = vec.size();
            LL sL = 0, sR = 0;
            for(int x: vec)
                sR += x;
            for(int x: vec) {
                ++cL;
                --cR;
                sL += x;
                sR -= x;
                ret[x] = (LL)(cL - cR) * x + (sR - sL);
            }
        }
        return ret;
    }
};
