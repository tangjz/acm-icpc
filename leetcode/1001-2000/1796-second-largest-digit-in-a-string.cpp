class Solution {
public:
    int secondHighest(string s) {
        set<int> vis;
        for(char ch : s)
            if(ch >= '0' && ch <= '9')
                vis.insert(ch - '0');
        return vis.size() > 1 ? *(++vis.rbegin()) : -1;
    }
};
