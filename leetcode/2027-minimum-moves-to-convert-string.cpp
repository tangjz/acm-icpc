class Solution {
public:
    int minimumMoves(string s) {
        int n = s.size();
        vector<int> pos;
        for(int i = 0; i < n; ++i)
            if(s[i] == 'X')
                pos.push_back(i);
        int ans = 0;
        while(!pos.empty()) {
            int cur = pos.back();
            ++ans;
            while(!pos.empty() && cur - pos.back() <= 2)
                pos.pop_back();
        }
        return ans;
    }
};
