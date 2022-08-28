class Solution {
public:
    int minSwaps(string s) {
        int n = s.length();
        vector<int> pL, pR;
        for(int i = 0; i < n; ++i)
            if(s[i] == '[') {
                pL.push_back(i);
            } else {
                pR.push_back(i);
            }
        reverse(pL.begin(), pL.end());
        int ret = 0, sum = 0;
        for(int i = 0; i < n; ++i) {
            if(s[i] == '[') {
                ++sum;
            } else {
                --sum;
            }
            if(sum < 0) {
                assert(pR[ret] <= i && i <= pL[ret]);
                s[pL[ret]] = ']';
                s[pR[ret]] = '[';
                sum += 2;
                ++ret;
            }
        }
        printf("%s\n", s.c_str());
        return ret;
    }
};
