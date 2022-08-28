class Solution {
public:
    int minSwaps(vector<int>& data) {
        int n = data.size(), m = 0, ans = 0;
        for(int x: data)
            m += x;
        for(int i = 0, c = 0; i < n; ++i) {
            c += data[i];
            if(i - m >= 0)
                c -= data[i - m];
            ans = max(ans, c);
        }
        return m - ans;
    }
};
