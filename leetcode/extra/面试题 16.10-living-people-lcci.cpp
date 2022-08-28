class Solution {
public:
    int maxAliveYear(vector<int>& birth, vector<int>& death) {
        static const int ofs = 1900, maxv = 103;
        vector<int> ctr(maxv);
        for(int x: birth)
            ++ctr[x - ofs];
        for(int x: death)
            --ctr[x - ofs + 1];
        for(int i = 1; i < maxv; ++i)
            ctr[i] += ctr[i - 1];
        return max_element(ctr.begin(), ctr.end()) - ctr.begin() + ofs;
    }
};
