class Solution {
public:
    string addBinary(string a, string b) {
        int aLen = (int)a.size(), bLen = (int)b.size();
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        if(aLen < bLen) {
            a += string(bLen - aLen, '0');
            aLen = bLen;
        }
        int adt = 0;
        for(int i = 0; i < bLen; ++i) {
            adt += (a[i] == '1') + (b[i] == '1');
            a[i] = '0' + (adt & 1);
            adt >>= 1;
        }
        for(int i = bLen; adt && i < aLen; ++i) {
            adt += (a[i] == '1');
            a[i] = '0' + (adt & 1);
            adt >>= 1;
        }
        if(adt)
            a += '1';
        reverse(a.begin(), a.end());
        return a;
    }
};
