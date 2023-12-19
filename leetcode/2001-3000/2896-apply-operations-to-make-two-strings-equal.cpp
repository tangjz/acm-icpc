class Solution {
public:
    int minOperations(string s1, string s2, int x) {
        int n = s1.size();
        vector<int> pos;
        for(int i = 0; i < n; ++i)
            if(s1[i] != s2[i])
                pos.push_back(i);
        int m = pos.size();
        if(m & 1)
            return -1;
        if(!m)
            return 0;
        int f[2] = {0, 0};
        for(int i = 1; i < m; ++i)
            f[i & 1] = min(f[~i & 1], f[i & 1] + pos[i] - pos[i - 1] - x);
        return min(f[0], f[1]) + m / 2 * x;
    }
};
