class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int adt = 1, n = digits.size();
        for(int i = n - 1; i >= 0; --i) {
            adt += digits[i];
            digits[i] = adt % 10;
            adt /= 10;
        }
        if(adt)
            digits.insert(digits.begin(), 1);
        return digits;
    }
};
