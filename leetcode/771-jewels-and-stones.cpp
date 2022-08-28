class Solution {
public:
    int numJewelsInStones(string J, string S) {
        int cnt = 0;
        unordered_set<char> jew;
        for(char ch : J)
            jew.insert(ch);
        for(char ch : S)
            cnt += jew.find(ch) != jew.end();
        return cnt;
    }
};
