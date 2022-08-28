class Solution {
public:
    string removeDuplicates(string s, int k) {
        stack<pair<char, int> > stk;
        for(char ch: s) {
            int occ = !stk.empty() && stk.top().first == ch ? stk.top().second + 1 : 1;
            if(occ < k) {
                stk.push({ch, occ});
            } else {
                for(int i = 1; i < k; ++i)
                    stk.pop();
            }
        }
        string t = "";
        while(!stk.empty()) {
            t.push_back(stk.top().first);
            stk.pop();
        }
        reverse(t.begin(), t.end());
        return t;
    }
};
