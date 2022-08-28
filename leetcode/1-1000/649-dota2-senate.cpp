class Solution {
public:
    string predictPartyVictory(string senate) {
        int n = senate.size();
        set<int> R, D;
        for(int i = 0; i < n; ++i)
            if(senate[i] == 'R') {
                R.insert(i);
            } else {
                D.insert(i);
            }
        int pos = 0;
        while(!R.empty() || !D.empty()) {
            int low = n;
            auto it = R.lower_bound(pos), jt = D.lower_bound(pos);
            if(it == R.end())
                it = R.begin();
            if(it != R.end()) {
                int dis = *it - pos;
                low = min(low, dis < 0 ? dis + n : dis);
            }
            if(jt == D.end())
                jt = D.begin();
            if(jt != D.end()) {
                int dis = *jt - pos;
                low = min(low, dis < 0 ? dis + n : dis);
            }
            (low += pos) >= n && (low -= n);
            (pos = low + 1) == n && (pos = 0);
            if(it != R.end() && low == *it) {
                if(D.empty())
                    return "Radiant";
                jt = D.lower_bound(pos);
                if(jt == D.end())
                    jt = D.begin();
                D.erase(jt);
            } else {
                if(R.empty())
                    return "Dire";
                it = R.lower_bound(pos);
                if(it == R.end())
                    it = R.begin();
                R.erase(it);
            }
        }
        return "";
    }
};
