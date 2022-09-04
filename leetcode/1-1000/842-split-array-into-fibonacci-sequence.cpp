class Solution {
public:
    vector<int> splitIntoFibonacci(string num) {
        typedef long long LL;
        int n = num.size();
        LL f0 = 0;
        for(int i = 1; i < n; ++i) {
            if(num[0] == '0' && i > 1)
                break;
            f0 = f0 * 10 + (num[i - 1] - '0');
            if(f0 > INT_MAX)
                break;
            LL f1 = 0;
            for(int j = i + 1; j < n; ++j) {
                if(num[i] == '0' && j > i + 1)
                    break;
                f1 = f1 * 10 + (num[j - 1] - '0');
                if(f1 > INT_MAX)
                    break;
                int sz = 2;
                vector<int> seq = {(int)f0, (int)f1};
                int k = j;
                while(k < n) {
                    LL las = seq[sz - 2];
                    las += seq[sz - 1];
                    if(las > INT_MAX)
                        break;
                    string rep = to_string(las);
                    if(num.substr(k, rep.size()) != rep)
                        break;
                    k += rep.size();
                    seq.push_back(las);
                    ++sz;
                }
                if(k == n)
                    return seq;
            }
        }
        return {};
    }
};
