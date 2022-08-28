class Solution {
public:
    vector<int> addToArrayForm(vector<int>& num, int k) {
        reverse(num.begin(), num.end());
        for(int i = 0; i < num.size(); ++i) {
            k += num[i];
            num[i] = k % 10;
            k /= 10;
            if(!k)
                break;
            if(i + 1 == num.size())
                num.push_back(0);
        }
        reverse(num.begin(), num.end());
        return num;
    }
};
