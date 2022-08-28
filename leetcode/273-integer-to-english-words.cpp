class Solution {
public:
    string numberToWords(int num) {
        static const string cardinal[20] = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
        static const string cardinal_ty[11] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety", "Hundred"};
        static const pair<int, string> magnitude[3] = {{1000L, "Thousand"}, {1000000L, "Million"}, {1000000000L, "Billion"}};
        vector<string> ret;
        auto parse = [&](int val) { // val > 0
            int hh = val / 100;
            if(hh > 0) {
                ret.push_back(cardinal[hh]);
                ret.push_back(cardinal_ty[10]);
                val %= 100;
            }
            if(val >= 20) {
                hh = val / 10;
                ret.push_back(cardinal_ty[hh]);
                val %= 10;
            }
            if(val > 0)
                ret.push_back(cardinal[val]);
        };
        for(int i = 2; i >= 0; --i) {
            int hi = num / magnitude[i].first;
            if(hi > 0) {
                parse(hi);
                ret.push_back(magnitude[i].second);
                num %= magnitude[i].first;
            }
        }
        if(num > 0) {
            parse(num);
        } else if(ret.empty()) {
            ret.push_back(cardinal[0]);
        }
        string buf = ret.front();
        for(int i = 1; i < (int)ret.size(); ++i) {
            buf.push_back(' ');
            buf += ret[i];
        }
        return buf;
    }
};
