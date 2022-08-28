class Solution {
public:
    int countPrimes(int n) {
        vector<int> d(n), pr;
        for(int i = 2; i < n; ++i) {
            if(!d[i]) {
                pr.push_back(i);
                d[i] = i;
            }
            for(int p: pr) {
                int j = i * p;
                if(j >= n)
                    break;
                d[j] = p;
                if(d[i] == p)
                    break;
            }
        }
        return pr.size();
    }
};
