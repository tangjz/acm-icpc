class Solution {
    vector<int> pr;
public:
    Solution() {
        const int maxv = (int)1.5e4 + 1;
        vector<int> d(maxv);
        for(int i = 2; i < maxv; ++i) {
            if(!d[i]) {
                pr.push_back(i);
                d[i] = i;
            }
            for(int p: pr) {
                int j = i * p;
                if(j >= maxv)
                    break;
                d[j] = p;
                if(d[i] == p)
                    break;
            }
        }
    }
    int primePalindrome(int n) {
        n = max(n, 2);
        string s = to_string(n);
        int len = s.size(), half = (len + 1) >> 1;
        int sta = stoi(s.substr(0, half)), pw = 1;
        for(int i = 0; i < half; ++i)
            pw *= 10;
        for( ; ; ++len, (len & 1) && (++half, pw *= 10), sta = pw / 10) {
            for( ; sta < pw; ++sta) {
                string t = to_string(sta);
                string rev_t = t;
                reverse(rev_t.begin(), rev_t.end());
                if(len & 1)
                    t.pop_back();
                t += rev_t;
                int val = stoi(t);
                if(val < n)
                    continue;
                bool ban = 0;
                for(int p: pr) {
                    if(p * p > val)
                        break;
                    if(val % p == 0) {
                        ban = 1;
                        break;
                    }
                }
                if(!ban)
                    return val;
            }
        }
        return -1;
    }
};
