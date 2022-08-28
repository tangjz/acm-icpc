class Solution {
public:
    int secondsToRemoveOccurrences(string s) {
        int n = s.size(), ans = 0;
        while(true) {
            int cnt = 0;
            for(int i = 0; i + 1 < n; ++i)
                if(s[i] == '0' && s[i + 1] == '1') {
                    swap(s[i], s[i + 1]);
                    ++i;
                    ++cnt;
                }
            if(!cnt)
                break;
            ++ans;
        }
        return ans;
    }
};
