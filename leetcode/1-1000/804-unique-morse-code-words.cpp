class Solution {
public:
    int uniqueMorseRepresentations(vector<string>& words) {
        const string tr[] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
        set<string> sp;
        for(auto &word: words) {
            string rep = "";
            for(char ch: word)
                rep += tr[(int)(ch - 'a')];
            sp.insert(rep);
        }
        return sp.size();
    }
};
