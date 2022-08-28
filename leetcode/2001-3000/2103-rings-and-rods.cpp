class Solution {
public:
    int countPoints(string rings) {
        int n = rings.size() / 2;
        int msk[10] = {};
        for(int i = 0; i < n; ++i) {
            char ch = rings[i + i];
            int idx = rings[i + i + 1] - '0';
            switch(ch) {
                case 'R':
                    msk[idx] |= 1;
                    break;
                case 'G':
                    msk[idx] |= 2;
                    break;
                case 'B':
                    msk[idx] |= 4;
                    break;
            }
        }
        int ans = 0;
        for(int i = 0; i < 10; ++i)
            ans += msk[i] == 7;
        return ans;
    }
};
