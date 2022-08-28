class Solution {
public:
    bool canThreePartsEqualSum(vector<int>& arr) {
        int tot = 0;
        for(int x: arr)
            tot += x;
        if(tot % 3 != 0)
            return false;
        int rem = arr.size();
        for(int i = 0; rem > 0 && i < 2; ++i) {
            int tmp = tot / 3;
            for(int x: arr) {
                tmp -= x;
                --rem;
                if(!tmp)
                    break;
            }
            reverse(arr.begin(), arr.end());
        }
        return rem > 0;
    }
};
