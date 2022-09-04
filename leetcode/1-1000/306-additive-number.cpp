class Solution {
    string rev_add(string const &u, string const &v) {
        int adt = 0;
        string w = "";
        for(int i = 0; i < (int)u.size() || i < (int)v.size(); ++i) {
            if(i < (int)u.size())
                adt += u[i] - '0';
            if(i < (int)v.size())
                adt += v[i] - '0';
            w.push_back('0' + (adt % 10));
            adt /= 10;
        }
        if(adt)
            w.push_back('0' + adt);
        return move(w);
    }
public:
    bool isAdditiveNumber(string num) {
        int n = num.size();
        reverse(num.begin(), num.end());
        for(int i = n - 2; i - 1 >= 0; --i) {
            if(num[n - 1] == '0' && i < n - 2)
                break;
            for(int j = i - 1; j >= 0; --j) {
                if(num[i] == '0' && j < i - 1)
                    break;
                string f0 = num.substr(i + 1), f1 = num.substr(j + 1, i - j);
                // printf("i %d j %d: f0 %s f1 %s\n", i, j, f0.c_str(), f1.c_str());
                int k = j;
                while(k >= 0) {
                    f0 = rev_add(f0, f1);
                    swap(f0, f1);
                    int sz = f1.size();
                    // printf("k %d: f1 %s\n", k - sz + 1, f1.c_str());
                    if(k - sz + 1 < 0 || num.substr(k - sz + 1, sz) != f1)
                        break;
                    k -= sz;
                }
                if(k == -1)
                    return 1;
            }
        }
        return 0;
    }
};
