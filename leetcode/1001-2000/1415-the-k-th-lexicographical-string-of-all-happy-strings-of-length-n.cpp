class Solution {
public:
    string getHappyString(int n, int k) {
        vector<string> vec;
        function<void(string)> gen = [&](string cur) {
            int len = (int)cur.length();
            if(len == n) {
                vec.push_back(cur);
            } else {
                for(char ch = 'a'; ch <= 'c'; ++ch)
                    if(!len || (cur[len - 1] != ch))
                        gen(cur + ch);
            }
        };
        gen("");
        return k <= (int)vec.size() ? vec[k - 1] : "";
    }
};
