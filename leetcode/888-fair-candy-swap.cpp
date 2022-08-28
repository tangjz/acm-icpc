class Solution {
public:
    vector<int> fairCandySwap(vector<int>& A, vector<int>& B) {
        int sum = 0;
        unordered_set<int> sp;
        for(int x: A)
            sum += x;
        for(int x: B) {
            sum -= x;
            sp.insert(x);
        }
        assert(!(sum & 1));
        sum >>= 1;
        for(int x: A) {
            auto it = sp.find(x - sum);
            if(it != sp.end())
                return {x, x - sum};
        }
        assert(0);
    }
};
