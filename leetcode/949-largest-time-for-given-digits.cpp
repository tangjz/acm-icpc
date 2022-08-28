class Solution {
public:
    string largestTimeFromDigits(vector<int>& arr) {
        sort(arr.begin(), arr.end(), greater<>());
        do {
            int hh = arr[0] * 10 + arr[1];
            int mm = arr[2] * 10 + arr[3];
            if(hh < 24 && mm < 60) {
                static char buf[7];
                sprintf(buf, "%02d:%02d", hh, mm);
                return buf;
            }
        } while(prev_permutation(arr.begin(), arr.end()));
        return "";
    }
};
