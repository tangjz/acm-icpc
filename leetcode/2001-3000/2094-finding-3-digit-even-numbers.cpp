class Solution {
public:
    vector<int> findEvenNumbers(vector<int>& digits) {
        const int maxd = 10;
        vector<int> ctr(maxd);
        for(int i: digits)
            ++ctr[i];
        vector<int> ret;
        for(int x = 1; x < maxd; ++x) {
            if(!ctr[x])
                continue;
            --ctr[x];
            for(int y = 0; y < maxd; ++y) {
                if(!ctr[y])
                    continue;
                --ctr[y];
                for(int z = 0; z < maxd; z += 2) {
                    if(!ctr[z])
                        continue;
                    ret.push_back((x * maxd + y) * maxd + z);
                }
                ++ctr[y];
            }
            ++ctr[x];
        }
        return ret;
    }
};
