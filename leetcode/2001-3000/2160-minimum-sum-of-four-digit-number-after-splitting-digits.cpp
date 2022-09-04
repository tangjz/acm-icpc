class Solution {
public:
    int minimumSum(int num) {
        string buf = to_string(num);
        int n = buf.size();
        sort(buf.begin(), buf.end());
        int v[2] = {};
        for(int i = 0; i < n; ++i)
            v[i & 1] = v[i & 1] * 10 + (buf[i] - '0');
        return v[0] + v[1];
    }
};
