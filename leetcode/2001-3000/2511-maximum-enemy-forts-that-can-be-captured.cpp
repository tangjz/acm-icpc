class Solution {
public:
    int captureForts(vector<int>& forts) {
        int n = forts.size(), ans = 0;
        for(int i = 0; i < n; ++i) {
            if(forts[i] != 1)
                continue;
            for(int j = i + 1, c = 0; j < n; ++j) {
                if(forts[j] != 0) {
                    if(forts[j] == -1)
                        ans = max(ans, c);
                    break;
                }
                ++c;
            }
            for(int j = i - 1, c = 0; j >= 0; --j) {
                if(forts[j] != 0) {
                    if(forts[j] == -1)
                        ans = max(ans, c);
                    break;
                }
                ++c;
            }
        }
        return ans;
    }
};
