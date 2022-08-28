class Solution {
public:
    bool oneEditAway(string first, string second) {
        if(first.size() == second.size()) {
            int n = first.size(), ctr = 0;
            for(int i = 0; i < n; ++i)
                ctr += first[i] == second[i];
            return ctr >= n - 1;
        }
        if(first.size() < second.size())
            first.swap(second);
        if(first.size() > second.size() + 1)
            return 0;
        int m = second.size(), p = 0;
        for(char ch: first)
            if(ch == second[p] && (++p) == m)
                break;
        return p == m;
    }
};
