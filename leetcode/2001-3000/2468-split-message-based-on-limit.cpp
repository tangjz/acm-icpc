class Solution {
public:
    vector<string> splitMessage(string message, int limit) {
        int n = message.size();
        int pre = 0;
        for(int len = 1, low = 1, upp = 10; len + len + 3 < limit; ++len, low = upp, upp *= 10) { // [low, upp)
            // pre + (val - low + 1) * len + val * (len + 3) + n <= val * limit
            int pos = max(low, max(n + pre - (low - 1) * len - 1, 0) / (limit - len - len - 3) + 1);
            if(pos < upp) {
                string suf = "/" + to_string(pos) + ">";
                vector<string> ret(pos);
                for(int i = 1, L = 0; i <= pos; ++i) {
                    string &cur = ret[i - 1] = "<" + to_string(i) + suf;
                    int adt = min(limit - (int)cur.size(), n - L);
                    cur = message.substr(L, adt) + cur;
                    L += adt;
                }
                return ret;
            }
            pre += (upp - low) * len;
        }
        return {};
    }
};
