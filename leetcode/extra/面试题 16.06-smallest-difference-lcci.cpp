class Solution {
public:
    int smallestDifference(vector<int>& a, vector<int>& b) {
        typedef long long LL;
        bool firA = 1, firB = 1;
        int preA = 0, preB = 0;
        LL ans = LLONG_MAX;
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        for(auto it = a.begin(), jt = b.begin(); it != a.end() || jt != b.end(); )
            if(jt == b.end() || (it != a.end() && *it < *jt)) {
                if(!firB)
                    ans = min(ans, (LL)*it - preB);
                firA = 0;
                preA = *(it++);
            } else {
                if(!firA)
                    ans = min(ans, (LL)*jt - preA);
                firB = 0;
                preB = *(jt++);
            }
        return ans;
    }
};
