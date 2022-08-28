class Solution {
public:
    bool checkRecord(string s) {
        int cntA = 0, cntL = 0;
        for(char ch: s) {
            if(ch == 'L') {
                if((++cntL) == 3)
                    return 0;
            } else {
                cntL = 0;
                if(ch == 'A' && (++cntA) == 2)
                    return 0;
            }
        }
        return 1;
    }
};
