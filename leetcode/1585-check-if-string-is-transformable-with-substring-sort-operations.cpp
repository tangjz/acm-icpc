class Solution {
public:
    bool isTransformable(string s, string t) {
        const int maxd = 10;
        vector<int> pos[maxd + 1];
        int idx = 0;
        for(char ch : s) {
            pos[(int)(ch - '0')].push_back(idx++);
        }
        reverse(t.begin(), t.end());
        for(char ch : t) {
            int x = ch - '0';
            if(pos[x].empty())
                return 0;
            idx = pos[x].back();
            for(int i = x + 1; i < maxd; ++i)
                if(!pos[i].empty() && pos[i].back() > idx)
                    return 0;
            pos[x].pop_back();
        }
        return 1;
    }
};
