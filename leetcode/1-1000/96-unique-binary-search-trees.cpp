class Solution {
public:
    int numTrees(int n) {
        vector<int> c(n + n + 1), d(n + n + 1), pr;
        for(int i = 2; i <= n + n; ++i) {
            if(!d[i]) {
                pr.push_back(i);
                d[i] = i;
            }
            for(int p : pr) {
                int j;
                if((j = i * p) > n + n)
                    break;
                d[j] = p;
                if(d[i] == p)
                    break;
            }
        }
        int ret = 1; // (2n)! / n! / (n+1)! = (2n choose n) / (n+1)
        for(int i = n + n; i >= 2; --i) {
            c[i] += 1 - (i <= n) - (i <= n + 1);
            if(d[i] < i) {
                c[d[i]] += c[i];
                c[i / d[i]] += c[i];
            } else {
                for(int j = c[i]; j > 0; --j)
                    ret *= i;
            }
        }
        return ret;
    }
};
