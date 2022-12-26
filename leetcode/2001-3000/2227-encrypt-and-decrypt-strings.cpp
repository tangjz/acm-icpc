class Encrypter {
    map<char, pair<char, char> > enc;
    map<string, int> dec;
public:
    Encrypter(vector<char>& keys, vector<string>& values, vector<string>& dictionary) {
        int n = keys.size();
        for(int i = 0; i < n; ++i) {
            pair<char, char> it = {values[i][0], values[i][1]};
            enc[keys[i]] = it;
        }
        for(auto &pat: dictionary) {
            string ret = "";
            for(char ch: pat) {
                auto &it = enc[ch];
                ret.push_back(it.first);
                ret.push_back(it.second);
            }
            ++dec[ret];
        }
    }

    string encrypt(string word1) {
        string ret = "";
        for(char ch: word1) {
            auto &it = enc[ch];
            ret.push_back(it.first);
            ret.push_back(it.second);
        }
        return ret;
    }

    int decrypt(string word2) {
        auto it = dec.find(word2);
        return it != dec.end() ? it -> second : 0;
    }
};

/**
 * Your Encrypter object will be instantiated and called as such:
 * Encrypter* obj = new Encrypter(keys, values, dictionary);
 * string param_1 = obj->encrypt(word1);
 * int param_2 = obj->decrypt(word2);
 */
