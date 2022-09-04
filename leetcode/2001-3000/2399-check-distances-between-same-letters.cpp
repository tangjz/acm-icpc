class Solution {
public:
    bool checkDistances(string s, vector<int>& distance) {
        int n = s.size();
        for(int i = 0; i < n; ++i) {
            if(!s[i])
                continue;
            int o = s[i] - 'a', j = i + distance[o] + 1;
            if(j >= n || s[j] != s[i])
                return 0;
            s[i] = s[j] = '\0';
        }
        return 1;
    }
};
