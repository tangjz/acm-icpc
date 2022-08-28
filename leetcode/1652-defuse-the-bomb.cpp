class Solution {
public:
    vector<int> decrypt(vector<int>& code, int k) {
        int n = code.size();
        if(!k)
            return vector<int>(n);
        vector<int> psum = {0};
        for(int x: code)
            psum.push_back(psum.back() + x);
        vector<int> ret;
        for(int i = 0; i < n; ++i) {
            int L = k > 0 ? i + 1 : i + k, R = k > 0 ? i + k: i - 1; // [L, R]
            L = (L + n) % n;
            R = (R + n) % n;
            ret.push_back(psum[R + 1] - psum[L] + (L > R ? psum[n] : 0));
        }
        return ret;
    }
};
