class Solution {
    vector<int> getHeight(string s) {
        int n = s.length();
        vector<int> ret(n);
        int pos = 0, rht = 0;
        for(int i = 0; i < n; ++i) {
            int &cur = ret[i] = i < rht ? min(rht - i, ret[pos + pos - i]) : 0;
            while(i - cur >= 0 && i + cur < n && s[i - cur] == s[i + cur])
                ++cur;
            if(i + cur > rht) {
                pos = i;
                rht = i + cur;
            }
        }
        return ret;
    }
    vector<int> getPrePal(vector<int> height) {
        int n = height.size();
        vector<vector<int> > events(n);
        vector<int> ret;
        set<int> pos;
        int cur = 0;
        for(int i = 0; i < n; ++i) {
            for(int j: events[i])
                pos.erase(j);
            pos.insert(i);
            int j = i + height[i];
            if(j < n)
                events[j].push_back(i);
            j = *pos.begin();
            cur = max(cur, (i - j) * 2 + 1);
            ret.push_back(cur);
        }
        return ret;
    }
public:
    long long maxProduct(string s) {
        int n = s.length();
        vector<int> height = getHeight(s);
        // puts("ok1");
        vector<int> pre = getPrePal(height);
        // puts("ok2");
        reverse(height.begin(), height.end());
        vector<int> suf = getPrePal(height);
        reverse(suf.begin(), suf.end());
        typedef long long LL;
        LL ans = 0;
        int upp = 0;
        for(int i = 0; i < n; ++i) {
            ans = max(ans, (LL)upp * suf[i]);
            upp = max(upp, pre[i]);
        }
        return ans;
    }
};
