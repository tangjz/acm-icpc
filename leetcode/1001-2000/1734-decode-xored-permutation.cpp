class Solution {
public:
    vector<int> decode(vector<int>& encoded) {
        int n = encoded.size() + 1, fir = 1;
        for(int i = 0; i < n - 1; ++i) {
            if(i > 0)
                encoded[i] ^= encoded[i - 1];
            fir ^= encoded[i] ^ (i + 2);
        }
        vector<int> ret = {fir};
        for(int x: encoded)
            ret.push_back(fir ^ x);
        return ret;
    }
};
