class WordsFrequency {
    unordered_map<string, int> ctr;
public:
    WordsFrequency(vector<string>& book) {
        ctr.clear();
        for(auto &it: book)
            ++ctr[it];
    }

    int get(string word) {
        auto it = ctr.find(word);
        return it != ctr.end() ? it -> second : 0;
    }
};

/**
 * Your WordsFrequency object will be instantiated and called as such:
 * WordsFrequency* obj = new WordsFrequency(book);
 * int param_1 = obj->get(word);
 */
